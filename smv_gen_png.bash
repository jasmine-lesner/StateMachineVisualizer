
    # Example how to run this script:
    #
    # (
    #     cd ${smv_path}
    #     && export src_path= \ # visualize state machine *.c files inside this folder or children 
    #     && export smv_path= \ # path to your local copy of state machine visualizer aka smv repo
    #     && export pic32mx_include_path= # points to pic32mx include files ( eg Microchip/xc32/v4.10/pic32mx/include ) 
    #     && export course_include_path= # points to course include files ( eg ECE118 )
    #     && bash ./smv_gen_png.bash
    # )

    # safety options
    set -o nounset
    set -o errexit
    set -o pipefail

    # debug options
    # set -o errtrace
    # set -o functrace
    # set -o xtrace
    # export SHELLOPTS

    smv_path="${smv_path:-$PWD}"

    cd "${smv_path}"

    src_path="${src_path:-$PWD/samples/ECE118_RoachLab_Bailen}"
    src_path="${src_path:-$PWD/samples/ECE218_Team1_F2022}"

    pic32mx_include_path="${pic32mx_include_path:-$HOME/smv_dep/pic32mx/include}"
    course_include_path="${course_include_path:-$HOME/smv_dep/ECE118/include}"

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

    ilist=$( \
            find "$src_path" \
                -type d \
                -name include \
                -print0 \
            | xargs -0 -I{} echo "-I'{}'" \
            | tr "\n" " " \
        )

    # echo "ilist $ilist"

    # next command has pipefail?
    # iconfig=$( \
    #         find "$src_path" \
    #             -type f \
    #             -name 'ES_Configure.h' \
    #         | head -n 1 \
    #         | tr "\n" "\0" \
    #         | xargs -0 -I{} dirname {} \
    #         || true \
    #     )
    # echo "iconfig $iconfig"

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
    # echo "iconfig2 $iconfig2"

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
                && echo "cpp \
                    -I\"${course_include_path}\" \
                    -I\"${pic32mx_include_path}\" \
                    $ilist \
                    $iconfig2 \
                    -I'${b}' \
                    -I. \
                    '${ff}.undef' \
                    " \
                    | bash \
                    | perl -pe '
                        s{zz0912819zz}{}g;
                    ' \
                    | dos2unix \
                    > "${ff}.cp5" \
                && rm -f "${ff}.undef"
                    # -I'$iconfig' \
            ) 2>&1 
            # | tee "${f}.log"
        done

    rm -f "$epath"

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

    find "$src_path" | egrep '\.c\.cp5$|\.c\.cp5\.xml$'  | tr "\n" "\0" | xargs -0 rm -f

    # more HTML escapes may be needed:
    # s/&/&amp;/g;
    # s/"/&quot;/g; 
    # s/'\''/&apos;/g;

    # find $"$src_path" -name '*.c.cp5.gv' \
    #     | while read f ; do
    #         echo "processing $f"
    #         dot -Tpng "${f}" -o "${f}.png"
    #     done
