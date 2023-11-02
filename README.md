# State Machine Visualizer

### USAGE

STEP 1: Fetch smv.bash script:
```
wget https://raw.githubusercontent.com/jlesner/smv2/main/smv.bash 
```

STEP 2: Inspect smv.bash so you understand the changes it will make to your computer. 
Notice for example it will install git, curl and podman if these tools are missing.
To install these things smv.bash runs "sudo apt-get" which may ask your password.

STEP 3: Run smv.bash with path to your state machine files:

```
bash smv.bash ${path_to_code}
```

STEP 4: Inspect the generated *.gv and *.png files:

```
find ${path_to_code} -name '*.cp5*'
```

When run for the first time smv.bash will checkout the latest smv project and fetch and install all dependencies.
Instructions how to remove the things that smv.bash installs are output when smv.bash ends.
