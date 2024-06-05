#!/bin/bash

echo "TEST $i"

read launch_app < "pos_0"$i"_argc.txt"
eval $launch_app > "pos_testing/outfile_$i.txt"

if diff -b "pos_0"$i"_out.txt" "pos_testing/outfile_$i.txt"; then
    echo "Positive Test $i OK"
else
    echo "Positive Test $i FAILED"
fi
echo 