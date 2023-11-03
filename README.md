# State Machine Visualizer

### USAGE

STEP 1: 

Fetch smv.bash script:
```
wget https://raw.githubusercontent.com/jlesner/smv2/main/smv.bash 
```

STEP 2:

Inspect smv.bash so you understand the changes it will make to your computer. Notice for example it will install git, curl and podman if these tools are missing.

If necessary to install these things smv.bash runs ```sudo apt-get``` which may ask for your password.

When run for the first time smv.bash will checkout the latest state machine visualizer (aka smv) project and fetch and install dependencies. 

The script requires Linux with apt package manager (like Ubuntu) so on Windows you may want to install Ubuntu/WSL2 or that in VM if using MACOS.

To isolate itself from the local environment smv.bash builds a Linux container and installs remaining dependencies (python, java, etc) and runs smv code inside that container. This container takes about 900mb. 

Instructions to remove the things that smv.bash installs are output when smv.bash ends. If you leave these installed the script runs faster next time.

STEP 3: 

Run smv.bash with path to your state machine files:
```
bash smv.bash ${path_to_code}
```

STEP 4: 

Inspect the generated *.gv and *.png files:
```
find ${path_to_code} -name '*.cp5*'
```
