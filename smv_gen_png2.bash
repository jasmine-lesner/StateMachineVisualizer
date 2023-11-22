# This script creates state machine diagrams (as *.gv and *.png files) from *.c files

# **Environment Variables**
#
# Environment variables specify folders this script uses:
#     `src_path` is for the top folder containing the source files to be visualized 
#     `smv_path` is the home of the state machine visualizer tool
#     `pic32mx_include_path` for Microchip PIC32MX include files
#     `course_include_path` for course-specific include files
#
# Example how to launch this script:
#
# (
#     cd ${smv_path}
#     && export src_path= # path to state machine *.c files (inside this folder or children)
#     && export smv_path= # path to your local copy of state machine visualizer aka smv repo
#     && export pic32mx_include_path= # path to pic32mx include files ( eg Microchip/xc32/v4.10/pic32mx/include ) 
#     && export course_include_path= # path to course include files ( eg ECE118 )
#     && bash ./smv_gen_png.bash
# )


# **Script Safety Options** (Enabled by default)
#
set -o nounset # Causes the script to exit if an uninitialized variable is used. Helps catch mistakes.
set -o pipefail # Causes a pipeline (e.g., cmd1 | cmd2) to return the exit status of the last command in the pipe that failed.
set -o errexit # Exits the script if any command fails (returns a non-zero status). Together with pipefail this stops script on first error.

# **Debug Options** (Disabled by default)
#
# - These options are for debugging purposes and are commented out. If enabled, they provide trace and debugging information.
#
# set -o errtrace # This option, also known as -E, causes any trap on ERR to be inherited by shell functions, command substitutions, and commands executed in a subshell environment. The ERR trap is a mechanism in Bash that allows a function to be executed whenever a command exits with a non-zero status (indicating failure). With errtrace enabled, this behavior is extended to more parts of the script, making it easier to detect and handle errors.
# set -o functrace # This option enables function tracing in the script. It makes the DEBUG and RETURN traps (which are normally only triggered by the script itself) also be triggered by shell functions. The DEBUG trap typically runs before each command in the script, and the RETURN trap runs each time a shell function or a script executed with the . or source commands finishes executing. This option is useful for tracing the flow of execution through functions in a script.
# set -o xtrace # This option, often referred to as -x, is used for debugging purposes. It prints each command and its arguments to the standard error (stderr) before executing it. This trace includes expansions of variables and commands, providing a detailed view of what's happening in the script. It's particularly useful for seeing the flow of execution and understanding how data is being manipulated.
# export SHELLOPTS # This command exports the SHELLOPTS variable, making it an environment variable that is inherited by child processes. SHELLOPTS is a special shell variable that contains a colon-separated list of enabled shell options. 


# **Setting Default Values for Variables**: 
#
# Default values for `smv_path`, `src_path`, `pic32mx_include_path`, and `course_include_path` are set using using parameter expansion. 
# The bash parameter expansion `:-` operator assigns a default value if the variable is unset or null.

smv_path="${smv_path:-$PWD}"

cd "${smv_path}" # Change the current working directory to the one specified in `smv_path`.

src_path="${src_path:-$PWD/samples/ECE118_RoachLab_Bailen}"
src_path="${src_path:-$PWD/samples/ECE218_Team1_F2022}"

pic32mx_include_path="${pic32mx_include_path:-$HOME/smv_dep/pic32mx/include}"
course_include_path="${course_include_path:-$HOME/smv_dep/ECE118/include}"


# **CPP Macro Encoding (`encode.pl`)**:
#
# `epath`` points to a *runtime* generated Perl script which encodes #define macros to prevent them beign expanded by CPP so that diagrams have labels like TURN_RIGHT instead of 0x12345678

epath="$src_path"/encode.pl

