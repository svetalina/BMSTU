#!/bin/bash

gcc -std=c99 -Wall -Werror -g3 --coverage -pedantic -c item.c
gcc -std=c99 -Wall -Werror -g3 --coverage -pedantic -c items.c
gcc -std=c99 -Wall -Werror -g3 --coverage -pedantic -c main.c
gcc -std=c99 -Wall -Werror -g3 --coverage -pedantic -o app.exe main.o item.o items.o

