#!/bin/bash

# Extract failing test commands from test output
OUTPUT_FILE="/tmp/mstest_output.txt"
MAND_DIR="/home/lpons/Desktop/Commoncore/Minishell/mand"

# Parse the test output and extract line numbers of failures
awk '
/^  #/ { section=$0 }
/^  [0-9]+:.*❌/ {
    match($0, /([0-9]+):.*\/([^\/]+\.sh):([0-9]+)/, arr)
    if (arr[1] && arr[2] && arr[3]) {
        print arr[2] ":" arr[3] ":" arr[1]
    }
}
' "$OUTPUT_FILE" | sort -u