find \
    "${src_path}" \
    "${course_include_path}" \
    -type f \( -name '*.h' -o -name '*.hpp' -o -name '*.c' \) \
    | tr "\n" "\0" \
    | xargs -0 cat \
    | dos2unix \
    | ( egrep -ai '^#define' || true ) \
    | perl -pe 's/#define (\w)(\w+)[ \(].*$/s{\\b$1$2\\b}{$1zz0912819zz$2}g; # encode123 /g;' \
    | ( grep encode123 || true ) \
    | perl -pe 's/ # encode123//g;' \
    | sort | uniq \
    > "${epath}"

# Step-by-step: 
#
# 1. **Finding Files (`find` Command)**:
#     - The `find` command searches for files within the directories specified by `${src_path}` and `${course_include_path}`.
#     - The `-type f` option restricts the search to files (as opposed to directories or other types of items).
#     - The `-name` options specify the file extensions to look for: `*.h`, `*.hpp`, and `*.c`, which are typically C and C++ header and source files.
#
# 2. **Replacing Newlines (`tr` Command)**:
#     - The `tr "\n" "\0"` command translates newline characters (`\n`) into null characters (`\0`). This is often done to handle filenames that contain spaces or unusual characters safely.
#
# 3. **Concatenating Files (`xargs` and `cat` Commands)**:
#     - The `xargs -0 cat` part reads the null-terminated strings from the previous command and uses `cat` to concatenate the contents of the files.
#
# 4. **Converting Line Endings (`dos2unix` Command)**:
#     - The `dos2unix` command converts Windows line endings (CRLF) to Unix line endings (LF), ensuring compatibility in Unix/Linux environments.
#
# 5. **Extracting `#define` Directives (`egrep` Command)**:
#     - The `egrep -ai '^#define'` command extracts lines that start with `#define`, ignoring case (`-i`). The `|| true` ensures that the pipeline doesn't fail if `egrep` doesn't find any matching lines.
#
# 6. **Perl Regular Expression Processing**:
#     - Two Perl (`perl -pe`) commands are used to perform regular expression substitutions on the extracted lines:
#         - The first `perl` command encodes certain patterns found after `#define` directives. 
#           It is targeting macro names and replacing parts of them with a unique string (`zz0912819zz`), marked with a comment `# encode123` for later identification.
#         - The second `perl` command removes the `# encode123` marker, leaving only the modified macro names.
#
# 7. **Filtering and Deduplicating (`grep`, `sort`, `uniq`)**:
#     - The `grep encode123 || true` command filters the lines containing the `encode123` marker.
#     - The `sort | uniq` commands sort the results and remove duplicate lines.
#
# 8. **Redirecting Output**:
#     - Finally, the output of this pipeline is redirected to a file specified by the `${epath}` variable.


# **Include List (for CPP) **
#
# Next we build `ilist` a space-separated string of include paths, each prefixed with `-I`. 
# This format is used by CPP to specify directories where the it will look for header files. 
# If there are include directories at `path1/include` and `path2/include`, `ilist` will end up looking something like `-I'path1/include' -I'path2/include'`.

ilist=$( \
        find "$src_path" \
            -type d \
            -name include \
            -print0 \
        | xargs -0 -I{} echo "-I'{}'" \
        | tr "\n" " " \
    )

# Step-by-step: 
#
# 1. **`find "$src_path"`**:
#     - The `find` command is used to search through directories and files. In this case, it's looking within the directory specified by the `src_path` variable.
#
# 2. **`-type d`**:
#     - This option tells `find` to look only for directories (`d`).
#
# 3. **`-name include`**:
#     - This option restricts the search to directories named `include`. 
#
# 4. **`-print0`**:
#     - This outputs the found directory names, with each name terminated by a null character (`\0`) instead of a newline. 
#       This is useful for handling filenames that contain spaces, newlines, or other unusual characters.
#
# 5. **`| xargs -0 -I{} echo "-I'{}'"`**:
#     - The output from `find` is piped (`|`) to `xargs`, which is used to build and execute command lines from the input.
#     - `-0` tells `xargs` to expect null-terminated inputs (which matches the output of `find ... -print0`).
#     - `-I{}` is a placeholder that will be replaced by each input line in the command `echo "-I'{}'"`.
#     - The `echo` command outputs each directory path prefixed with `-I'`, which is a common way to specify include directories for compilers.
#
# 6. **`| tr "\n" " "`**:
#     - This translates (using the `tr` command) all newline characters into spaces. 
#        This is important because `xargs` by default outputs items separated by newlines, but the intention here is to create a space-separated list.


