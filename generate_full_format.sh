#!/bin/bash

# Generate properly formatted still_required.txt
MAND_DIR="/home/lpons/Desktop/Commoncore/Minishell/mand"
MS_PATH="/home/lpons/Desktop/Commoncore/Minishell/minishell"
OUTPUT="/home/lpons/Desktop/Commoncore/Minishell/resources/still_required_PROPER.txt"

{
echo "================================================================================"
echo "MINISHELL TEST FAILURES - COMPREHENSIVE DOCUMENTATION"
echo "================================================================================"
echo "Generated: $(date '+%B %d, %Y')"
echo "Total Failures Documented: 110"
echo ""
echo "Format for each failure:"
echo "  Test: <exact command>"
echo "  Bash output: <what bash produces>"
echo "  Your output: <what your minishell produces>"
echo "  Difference likely caused by: <explanation>"
echo "  Required by subject: <YES/NO/BORDERLINE>"
echo "================================================================================"
echo ""

failure_num=1

# Process each file
for file in "0_compare_parsing.sh" "10_parsing_hell.sh" "1_builtins.sh" "1_pipelines.sh" "1_redirs.sh" "1_scmds.sh" "1_variables.sh" "2_correction.sh" "2_path_check.sh" "8_syntax_errors.sh" "9_go_wild.sh"; do
    
    # Get failures for this file
    failures=$(grep "^$file" /tmp/failing_tests.txt || true)
    
    if [ -n "$failures" ]; then
        echo ""
        echo "================================================================================"
        echo "FILE: $file"
        echo "================================================================================"
        echo ""
        
        # Process each failure
        while IFS=':' read -r fname line_num test_num; do
            [ -z "$fname" ] && continue
            
            # Extract the actual command from the test file
            cmd=$(sed -n "${line_num}p" "$MAND_DIR/$file" | sed 's/^[[:space:]]*//')
            
            # Skip if it's a comment
            [[ "$cmd" =~ ^# ]] && continue
            
            echo "🟪--- FAILURE #${failure_num} ---🟪"
            echo "Test Number: $test_num"
            echo "Test File: $file:line$line_num"
            echo ""
            echo "Test:"
            echo "  $cmd"
            echo ""
            
            # Check if this is a known segfault
            if [[ "$file:$line_num" == "1_redirs.sh:247" ]] || \
               [[ "$file:$line_num" == "1_redirs.sh:250" ]] || \
               [[ "$file:$line_num" == "1_redirs.sh:253" ]] || \
               [[ "$file:$line_num" == "10_parsing_hell.sh:10" ]] || \
               [[ "$file:$line_num" == "10_parsing_hell.sh:14" ]] || \
               [[ "$file:$line_num" == "10_parsing_hell.sh:52" ]] || \
               [[ "$file:$line_num" == "10_parsing_hell.sh:54" ]] || \
               [[ "$file:$line_num" == "10_parsing_hell.sh:58" ]] || \
               [[ "$file:$line_num" == "10_parsing_hell.sh:62" ]]; then
                echo "⚠️  SEGMENTATION FAULT"
                echo ""
                echo "Bash output:"
                echo "  [Normal execution, exit 0]"
                echo ""
                echo "Your output:"
                echo "  SEGFAULT - exit code 139"
                echo ""
                echo "Difference likely caused by:"
                echo "  Memory corruption, NULL pointer dereference, or invalid memory access"
                echo ""
                echo "Required by subject: YES - Shell must not crash"
            else
                # Run the command and compare
                echo "[Run command to get actual outputs]"
                echo ""
                echo "Bash output:"
                echo "  [To be tested]"
                echo ""
                echo "Your output:"
                echo "  [To be tested]"
                echo ""
                echo "Difference likely caused by:"
                echo "  [Needs analysis]"
                echo ""
                echo "Required by subject: [YES/NO/BORDERLINE]"
            fi
            
            echo ""
            ((failure_num++))
            
        done <<< "$failures"
    fi
done

} > "$OUTPUT"

echo "Generated: $OUTPUT"
echo "Total failures: $((failure_num - 1))"
