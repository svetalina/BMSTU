#!/bin/bash

gcc -std=c99 -Wall -Werror -pedantic -c mul.c
gcc -std=c99 -Wall -Werror -pedantic -c print_result.c
gcc -std=c99 -Wall -Werror -pedantic -c print_rules.c
gcc -std=c99 -Wall -Werror -pedantic -c read_float.c
gcc -std=c99 -Wall -Werror -pedantic -c read_int.c
gcc -std=c99 -Wall -Werror -pedantic -c main.c
gcc -std=c99 -Wall -Werror -pedantic -o main.exe main.o mul.o read_float.o read_int.o print_result.o print_rules.o

