gcc -std=c99 -Wall -Werror -pedantic -c read.c
gcc -std=c99 -Wall -Werror -pedantic -c print.c
gcc -std=c99 -Wall -Werror -pedantic -c stack_array.c
gcc -std=c99 -Wall -Werror -pedantic -c stack_list.c
gcc -std=c99 -Wall -Werror -pedantic -c comparison_stacks.c
gcc -std=c99 -Wall -Werror -pedantic -c main.c
gcc -std=c99 -Wall -Werror -pedantic -o main.exe read.o print.o stack_array.o stack_list.o comparison_stacks.o main.o
