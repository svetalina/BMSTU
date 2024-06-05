#!/bin/bash

mkdir -p pos_testing

for i in {1..8}; do
    export i
    sh pos_test.sh
done

for j in {1..10}; do
    export j
    sh neg_test.sh
done
