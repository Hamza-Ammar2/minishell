#!/usr/bin/env python3
"""
Generate still_required.txt from mstest output in proper format
"""
import re
import subprocess
import os
from datetime import datetime

MAND_DIR = "/home/lpons/Desktop/Commoncore/Minishell/mand"
MINISHELL = "/home/lpons/Desktop/Commoncore/Minishell/minishell"

def parse_test_output():
    """Parse mstest output to extract failures"""
    with open('/tmp/mstest_output.txt', 'r', encoding='utf-8') as f:
        content = f.read()
    
    failures = []
    current_section = None
    
    lines = content.split('\n')
    for i, line in enumerate(lines):
        # Detect section
        if re.search(r'#\s+([A-Z\s]+)\s+#', line):
            match = re.search(r'#\s+([A-Z\s]+)\s+#', line)
            current_section = match.group(1).strip()
            continue
        
        # Detect failures (contains at least one ❌)
        if re.match(r'\s+\d+:', line) and '❌' in line:
            # Extract test number and file location
            match = re.search(r'(\d+):\s+.*?(/home/\S+\.sh):(\d+)', line)
            if match:
                test_num = match.group(1)
                file_path = match.group(2)
                line_num = int(match.group(3))
                file_name = os.path.basename(file_path)
                
                # Check for segfault in previous line
                segfault = i > 0 and 'Segmentation fault' in lines[i-1]
                
                failures.append({
                    'section': current_section or 'UNKNOWN',
                    'test_num': test_num,
                    'file': file_name,
                    'line': line_num,
                    'full_line': line,
                    'segfault': segfault
                })
    
    return failures

def get_test_command(file_path, line_num):
    """Extract the actual test command from the test file"""
    try:
        with open(file_path, 'r') as f:
            lines = f.readlines()
        
        if line_num <= len(lines):
            # The command is at the line number
            cmd = lines[line_num - 1].strip()
            # Remove any leading test framework code
            cmd = re.sub(r'^.*?(?:echo|printf).*?[\'"](.*)[\'"].*$', r'\1', cmd)
            return cmd
        return None
    except:
        return None

def run_command_comparison(cmd):
    """Run command in both bash and minishell and compare"""
    if not cmd or cmd.startswith('#'):
        return None
    
    # Run in bash
    try:
        bash_result = subprocess.run(
            ['bash', '-c', f'echo -n "{cmd}" | bash'],
            capture_output=True,
            text=True,
            timeout=2
        )
        bash_out = bash_result.stdout
        bash_err = bash_result.stderr
        bash_exit = bash_result.returncode
    except Exception as e:
        bash_out = f"ERROR: {e}"
        bash_err = ""
        bash_exit = -1
    
    # Run in minishell
    try:
        ms_result = subprocess.run(
            ['bash', '-c', f'echo -n "{cmd}" | {MINISHELL}'],
            capture_output=True,
            text=True,
            timeout=2
        )
        ms_out = ms_result.stdout
        ms_err = ms_result.stderr
        ms_exit = ms_result.returncode
    except Exception as e:
        ms_out = f"ERROR: {e}"
        ms_err = ""
        ms_exit = -1
    
    return {
        'bash_out': bash_out,
        'bash_err': bash_err,
        'bash_exit': bash_exit,
        'ms_out': ms_out,
        'ms_err': ms_err,
        'ms_exit': ms_exit
    }

def generate_still_required():
    """Generate the complete still_required.txt file"""
    failures = parse_test_output()
    
    output = []
    output.append("=" * 80)
    output.append("MINISHELL TEST FAILURES - COMPREHENSIVE DOCUMENTATION")
    output.append("=" * 80)
    output.append(f"Generated: {datetime.now().strftime('%B %d, %Y')}")
    output.append(f"Total Failures Documented: {len(failures)}")
    output.append("")
    output.append("Format for each failure:")
    output.append("  Test: <exact command>")
    output.append("  Bash output: <what bash produces>")
    output.append("  Your output: <what your minishell produces>")
    output.append("  Difference likely caused by: <explanation>")
    output.append("  Required by subject: <YES/NO/BORDERLINE>")
    output.append("=" * 80)
    output.append("")
    
    # Group by file
    by_file = {}
    for f in failures:
        if f['file'] not in by_file:
            by_file[f['file']] = []
        by_file[f['file']].append(f)
    
    failure_count = 1
    for file_name in sorted(by_file.keys()):
        output.append("")
        output.append("=" * 80)
        output.append(f"FILE: {file_name}")
        output.append("=" * 80)
        output.append("")
        
        for failure in by_file[file_name]:
            output.append(f"🟪--- FAILURE #{failure_count} ---🟪")
            output.append(f"Category: {failure['section']}")
            output.append(f"Test Number: {failure['test_num']}")
            output.append(f"Test File: {file_name}:line{failure['line']}")
            
            # Try to get the actual command
            file_path = os.path.join(MAND_DIR, file_name)
            cmd = get_test_command(file_path, failure['line'])
            
            if failure['segfault']:
                output.append("⚠️  SEGMENTATION FAULT - Exit Code 139")
                output.append("")
                output.append("Test:")
                output.append(f"  {cmd if cmd else '<unable to extract command>'}")
                output.append("")
                output.append("Result:")
                output.append("  Minishell: SEGFAULT (exit 139)")
                output.append("  Bash: Normal execution (exit 0)")
                output.append("")
                output.append("Difference likely caused by:")
                output.append("  Memory corruption, NULL pointer dereference, or buffer overflow")
                output.append("")
                output.append("Required by subject: YES - Must not crash")
            else:
                output.append("")
                output.append("Test:")
                output.append(f"  {cmd if cmd else '<unable to extract command>'}")
                output.append("")
                output.append("[To be filled: Run commands to get actual output]")
                output.append("")
                output.append("Bash output:")
                output.append("  [TODO]")
                output.append("")
                output.append("Your output:")
                output.append("  [TODO]")
                output.append("")
                output.append("Difference likely caused by:")
                output.append("  [TODO]")
                output.append("")
                output.append("Required by subject: [TODO]")
            
            output.append("")
            failure_count += 1
    
    return '\n'.join(output)

if __name__ == '__main__':
    content = generate_still_required()
    
    output_file = '/home/lpons/Desktop/Commoncore/Minishell/resources/still_required_NEW.txt'
    with open(output_file, 'w') as f:
        f.write(content)
    
    print(f"Generated {output_file}")
    print(f"Total failures documented: {content.count('🟪--- FAILURE')}")
