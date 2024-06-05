#!/bin/bash

echo "TEST $j"

if  [ $j -gt 9 ]; then
        read rc < "neg_"$j"_out.txt"
        read launch_app < "neg_"$j"_argc.txt"
    else 
        read rc < "neg_0"$j"_out.txt"
        read launch_app < "neg_0"$j"_argc.txt"
    fi
    
eval $launch_app

if [ $rc -eq  $? ]; then
    echo "Negative Test $j OK"
else
    echo "Negative Test $j FAILED"
fi
echo 