#!/bin/bash

echo "TEST $i"

read launch_app < "pos_0"$i"_argc.txt"
eval $launch_app

if cmp -s "pos_0"$i"_out.txt" "res_0"$i".txt"; then
    echo "Positive Test $i OK"
else
    echo "Positive Test $i FAILED"
fi
echo 