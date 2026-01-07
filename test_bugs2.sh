#!/bin/bash

echo "========================================"
echo "Additional Specific Bug Tests"
echo "========================================"
echo ""

# Test the segfault in more detail
echo "TEST: check_cd with commands starting with 'cd'"
echo "---"
echo "Command: cdd (should be command not found)"
echo "cdd" | timeout 2 ./minishell 2>&1 || echo "Process timed out or crashed"
echo ""

echo "Command: cd123 (should be command not found)"
echo "cd123" | timeout 2 ./minishell 2>&1 || echo "Process timed out or crashed"
echo ""

# Test cd with actual directory
echo "TEST: cd to /tmp then pwd"
echo "---"
echo -e "cd /tmp\npwd\nexit" | ./minishell 2>&1 | grep -A5 "cd /tmp"
echo ""

# Test input redirection with bad file
echo "TEST: Input redirection with nonexistent file"
echo "---"
echo "ls < badfile.txt" | ./minishell 2>&1
echo ""

# Check what bash does
echo "COMPARISON: What bash does with bad input file"
echo "---"
bash -c "ls < badfile_xyz_999.txt" 2>&1
echo ""
