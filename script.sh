#!/bin/bash

# Find all .c files in the src/ directory and its subdirectories
SRC_FILES=($(find src -type f -name "*.c"))
COUNT=0

echo -n "SRC = "  # Start the Makefile variable

for FILE in "${SRC_FILES[@]}"; do
    echo -n "$FILE "

    # Every 5th file, add a backslash and a new line
    ((COUNT++))
    if ((COUNT % 4 == 0)); then
        echo "\\"
        echo -n "      "
    fi
done

echo ""  # End the line
