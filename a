#!/bin/bash

# Run the command
ls -la

# Display the last argument of the previous command
echo "Last argument: $_\n"

for var in $(compgen -e); do
    # Print the variable and its value
    if [ "$var" = "_" ]; then
        echo "\$_=${!var}"
    else
        echo "$var=${!var}"
    fi
done