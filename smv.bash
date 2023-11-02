# debug options
# set -o errtrace
# set -o functrace
# set -o xtrace
# export SHELLOPTS

if [[ -z "$1" ]]; then
    echo "Error: You must supply src_path as an argument."
    exit 1
fi

# safety options
set -o nounset
set -o errexit
set -o pipefail


if [[ ! -d "$1" ]]; then
    echo "Error: Supplied argument src_path must be a folder."
    exit 1
fi

export src_path=`cd "${1}" ; pwd`

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


export smv_path="${smv_path:-$HOME/smv}"
export dep_path="${dep_path:-$HOME/smv_dep}"
export course_include_path="${course_include_path:-${dep_path}/ECE118/include}"
export pic32mx_include_path="${pic32mx_include_path:-${dep_path}/pic32mx/include}"


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


(
    cd "${smv_path}"
    ( docker images smv:0.05 \
            | tail -n 1 \
            | grep ^REPOSITORY \
	    && docker build -t smv:0.05 . 
    ) || true
)


docker run \
    --name smv_01 \
    --rm \
    -it \
    -v ${smv_path}:${smv_path} \
    -v ${src_path}:${src_path} \
    -v ${pic32mx_include_path}:${pic32mx_include_path} \
    -v ${course_include_path}:${course_include_path} \
    smv:0.05 \
    bash -c \
        " \
        cd ${smv_path} \
            && export smv_path=${smv_path} \
            && export src_path=${src_path} \
            && export pic32mx_include_path=${pic32mx_include_path} \
            && export course_include_path=${course_include_path} \
            && bash ./smv_gen_png.bash \
        "

echo "
NOTE: To uninstall smv, the following three commands may (or may not) be useful:
    docker rmi smv:0.05
    sudo apt remove podman podman-docker # first check you no longer need this 
    rm -rf ${smv_path} ${dep_path} # first check these were actually used for your installation!
"
