#!/bin/bash

mv app.exe ./func_tests
cd func_tests
sh all_tests.sh

rm -r pos_testing/
rm -f res_0*
rm *.exe
