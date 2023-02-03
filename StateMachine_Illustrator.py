#import sys
# from glob import glob
from pathlib import Path
import re

P = Path('.')

Pfiles = [x for x in P.iterdir() if x.is_file()]
# print(Pfiles)

configFile = P/'ES_Configure.h'


def draw_state_machine(file_address):
    myfile = open(file_address,'r')
    cFile = myfile.readlines()
    myfile.close()
    # print(cFile)

    # Find the initial psudo state
    sub1,sub2,sub3 = "  CurrentState","=","nextState"
    settingCurrentState = [s for s in cFile if sub1 in s and sub2 in s and not sub3 in s]
    if len(settingCurrentState) < 1:
        print("Missing Init State")
    else:
        settingCurrentState = re.findall(r'\= (.\w*)',settingCurrentState[0])[0]
        inital_state = settingCurrentState
    print(inital_state)

    # Get list of all states
    states = []
    sub = "static const char *StateNames[] = {"
    startStateEnumIdx = [idx for idx, s in enumerate(cFile) if sub in s][0]+1
    while not '}' in cFile[startStateEnumIdx]:
          states.append(re.findall(r'"(.*?)"',cFile[startStateEnumIdx])[0])
          startStateEnumIdx += 1
    
    print(states)

    #Read the initial psudo state
    sub = "case " + inital_state
    StateIdx = [idx for idx, s in enumerate(cFile) if sub in s][0]+1
    while not 'nextState =' in cFile[StateIdx]:
        StateIdx += 1
    
    first_state = re.findall(r'= (.*?);',cFile[StateIdx])[0]
    print(first_state)




if configFile in Pfiles: #Does ES_Configure exist? in the .X project
    myfile = open(configFile,'r')
    configFile = myfile.readlines()
    myfile.close()
    sub = "#define NUM_SERVICES"
    num_services = [s for s in configFile if sub in s]
    if len(num_services) == 0 or len(num_services) > 1:
        print("problem with NUM_SERVICES")
    else: 
        number_of_services = [int(s) for s in re.findall(r'\b\d+\b', num_services[0])][0] # Isolate the integer of services  
        if(number_of_services > 1):
            sub = "#define SERV_1_HEADER"  
            header = [s for s in configFile if sub in s][0].split(" ")[2]
            c_file = header.split('.')[0][1:]+".c"
            state_machine_file = P/c_file
            if state_machine_file in Pfiles: #Checks if the .c exists in the .X project
                draw_state_machine(state_machine_file)
            else:
                print("MISSING " + c_file)
else:
    print("NO CONFIG FILE!")

             