# **Include Configure List (for CPP)**:
#
# Here we build `iconfig2`, a space-separated string of include flags for each directory containing an `ES_Configure.h` file.

iconfig2=$( \
        find "$src_path" \
            -type f \
            -name 'ES_Configure.h' \
            -print0 \
        | xargs -0 -I{} dirname {} \
        | tr "\n" "\0" \
        | xargs -0 -I{} echo "-I'{}'" \
        | tr "\n" " " \
    )

# Step-by-step: 
#
# 1. **`find "$src_path" -type f -name 'ES_Configure.h' -print0`**:
#     - This command searches within the directory specified by `src_path` for files (`-type f`) named `ES_Configure.h`.
#     - The `-print0` option prints the full file path followed by a null character (`\0`). This is useful for handling filenames with spaces or unusual characters.
#
# 2. **`| xargs -0 -I{} dirname {}`**:
#     - The output from `find` is piped (`|`) into `xargs`, which executes the `dirname` command for each found file path.
#     - `xargs -0` tells `xargs` to expect null-terminated input (matching the `-print0` from `find`), which is safer for handling filenames with special characters.
#     - `dirname {}` extracts the directory path of each found file, with `{}` being a placeholder for each input line.
#
# 3. **`| tr "\n" "\0"`**:
#     - This translates (`tr`) newline characters (`\n`) into null characters (`\0`), preparing the list of directories for another round of `xargs`.
#
# 4. **`| xargs -0 -I{} echo "-I'{}'"`**:
#     - Here, `xargs` processes each null-terminated string (directory path) and echoes it with `-I` prepended and surrounded by single quotes.
#     - This step formats each directory path into a format suitable for inclusion flags (e.g., `-I'/path/to/dir'`) used to specify directories where include files are located.
#
# 5. **`| tr "\n" " "`**:
#     - Finally, this translates newline characters into spaces, converting the multi-line output into a single line.


# **Apply CPP**
#
# Here we apply CPP to C source files that contain references to (`nextState`) as these are deemed to contain state machines.
#

find "$src_path" -type f -name '*.c' -print0 \
    | xargs -0 egrep -l nextState \
    | while read f ; do
        ff="`basename \"${f}\"`"
        b="`dirname \"${f}\"`"
        (
            cd "$b" \
            && echo "amalgamating '${f}'" \
            && cat "${ff}" \
                | dos2unix \
                | perl -p "${epath}" \
                | ( egrep -avi '^#define '  || true ) \
                > "${ff}.undef" \
            && echo "( cd '$b' ; cpp \
                -I\"${course_include_path}\" \
                -I\"${pic32mx_include_path}\" \
                $ilist \
                $iconfig2 \
                -I'${b}' \
                -I. \
                '${ff}.undef' \
                )" \
                | tee /dev/stderr \
                | bash \
                | perl -pe '
                    s{zz0912819zz}{}g;
                ' \
                | dos2unix \
                > "${ff}.cp5"
                # \
            # && rm -f "${ff}.undef"
                # -I'$iconfig' \
        ) 2>&1 
        # | tee "${f}.log"
    done

rm -f "$epath" # encode.pl script has served its purpose and is no longer needed

