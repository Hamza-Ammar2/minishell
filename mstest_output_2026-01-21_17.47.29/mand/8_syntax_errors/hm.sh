#!/bin/bash

# Extract unique test numbers from filenames
tests=$(ls *_bash | sed -E 's/^([0-9]+)_.*/\1/' | sort -n | uniq)

for n in $tests; do
    echo "=== Test $n ==="

    if [[ -f "${n}_stdout_bash" && -f "${n}_stdout_minishell" ]]; then
        echo "-- stdout diff --"
        diff -u "${n}_stdout_bash" "${n}_stdout_minishell" || true
    else
        echo "-- stdout files missing --"
    fi

    if [[ -f "${n}_stderr_bash" && -f "${n}_stderr_minishell" ]]; then
        echo "-- stderr diff --"
        diff -u "${n}_stderr_bash" "${n}_stderr_minishell" || true
    else
        echo "-- stderr files missing --"
    fi

    echo
done

