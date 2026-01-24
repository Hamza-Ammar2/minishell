# MINISHELL TEST FAILURES - Updated January 21, 2026

Total Tests: 941
Tests Passed: 831 (88.3%)
Tests Failed: 110
Component Failures: STD_OUT: 69, STD_ERR: 29, EXIT_CODE: 33

## CRITICAL - SEGMENTATION FAULTS (8 tests - Priority 1)

### REDIR Segfaults
- **REDIR 89** (Test 880, line 247): `/bin/echo 1 > tmp_redir_out tmp_redir_out_file1`
  Exit: minishell(139) vs bash(0) - SEGFAULT
  
- **REDIR 90** (Test 881, line 250): `/bin/grep 1 < inputfile`
  Exit: minishell(139) vs bash(0) - SEGFAULT
  STD_ERR also fails
  
- **REDIR 91** (Test 882, line 253): `/bin/grep 1 < NO_SUCH_FILE`  
  Exit: minishell(139) vs bash(0) - SEGFAULT

### PARSING HELL Segfaults
- **PARSING_HELL 3** (line 10): SEGFAULT - Exit: minishell(139) vs bash(0), STD_ERR fails
- **PARSING_HELL 4** (line 14): SEGFAULT - Exit: minishell(139) vs bash(0)
- **PARSING_HELL 16** (line 52): SEGFAULT - Exit: minishell(139) vs bash(1), STD_ERR fails
- **PARSING_HELL 17** (line 54): SEGFAULT - Exit: minishell(139) vs bash(0)
- **PARSING_HELL 18** (line 58): SEGFAULT - Exit: minishell(139) vs bash(0)
- **PARSING_HELL 19** (line 62): SEGFAULT - Exit: minishell(139) vs bash(0)

---

## QUOTE & VARIABLE EXPANSION (~50 tests - Priority 2)

### COMPARE PARSING (11 failures)
- Tests 11, 12, 14, 15 (lines 26, 28, 32, 34): STD_OUT failures  
- Tests 24-30 (lines 52, 54, 56, 58, 60, 62, 64): STD_OUT failures
- Pattern: Likely $"..." and $'...' quote expansion issues

### VARIABLES (24 failures)
- Tests 15-20 (lines 40, 42, 44, 46, 48, 50): STD_OUT failures - Quote expansion
- Tests 25-26 (lines 60, 62): STD_OUT failures
- Test 28 (line 66): STD_OUT failure
- Test 43 (line 120): STD_OUT and STD_ERR failures
- Tests 45-53 (lines 130, 133, 136, 139, 142, 145, 148, 151, 154): STD_OUT failures
- Tests 56-58 (lines 163, 166, 169): STD_OUT failures

### CORRECTION (16 failures)
- Tests 60-61 (lines 129, 131): STD_OUT failures
- Tests 65-70 (lines 139, 141, 143, 145, 147, 149): STD_OUT failures - Quote expansion
- Tests 75-76 (lines 159, 161): STD_OUT failures
- Test 78 (line 165): STD_OUT failure
- Tests 110-111 (lines 261, 265): STD_OUT/STD_ERR/EXIT failures (127 vs 0)
- Test 113 (line 273): STD_ERR/EXIT failure (127 vs 0)

---

## EXIT CODE ISSUES (~20 tests - Priority 3)

### BUILTINS (36 failures)
Export/Env display:
- Tests 13-14, 16-17 (lines 31, 33, 37, 39): STD_OUT failures
- Tests 27-33 (lines 59, 61, 63, 65, 67, 69, 71): STD_OUT failures

Exit code mismatches:
- Test 102 (line 233): STD_ERR/EXIT (1 vs 0)
- Test 105 (line 239): STD_ERR failure only
- Test 107 (line 243): STD_ERR failure only
- Test 123 (line 294): STD_ERR failure only
- Test 140 (line 360): EXIT (1 vs 127)
- Test 150 (line 390): STD_OUT failure
- Test 165 (line 420): EXIT (1 vs 2)
- Test 170 (line 430): EXIT (1 vs 2)
- Test 185 (line 460): EXIT (1 vs 2)
- Test 200 (line 490): STD_ERR/EXIT (1 vs 0)
- Test 224 (line 552): STD_ERR/EXIT (0 vs 127)
- Test 231 (line 566): STD_ERR/EXIT (0 vs 2)

### SYNTAX ERRORS (6 failures)
- Tests 15-16 (lines 33, 35): EXIT (1 vs 127)
- Tests 20-22 (lines 43, 46, 49): EXIT (0 vs 2)

### SCMD (2 failures)
- Test 7 (line 19): STD_ERR/EXIT (2 vs 0)
- Test 26 (line 84): EXIT (1 vs 127)

### PARSING HELL (non-segfault failures - 10 tests)
- Test 30 (line 96): STD_OUT failure
- Test 54 (line 159): STD_ERR/EXIT (127 vs 0)
- Test 57 (line 167): STD_ERR/EXIT (127 vs 0)
- Test 77 (line 216): STD_OUT/STD_ERR/EXIT (127 vs 0)
- Test 78 (line 219): STD_OUT failure
- Tests 112-114 (lines 297, 299, 301): STD_OUT failures
- Test 123 (line 319): EXIT (2 vs 127)

---

## PIPELINE & STDERR ISSUES (~10 tests - Priority 4)

### PIPELINES (7 failures)
- Test 16 (line 34): STD_OUT failure
- Test 29 (line 96): STD_OUT/EXIT (0 vs 2)
- Test 35 (line 142): EXIT (2 vs 1)
- Tests 36-37 (lines 144, 147): STD_ERR failures
- Tests 41-42 (lines 166, 171): STD_ERR failures

### PATH FAILS (2 failures)
- Test 11 (line 43): STD_ERR failure
- Test 12 (line 47): STD_OUT failure

### WILD (5 failures)
- Test 6 (line 18): STD_OUT/STD_ERR failures
- Test 7 (line 22): STD_ERR failure
- Test 10 (line 30): STD_OUT/STD_ERR failures
- Tests 13-15 (lines 46, 49, 52): STD_ERR failures

---

## RECOMMENDATIONS

1. **IMMEDIATE**: Fix segfaults in redirection and parsing
   - Focus on REDIR tests with file operations
   - Debug PARSING_HELL edge cases
   - Run with valgrind to find memory issues

2. **HIGH PRIORITY**: Implement proper quote expansion
   - $"..." ANSI-C quoting
   - $'...' locale-specific expansion
   - Test with export display

3. **MEDIUM PRIORITY**: Standardize exit codes
   - Command not found: should be 127
   - Builtin errors: typically 1 or 2
   - Syntax errors: should be 2

4. **LOW PRIORITY**: Error message formatting
   - Match bash STD_ERR output format
   - Wildcard error messages
   - Path resolution error messages

---

## TESTING NOTES

- Tests use `echo -n "$INPUT" | $MINISHELL_PATH/$EXECUTABLE` format
- Some segfaults may be state-dependent (previous test state)
- Manual testing shows some tests pass individually but fail in sequence
- Valgrind shows no leaks but segfaults need investigation