# Step-by-step: 
#
# 1. **Finding Files and Identifying Relevant Ones**:
#     - `find "$src_path" -type f -name '*.c' -print0`: This command finds all C source files (`*.c`) in the directory specified 
#        by `src_path`. The `-print0` option outputs the file names separated by null characters, which is useful for handling filenames with spaces.
#     - `| xargs -0 egrep -l nextState`: The file paths are piped to `egrep` to search for the pattern `nextState` in these files. 
#        The `-l` option makes `egrep` list only the names of files where the pattern is found.
#
# 2. **Processing Each File**:
#     - The script then enters a `while read f` loop to process each file that contains the `nextState` pattern.
#     - `ff="`basename \"${f}\"`"`: Extracts the filename from the full path.
#     - `b="`dirname \"${f}\"`"`: Extracts the directory path from the full path.
#
# 3. **Amalgamation and Preprocessing**:
#     - The script changes directory to the file's directory (`cd "$b"`) and performs a series of operations:
#         - It echoes a message indicating the start of processing for the file.
#         - The file is concatenated (`cat "${ff}"`), converted from DOS to UNIX text format (`dos2unix`), and then processed with a Perl script (`perl -p "${epath}"`).
#         - The perl ${epath} script is generated above and protects macros from being expanded by CPP.
#         - Any line starting with `#define` is removed using `egrep -avi '^#define '`, and `|| true` ensures that the pipeline does not fail if `egrep` doesn't match any lines.
#         - The processed content is saved into a temporary file (`"${ff}.undef"`).
#
# 4. **Further Processing with C Preprocessor**:
#     - The script constructs a command to run the C preprocessor (`cpp`) on the `.undef` file, including various include paths 
#       (specified by `course_include_path`, `pic32mx_include_path`, `ilist`, `iconfig2`, and the current and root directories).
#     - This command is echoed (and logged via `tee /dev/stderr`) and then executed in a subshell (`| bash`).
#
# 5. **Post-Processing and Final Output**:
#     - Output from the C preprocessor is further processed with Perl (`perl -pe`), replacing `zz0912819zz` with nothing.
#     - The purpose of this is to remove ${epath} encoding that protects macros from being expanded by CPP.
#     - The final output is converted again to UNIX format (`dos2unix`) and saved as `"${ff}.cp5"`.
#
# 6. **Cleanup and Logging**:
#     - Commented-out lines (`# && rm -f "${ff}.undef"` and `# | tee "${f}.log"`) show cleanup and logging which are currently disabled.
#


# **Apply PycParser and XSLT and GraphViz**
#
# We locate `*.c.cp5` files in `src_path` (generated above) and build their abstract syntax tree AST using PycParser, 
# then apply pipeline of XLST templates, and finally use GraphViz to generate state diagram in PNG format. 

find "$src_path" -name '*.c.cp5' \
    | while read f ; do
        echo "visualizing '$f'"
        (
            cat "$f" \
                | tr -d '\r' \
                | ( egrep -avi '^[[:blank:]]*$|^#|va_list|__attribute__' || true ) \
                | perl -pe's{__extension__}{ }g; s{__}{}g; ' \
                | python3 c_ast_xml.py \
                | tee "${f}.xml" \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00005_identity.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00100_declutter_attributes.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00200_add_bLine_eLine.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00300_add_CurrentStateTest.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00300_add_EventParamTest.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00300_add_EventTypeTest.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00300_add_NextStateLabel.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00400_add_CascadeElements.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00500_add_CascadeLabel.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00550_add_EventLabel.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00560_add_Guard_Element.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00570_add_Guard_Attributes.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00600_add_onEntry_onExit.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00600_add_onTransition2.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00620_drop_unwanted_code.xml \
                | saxonb-xslt -s:/dev/stdin -o:/dev/stdout -xsl:xslt/s00800_gv_digraph4.xml \
                | perl -pe 's/ && / &amp;&amp; /g;
                            s/ < / &lt; /g;
                            s/ > / &gt; /g;
                            s/ <= / &lt;= /g;
                            s/ >= / &gt;= /g;
                        ' \
                > "${f}.gv"

            dot -Tpng "${f}.gv" -o "${f}.png"

        ) 2>&1 
        # | tee "${f}.log"
    done

