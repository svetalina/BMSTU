#!/bin/bash

mkdir -p pos_testing

for i in {1..3}; do
    export i
    sh pos_test.sh
done

for j in {1..9}; do
    export j
    sh neg_test.sh
done
