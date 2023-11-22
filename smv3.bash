# This script carries out the setup and execution of state machine visualizer. 
#
# This script is intended to be run on debian or ubuntu. It may work on other unix distributions but this is not tested.
#
# This script handles dependencies, environment setup, and execution within a Docker container. 
#
# This script is designed to be robust and user-friendly, providing clear error messages and automatically installing missing components.
#
# This script launches smv_gen_png.bash which creates state machine diagrams (as *.gv and *.png files) from *.c files


# **Environment Variables**
#
# Environment variables specify folders this script uses:
#     `src_path` is for the top folder containing the source files to be visualized 
#     `smv_path` is the home of the state machine visualizer tool
#     `pic32mx_include_path` for Microchip PIC32MX include files
#     `course_include_path` for course-specific include files
#
# src_path may be a relative path in unix or windows path format (e.g., /mnt/c/dev/ECE118 or C:\dev\ECE118)
# IMPORTANT: The rest must be absolute paths in unix path format (e.g., /mnt/c/dev/ECE118/include)
#


# **Example how to run this script**
#
# To use the default values for environment variables and download any needed pic32mx and course include files:
#
#     bash smv.bash $src_path
#
# If you already have pic32mx and course include files or want to use different versions specify their location as follows:
#
# (
#     export smv_path=~/smv # assuming you already have smv repo cloned here
#     && export pic32mx_include_path='/mnt/c/Program Files/Microchip/xc32/v4.10/pic32mx/include'
#     && export course_include_path='/mnt/c/dev/ECE118/include'
#     && bash smv.bash $src_path
# )
#


# **Debug Options** (Disabled by default)
#
# - These options are for debugging purposes and are commented out. If enabled, they provide trace and debugging information.
#
# set -o errtrace # This option, also known as -E, causes any trap on ERR to be inherited by shell functions, command substitutions, and commands executed in a subshell environment. The ERR trap is a mechanism in Bash that allows a function to be executed whenever a command exits with a non-zero status (indicating failure). With errtrace enabled, this behavior is extended to more parts of the script, making it easier to detect and handle errors.
# set -o functrace # This option enables function tracing in the script. It makes the DEBUG and RETURN traps (which are normally only triggered by the script itself) also be triggered by shell functions. The DEBUG trap typically runs before each command in the script, and the RETURN trap runs each time a shell function or a script executed with the . or source commands finishes executing. This option is useful for tracing the flow of execution through functions in a script.
# set -o xtrace # This option, often referred to as -x, is used for debugging purposes. It prints each command and its arguments to the standard error (stderr) before executing it. This trace includes expansions of variables and commands, providing a detailed view of what's happening in the script. It's particularly useful for seeing the flow of execution and understanding how data is being manipulated.
# export SHELLOPTS # This command exports the SHELLOPTS variable, making it an environment variable that is inherited by child processes. SHELLOPTS is a special shell variable that contains a colon-separated list of enabled shell options. 


# **Argument Parsing**
#
# Check if an argument is passed to the script (arg="$1"). If not, print an error message and exit.

arg="$1"

if [[ -z "$arg" ]]; then
    echo "Error: You must supply src_path as an argument."
    exit 1
fi


# **Script Safety Options** (Enabled by default)
#
set -o nounset # Causes the script to exit if an uninitialized variable is used. Helps catch mistakes.
set -o pipefail # Causes a pipeline (e.g., cmd1 | cmd2) to return the exit status of the last command in the pipe that failed.
set -o errexit # Exits the script if any command fails (returns a non-zero status). Together with pipefail this stops script on first error.


# **Apply UNIX Path Conversion** 
#
# Check if the argument contains a colon (:), suggesting a Windows-style path. If so, convert it to a Unix path using wslpath. Otherwise, use the argument directly.
#
if [[ "$arg" == *:* ]]; then
  unix_path="$(echo ${arg} | tr "\n" "\0" | xargs -0 wslpath -u )"
else
  unix_path="$arg"
fi

# **Directory Validation**
#
# Verify if the supplied unix_path argument is a directory. If not, it print an error message and exit.
#
if [[ ! -d "$unix_path" ]]; then
    echo "Error: Supplied argument src_path must be a folder."
    exit 1
fi


# **Apply Absolute Path Conversion**
#
# If supplied unix_path argument is relative convert it to be absolute using pwd. (e.g., local path ECE118 may be mapped to /mnt/c/dev/ECE118)
# This is needed for docker to work properly.
#

export src_path=`cd "${unix_path}" ; pwd`


