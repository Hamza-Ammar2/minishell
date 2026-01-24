#!/usr/bin/env python3
"""
Parse mstest output and generate structured failure report
"""
import re
import sys

def parse_test_output(file_path):
    """Parse mstest output file and extract failures"""
    failures = []
    current_section = None
    
    with open(file_path, 'r') as f:
        lines = f.readlines()
    
    i = 0
    while i < len(lines):
        line = lines[i]
        
        # Detect section headers
        section_match = re.search(r'#\s+([A-Z\s]+)\s+#', line)
        if section_match:
            current_section = section_match.group(1).strip()
            i += 1
            continue
        
        # Detect test lines with failures
        test_match = re.match(r'\s+(\d+):\s+STD_OUT: (✅|❌)\s+STD_ERR: (✅|❌)\s+EXIT_CODE: (✅|❌)(?:\s+\[\s+minishell\((\d+)\)\s+bash\((\d+)\)\s+\])?\s+(.+)$', line)
        
        if test_match:
            test_num = test_match.group(1)
            stdout = test_match.group(2)
            stderr = test_match.group(3)
            exitcode = test_match.group(4)
            minishell_exit = test_match.group(5) if test_match.group(5) else None
            bash_exit = test_match.group(6) if test_match.group(6) else None
            file_line = test_match.group(7).strip()
            
            # Check if any component failed
            if stdout == '❌' or stderr == '❌' or exitcode == '❌':
                failure = {
                    'section': current_section,
                    'test_num': test_num,
                    'stdout_fail': stdout == '❌',
                    'stderr_fail': stderr == '❌',
                    'exitcode_fail': exitcode == '❌',
                    'minishell_exit': minishell_exit,
                    'bash_exit': bash_exit,
                    'file_line': file_line
                }
                
                # Check for segfault in previous lines
                if i > 0 and 'Segmentation fault' in lines[i-1]:
                    failure['segfault'] = True
                else:
                    failure['segfault'] = False
                
                failures.append(failure)
        
        i += 1
    
    return failures

def print_failures_summary(failures):
    """Print summary of failures by category"""
    print(f"\n=== TOTAL FAILURES: {len(failures)} ===\n")
    
    # Group by section
    by_section = {}
    for f in failures:
        section = f['section'] if f['section'] else 'UNKNOWN'
        if section not in by_section:
            by_section[section] = []
        by_section[section].append(f)
    
    # Print by section
    for section, fails in sorted(by_section.items()):
        print(f"\n## {section} ({len(fails)} failures)")
        for f in fails:
            issues = []
            if f['stdout_fail']:
                issues.append('STDOUT')
            if f['stderr_fail']:
                issues.append('STDERR')
            if f['exitcode_fail']:
                issues.append(f"EXIT({f['minishell_exit']} vs {f['bash_exit']})")
            if f['segfault']:
                issues.append('SEGFAULT')
            
            print(f"  Test {f['test_num']}: {', '.join(issues)}")
            print(f"    {f['file_line']}")

def print_segfaults(failures):
    """Print only segfault failures"""
    segfaults = [f for f in failures if f['segfault']]
    print(f"\n=== SEGFAULTS: {len(segfaults)} ===\n")
    for f in segfaults:
        print(f"{f['section']} Test {f['test_num']}: {f['file_line']}")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: ./parse_test_results.py <mstest_output.txt>")
        sys.exit(1)
    
    failures = parse_test_output(sys.argv[1])
    print_failures_summary(failures)
    print_segfaults(failures)
    
    print(f"\n\nTotal test failures: {len(failures)}")
    print(f"Tests passed: {941 - len(failures)} / 941")
