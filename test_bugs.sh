#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "=========================================="
echo "Testing Minishell Bugs"
echo "=========================================="
echo ""

# Test 1: check_cd always prints error
echo -e "${YELLOW}TEST 1: check_cd() always prints error${NC}"
echo "Command: cd /tmp"
echo "Expected: No error (cd should succeed)"
echo "Actual output:"
echo "cd /tmp" | ./minishell 2>&1 | grep -i "chdir\|failed"
if [ $? -eq 0 ]; then
    echo -e "${RED}❌ BUG CONFIRMED: Error message shown even on success${NC}"
else
    echo -e "${GREEN}✅ No bug: No error message${NC}"
fi
echo ""

# Test 2: cd doesn't work (runs in child process)
echo -e "${YELLOW}TEST 2: cd runs in child process (doesn't work)${NC}"
echo "Commands: pwd, cd /tmp, pwd"
echo "Expected: Second pwd should show /tmp"
echo "Actual output:"
CURRENT_DIR=$(pwd)
echo -e "pwd\ncd /tmp\npwd" | ./minishell 2>&1 | grep "^/"
echo -e "${YELLOW}Note: If both pwd outputs are the same, cd didn't work${NC}"
echo ""

# Test 3: direct_io() no error checking
echo -e "${YELLOW}TEST 3: direct_io() doesn't check for file errors${NC}"
echo "Command: cat < nonexistent_file_12345.txt"
echo "Expected: Error message about file not found"
echo "Actual output:"
echo "cat < nonexistent_file_12345.txt" | ./minishell 2>&1
echo ""

# Test 4: check_cd() only checks first 2 chars
echo -e "${YELLOW}TEST 4: check_cd() only checks first 2 chars${NC}"
echo "Testing if 'cdrom' or 'cdd' is treated as 'cd'"
echo "Command: cdrom (should fail as command not found)"
echo "Actual output:"
echo "cdrom" | ./minishell 2>&1
echo ""

# Test 5: Test with a simple command to see if get_path works
echo -e "${YELLOW}TEST 5: Test basic command execution${NC}"
echo "Command: ls -la"
echo "Expected: Should list files"
echo "Actual output:"
echo "ls -la" | ./minishell 2>&1 | head -5
echo ""

# Test 6: Test redirect output to file
echo -e "${YELLOW}TEST 6: Test output redirection${NC}"
echo "Command: echo hello > test_output.txt"
echo "Expected: Should create file with 'hello'"
rm -f test_output.txt
echo "echo hello > test_output.txt" | ./minishell 2>&1
if [ -f test_output.txt ]; then
    echo -e "${GREEN}✅ File created${NC}"
    echo "Contents:"
    cat test_output.txt
    rm -f test_output.txt
else
    echo -e "${RED}❌ File not created${NC}"
fi
echo ""

echo "=========================================="
echo "Tests Complete"
echo "=========================================="
