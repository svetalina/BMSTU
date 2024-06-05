#!/bin/bash

echo "TEST $i"

read launch_app < pos_argc_0$i.txt
eval $launch_app

if cmp -s "pos_out_0$i.txt" "pos_testing/outfile_$i.txt"; then
    echo "Positive Test $i OK"
else
    echo "Positive Test $i FAILED"
fi
echo 