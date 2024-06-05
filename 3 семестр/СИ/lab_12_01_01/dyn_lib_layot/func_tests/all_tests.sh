#!/bin/bash

mkdir -p pos_testing

for i in {1..6}; do
    export i
    sh pos_test.sh
done

for j in {1..7}; do
    export j
    sh neg_test.sh
done
