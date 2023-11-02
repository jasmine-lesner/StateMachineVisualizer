# State Machine Visualizer

### USAGE

Fetch smv.bash script:
```
wget https://raw.githubusercontent.com/jlesner/smv2/main/smv.bash 
```

Run smv.bash with path to your state machine files:

```
bash smv.bash ${path_to_code}
```

Inspect the generated files:

```
find ${path_to_code} -name '*.cp5*'
```

When run for the first time smv.bash will checkout the latest smv project and fetch and install all dependencies.
Instructions how to to remove what was installed are output when script ends.
