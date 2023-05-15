# State Machine Visualizer

### DEMO

Here is the [latest presentation](demo/smv_0020.pdf).

### c_ast_xml_xslt.py

From STDIN C code is read and its AST is output to STDOUT in XML format.

Arguments can specify files with XSLT to apply in the order supplied.

Supplied gv_digraph.xslt creates state machine visualization. 

### USAGE

Assuming we want to visualize TemplateFSM.c located in:
```
/mnt/c/Users/chris/OneDrive/Desktop/MPLAB_Projects/FSM_Roach.X/
```

To output the result of applying gv_digraph XSLT template:
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
    | python3 c_ast_xml_xslt.py xslt/*.xslt \
    > gv_digraph.gv
```

The result will be:
```
# cat gv_digraph.gvEven

digraph fsm {
    // states
    "InitPState";
    "Hiding";
    "Moving";
    "Getting_Unstuck";

    // transitions
    "InitPState" -> "Hiding" [label = "ES_INIT" ]; // switch if
    "Hiding" -> "Moving" [label = "DARK_TO_LIGHT" ]; // switch switch
    "Moving" -> "Hiding" [label = "LIGHT_TO_DARK" ]; // switch if
    "Moving" -> "Getting_Unstuck" [label = "BUMPER_PRESSED(1)" ]; // switch if
    "Moving" -> "Getting_Unstuck" [label = "BUMPER_PRESSED(2)" ]; // switch if
    "Moving" -> "Getting_Unstuck" [label = "BUMPER_PRESSED(4)" ]; // switch if
    "Moving" -> "Getting_Unstuck" [label = "BUMPER_PRESSED(8)" ]; // switch if
    "Getting_Unstuck" -> "Hiding" [label = "LIGHT_TO_DARK" ]; // switch if
    "Getting_Unstuck" -> "Moving" [label = "ES_TIMEOUT(0)" ]; // switch if
}
```

### SETUP

```
# get access to install stuff

sudo bash 

# install python3 and pip3

apt-get update ; apt install -y python3 python3-pip python3.10-venv xsltproc

# create python virtual environment called smv to install necessary packages (optional)

python3 -m venv smv

# activate smv python virtual environment (optional)

. smv/bin/activate

# install pycparser lxml dependency

pip3 install pycparser lxml
```

### LIMITATIONS

Input code must be in a format supported by pycparser:
* all macros and header files expanded (xc32-cpp.exe aka cpp does this)
* pycparser does not support: __extension__ va_list __attribute__ (grep and perl remove these)

Input must have gv_digraph.xslt supported code structure (see example below)
* top switch statement on CurrentState 
* EventType checked using nested switch statements or checked using if statments
* nextState is assigned inside these nested switch or if statements
* switch statements can be nested but only one level deep (see EXAMPLE below)
* if statments can have arbirary nesting
 
Example of supported code structure:

  ```
    switch (CurrentState) {
  
    case InitPState: 
        if (ThisEvent.EventType == ES_INIT)
        {
            nextState = Hiding;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
    case Hiding: 
        switch (ThisEvent.EventType) { // nested 
            
            case DARK_TO_LIGHT:
                goForward(MOVING_SPEED);
                nextState = Moving;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                break;
                
            default:
                break;
        }
        break;
    case Moving: 
        if (ThisEvent.EventType == LIGHT_TO_DARK) 
        {
            stopMovement();
            nextState = Hiding;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        } 
        
        if (ThisEvent.EventType == BUMPER_PRESSED)
        {
           if(ThisEvent.EventParam == 1)
           {
               previousBumpers = 1; 
               backUpRight(TURNING_SPEED);
                ES_Timer_InitTimer(SIMPLE_SERVICE_TIMER,TURN_TIME);
                nextState = Getting_Unstuck;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;    
           } 
           // ..
           else if(ThisEvent.EventParam == 8)
           {
                turnRight(TURNING_SPEED);
                ES_Timer_InitTimer(SIMPLE_SERVICE_TIMER,TURN_TIME);
                nextState = Getting_Unstuck;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
           }
        }
        break;        
    default: // all unhandled states fall into here
        break;
    } // end switch on CurrentState

```


### STEPS

```
sp=`pwd`/sample 

mkdir "$sp"

sf=(
        "step000_c_code_containing_state_machine.c"
        "step001_c_code_after_cpp.c"
        "step002_c_code_supported_by_pycparser.c"
        "step003_abstract_syntax_tree.xml"
        "step004_gv_digraph.gv"
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
    | python3 c_ast_xml_xslt.py xslt/*.xslt \
    | tee "${sp}/${sf[4]}" \
    > gv_digraph.gv


# $ wc -l sample/*
#   310 sample/step000_c_code_containing_state_machine.c
#  1294 sample/step001_c_code_after_cpp.c
#  1137 sample/step002_c_code_supported_by_pycparser.c
#  5873 sample/step003_abstract_syntax_tree.xml
#    25 sample/step004_gv_digraph.gv
#  8639 total
# $
```
