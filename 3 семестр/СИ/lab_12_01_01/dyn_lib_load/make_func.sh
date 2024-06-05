#!/bin/bash

mv app.exe ./func_tests
mv libarray.dll ./func_tests
mv libfile.dll ./func_tests
cd func_tests
sh all_tests.sh

rm -r pos_testing
rm *.exe *.dll
