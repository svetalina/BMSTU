#!/bin/bash

gcc -std=c99 -Wall -Werror -pedantic -c item.c
gcc -std=c99 -Wall -Werror -pedantic -c items.c
gcc -std=c99 -Wall -Werror -pedantic -c main.c
gcc -std=c99 -Wall -Werror -pedantic -o app.exe main.o item.o items.o