# Step-by-step: 
#
# 1. **Finding Files and Iteration**:
#    - The `find` command locates all files with the `.c.cp5` extension within `src_path`.
#    - The `while read f` loop processes each found file one by one.
#
# 2. **Initial Processing of Each File**:
#    - Each file's contents are read and echoed with `cat "$f"`.
#    - The `tr -d '\r'` command removes carriage return characters, which is useful for ensuring compatibility with Unix line endings.
#    - A series of `egrep` filters out lines that are either blank, start with `#`, or contain specific strings like `va_list` or `__attribute__`. 
#      The `|| true` ensures that the pipeline doesn't break if `egrep` doesn't find a match.
#
# 3. **Perl Script Processing**:
#    - The Perl one-liner makes two substitutions: it replaces `__extension__` with a space and removes double underscores (`__`).
#      The purpose of this is to ensure compatibility with the C parser used in the next step.
#
# 4. **Generating XML Representation**:
#    - The script uses `python3 c_ast_xml.py` to convert the processed C code into an XML representation of its abstract syntax tree (AST).
#
# 5. **Multiple XSLT Transformations**:
#    - The XML output is then piped through a series of XSLT (eXtensible Stylesheet Language Transformations) using `saxonb-xslt`. 
#      Each transformation (`xslt/s00005_identity.xml`, etc.) progressively modifies the XML, to prepare it for visualization.
#      For example the purpose of s00005_identity.xml is to format the XML output of PyParser to allow diff to work better during debugging.
#      For example the purpose of s00100_declutter_attributes.xml remove AST elements not needed for subsequent processing.
#      See comments inside each XSLT *.xml template for more details.
#
# 6. **HTML Escape Processing**:
#    - A final Perl script further processes the GraphViz diagram description, replacing certain logical and comparison operators 
#      (`&&`, `>`, `<`, `<=`, `>=`) with their HTML entity equivalents to ensure proper parsing by GraphViz.
#      NOTE more HTML escapes may be needed such as: 
#         s/&/&amp;/g;
#         s/"/&quot;/g; 
#         s/'\''/&apos;/g;
#
# 7. **GraphViz Visualization**:
#    - The processed output is saved as a GraphViz file (`${f}.gv`).
#    - The `dot` command from GraphViz is then used to generate a PNG image from the `.gv` file, visualizing the structure of the C code.
#
# 8. **Error Handling and Logging**:
#    - The `2>&1` notation combines standard output and error streams, which can be used for logging or debugging (as indicated by the commented out `| tee "${f}.log"`).


# **Cleanup Intermedite Files**
#
# Find all files within `src_path` that end with `.c.cp5` or `.c.cp5.xml`, and then safely and forcefully delete them. 
# The use of null characters as delimiters in `xargs` makes this command robust against file names with unusual characters or spaces.

find "$src_path" | egrep '\.c\.cp5$|\.c\.cp5\.xml$'  | tr "\n" "\0" | xargs -0 rm -f

# Step-by-step:
#
# 1. **`find "$src_path"`**:
#    - This command searches for all files and directories within the directory specified by the variable `src_path`.
#
# 2. **`egrep '\.c\.cp5$|\.c\.cp5\.xml$'`**:
#    - The output from `find` is piped to `egrep`, which is a version of `grep` used for pattern matching with regular expressions.
#    - The regex `'\.c\.cp5$|\.c\.cp5\.xml$'` is used to filter the list of files. It looks for files that end with `.c.cp5` or `.c.cp5.xml`. The `$` ensures that the pattern matches the end of the file name.
#
# 3. **`tr "\n" "\0"`**:
#    - This translates (or replaces) newline characters (`\n`) in the output with null characters (`\0`). 
#      This is done because file names can potentially contain spaces or other special characters, which might be misinterpreted by the next command. Using null characters as delimiters avoids this issue.
#
# 4. **`xargs -0 rm -f`**:
#    - The modified output is then piped to `xargs`, which builds and executes command lines from standard input.
#    - The `-0` option tells `xargs` to expect input items to be terminated by a null character, which matches the output from the `tr` command.
#    - `rm -f` is the command that `xargs` executes. `rm` is the remove command in Unix/Linux, and the `-f` option forces deletion without prompting for confirmation, even if the files are write-protected.

