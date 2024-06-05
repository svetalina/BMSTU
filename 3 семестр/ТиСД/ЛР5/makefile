CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic -ggdb -O0
CFILES = $(wildcard *.c)

include $(wildcard *.d)

release: $(patsubst %.c, %.o, $(CFILES))
	$(CC) $(FLAGS) -o app.exe $^
	
%.o: %.c head.h
	$(CC) $(FLAGS) -c $<
    