# **Dependency Checks and Installations**
#
# Check for the existence of various tools (curl, git, docker) and try to install them if they are missing.
#
# NOTE: sudo below will prompt user for password if the user is not already root. This is needed to install packages.

( apt-get --version 2>&1 ) >/dev/null \
    || ( \
        echo "Error: apt-get package manager missing; please use debian or ubuntu to run me."
        exit 1
    )

( curl --version 2>&1 ) >/dev/null \
    || ( \
        sudo apt-get update \
            && sudo apt install -y curl
    )

( git --version 2>&1 ) >/dev/null \
    || ( \
    sudo apt-get update \
        && sudo apt install -y git
    )

( docker --version 2>&1 ) >/dev/null \
    || ( \
        sudo apt-get update \
            && sudo apt-get install -y podman podman-docker
            # podman emulates docker and takes less resources; to install docker run
            # apt-get install -y docker.io
    )


# **Set Default Values for Variables**: 
#
# Default values for `smv_path`, `src_path`, `pic32mx_include_path`, and `course_include_path` are set using using parameter expansion. 
# The bash parameter expansion `:-` operator assigns a default value if the variable is unset or null.
#
export smv_path="${smv_path:-$HOME/smv}"
export dep_path="${dep_path:-$HOME/smv_dep}"
export course_include_path="${course_include_path:-${dep_path}/ECE118/include}"
export pic32mx_include_path="${pic32mx_include_path:-${dep_path}/pic32mx/include}"


# **Fetch Dependencies**
#
# For course_include_path and pic32mx_include_path, checks if these directories exist. 
# If not, fetch these from specified URLs using curl and extract them.
#

if [[ -d "${course_include_path}" ]]; then
    echo "course_include_path exists: ${course_include_path}"
else
    echo "course_include_path does not exist: ${course_include_path}"
    echo "fetching from http://www.ufafu.com/smv/ECE118.tgz"
    ( 
        mkdir -p "${course_include_path}"
        cd "${course_include_path}"/../..
        curl -L http://www.ufafu.com/smv/ECE118.tgz \
            | tar -xzf - 
    )
fi


if [[ -d "${pic32mx_include_path}" ]]; then
    echo "pic32mx_include_path exists: ${pic32mx_include_path}"
else
    echo "pic32mx_include_path does not exist: ${pic32mx_include_path}"
    echo "fetching from http://www.ufafu.com/smv/pic32mx.tgz"
    ( 
        mkdir -p "${pic32mx_include_path}"
        cd "${pic32mx_include_path}"/../..
        curl -L http://www.ufafu.com/smv/pic32mx.tgz \
            | tar -xzf - 
    )
fi


# **Clone Repository**
#
# If the smv_path directory doesn't exist, it clone a Git repository from a specified URL.
#

if [[ -d "${smv_path}" ]]; then
    echo "smv_path exists: ${smv_path}"
else
    echo "smv_path does not exist: ${smv_path}"
    echo "cloning repo from https://github.com/jlesner/smv2"
    (
        base_smv=$(basename "${smv_path}")
	dirname_smv=$(dirname "${smv_path}")
        cd "${dirname_smv}"
        git clone https://github.com/jlesner/smv2 ${base_smv}
    )
fi


# **Build and Launch Container**
#
# Build a container image tagged smv:0.05 and then launch a new temporary container with this image. 
# Mount several volumes from the host to the container and execute smv_gen_png.bash inside the container.
#

(
    cd "${smv_path}"
    ( docker images smv:0.05 \
            | tail -n 1 \
            | grep ^REPOSITORY \
	    && docker build -t smv:0.05 . 
    ) || true
)

docker run \
    --rm \
    -it \
    -v "${smv_path}":"${smv_path}" \
    -v "${src_path}":"${src_path}" \
    -v "${pic32mx_include_path}":"${pic32mx_include_path}" \
    -v "${course_include_path}":"${course_include_path}" \
    smv:0.05 \
    bash -c \
        " \
        cd '${smv_path}' \
            && export smv_path='${smv_path}' \
            && export src_path='${src_path}' \
            && export pic32mx_include_path='${pic32mx_include_path}' \
            && export course_include_path='${course_include_path}' \
            && bash ./smv_gen_png.bash \
        "


# **Uninstallation** 
#
# Explain how to uninstall showing commands to remove Docker images, apt packages, and directories related to the installation.
#
echo "
NOTE: To uninstall smv, the following three commands may (or may not) be useful:
    docker rmi smv:0.05 ubuntu:20.04
    sudo apt remove podman podman-docker # first check you no longer need this 
    rm -rf '${smv_path}' '${dep_path}' # first check these were actually used for your installation!
"
