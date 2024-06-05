#!/bin/bash

echo "TEST $j"

read rc < neg_out_0$i.txt

read launch_app < neg_argc_0$i.txt
eval $launch_app

if [ $rc -eq  $? ]; then
    echo "Negative Test $j OK"
else
    echo "Negative Test $j FAILED"
fi
echo