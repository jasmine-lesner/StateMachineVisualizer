# State Machine Visualizer
## c_ast_xml_xslt.py

### WHAT IS IT?

From STDIN C code is read and its AST is output to STDOUT in XML format.

Arguments can specify files with XSLT to apply in the order supplied.

### SETUP?

```
# get access to install stuff

sudo bash 

# install python3 and pip3

apt-get update ; apt install -y python3 python3-pip python3.10-venv

# create and activate python virtual environment to install necessary packages (optional)

python3 -m venv smv ; . smv/bin/activate

# install pycparser lxml dependency

pip3 install pycparser lxml
```

### EXAMPLE?

Assuming we want to visualize TemplateFSM.c located in:
```
/mnt/c/Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/
```

Output the result of applying gv_digraph XSLT template:
```
( 
    cd "/mnt/c/Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/" \
    && /mnt/c/'Program Files'/Microchip/xc32/v4.10/bin/xc32-cpp.exe \
        -I'C:\Program Files/Microchip/xc32/v4.10/pic32mx/include/' \
        -I'C:\Users/chris/OneDrive/Desktop/ECE118/include' \
        -I'C:\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X' \
        -I'C:\Users/chris/OneDrive/Desktop/MPLAB_Projects/EventChecking.X/' \
        TemplateFSM.c \
) \
    | egrep -avi '^#|va_list|__attribute__' \
    | perl -pe's{__extension__}{ }g;' \
    | python3 c_ast_xml_xslt.py gv_digraph.xslt \
    | uniq \
    > gv_digraph.gv
```
The result will be:
```
# cat gv_digraph.gv

digraph fsm {

    // header
    // rankdir=LR;
    init [shape = "point", color = "black",style="filled",width=.1,forcelabels=false];

    // states
    InitPState;
    Hiding;
    Moving;
    Getting_Unstuck;

    // transitions
    init -> InitPState[label = ES_INIT];
    InitPState -> Hiding  [label = ES_INIT]; // switch if
    Hiding -> Moving  [label = DARK_TO_LIGHT]; // switch switch
    Moving -> Hiding  [label = LIGHT_TO_DARK]; // switch if
    Moving -> Getting_Unstuck  [label = BUMPER_PRESSED]; // switch if
    Getting_Unstuck -> Hiding  [label = LIGHT_TO_DARK]; // switch if
    Getting_Unstuck -> Moving  [label = ES_TIMEOUT]; // switch if

}
```

### SAMPLES?

```
sp=`pwd`/sample 

mkdir "$sp"

sf=(
        "step000_c_code_containing_state_machine.c"
        "step001_c_code_after_cpp.c"
        "step002_c_code_supported_by_pycparser.c"
        "step003_abstract_syntax_tree.xml"
        "step004_gv_digraph.gv"
        "step005_gv_digraph_unique.gv"
)

(
    target=TemplateFSM.c
    cd "/mnt/c/Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/" \
    && cat $target > "${sp}/${sf[0]}" \
    && /mnt/c/'Program Files'/Microchip/xc32/v4.10/bin/xc32-cpp.exe \
        -I'C:\Program Files/Microchip/xc32/v4.10/pic32mx/include/' \
        -I'C:\Users/chris/OneDrive/Desktop/ECE118/include' \
        -I'C:\Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X' \
        -I'C:\Users/chris/OneDrive/Desktop/MPLAB_Projects/EventChecking.X/' \
        $target \
) \
    | tee "${sp}/${sf[1]}" \
    | egrep -avi '^#|va_list|__attribute__' \
    | perl -pe's{__extension__}{ }g;' \
    | tee "${sp}/${sf[2]}" \
    | tee >( python3 c_ast_xml_xslt.py > "${sp}/${sf[3]}" ) \
    | python3 c_ast_xml_xslt.py gv_digraph.xslt \
    | tee "${sp}/${sf[4]}" \
    | uniq \
    | tee "${sp}/${sf[5]}" \
    > gv_digraph.gv


#  (smv) # wc -l sample/*
#     310 sample/step000_c_code_containing_state_machine.c
#    1294 sample/step001_c_code_after_cpp.c
#    1137 sample/step002_c_code_supported_by_pycparser.c
#    5873 sample/step003_abstract_syntax_tree.xml
#      26 sample/step004_gv_digraph.gv
#      23 sample/step005_gv_digraph_unique.gv
#    8663 total
#  (smv) #
```

### LIMITATIONS?

* input must have all macros and header files expanded (we use xc32-cpp.exe aka cpp for this)
* pycparser does not support: __extension__ va_list __attribute__ 
* input must be in a format supported by pycparser (we use grep and perl for this)

