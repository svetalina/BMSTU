#!/bin/bash

for i in {1..3}; do
    echo "TEST $i"
    
    read launch_app < func_tests/pos_argc_0$i.txt
    eval $launch_app > func_tests/pos_testing/outfile_0$i.txt

    if cmp -s "func_tests/pos_out_0$i.txt" "func_tests/pos_testing/outfile_0$i.txt"; then
        echo "Positive Test $i OK"
    else
        echo "Positive Test $i FAILED"
    fi
    echo
done

for i in {1..11}; do
    echo "TEST $i"
    
    if [ "$i" -gt 9 ]; then
        read rc < func_tests/neg_out_$i.txt
        read launch_app < func_tests/neg_argc_$i.txt
    else 
        read rc < func_tests/neg_out_0$i.txt
        read launch_app < func_tests/neg_argc_0$i.txt
    fi
    
    eval $launch_app
    
    if [ $? -eq $((256 + rc)) ]; then
        echo "Negative Test $i OK"
    else
        echo "Negative Test $i FAILED"
    fi
    echo
done
