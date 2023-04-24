# State Machine Visualizer
## c_ast_xml_xslt.py

### WHAT IS IT?

From STDIN C code is read and its AST is output to STDOUT in XML format.

Arguments can specify files with XSLT to apply in the order supplied.

### LIMITATIONS?

* input must have all macros and header files expanded 
* input must be in a format supported by pycparser
* pycparser does not support: __extension__ va_list __attribute__ 

### EXAMPLE?

Assuming we want to visualize TemplateFSM.c located in:
```
/mnt/c/Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/
```
Output pycparser Abstract Syntax Tree (AST) in XML:
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
    | python c_ast_xml_xslt.py \
    > TemplateFSM_ast.xml
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
    | python c_ast_xml_xslt.py gv_digraph.xslt \
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
