#!/bin/bash

echo "TEST $i"

if [ "$i" -gt 9 ]; then
        read launch_app < "pos_"$i"_argc.txt"
        eval $launch_app > pos_testing/"res_"$i".txt"
        
        if diff -b "pos_"$i"_out.txt" pos_testing/"res_"$i".txt"; then
            echo "Positive Test $i OK"
        else
            echo "Positive Test $i FAILED"
        fi
    else 
        read launch_app < "pos_0"$i"_argc.txt"
        eval $launch_app > pos_testing/"res_0"$i".txt"
        
        if diff -b "pos_0"$i"_out.txt" pos_testing/"res_0"$i".txt"; then
            echo "Positive Test $i OK"
        else
            echo "Positive Test $i FAILED"
        fi
    fi
echo
