#!/bin/bash

echo "TEST $j"

read rc < "neg_0"$j"_out.txt"
read launch_app < "neg_0"$j"_argc.txt"
eval $launch_app

if [ $((256 + rc)) -eq  $? ]; then
    echo "Negative Test $j OK"
else
    echo "Negative Test $j FAILED"
fi
echo 