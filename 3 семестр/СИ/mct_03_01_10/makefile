CC := gcc
FLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra

CFILES = $(wildcard *.c)

include $(wildcard *.d)

debug: FLAGS += -g3 --coverage
debug: release

release: $(patsubst %.c, %.o, $(CFILES))
	$(CC) $(FLAGS) -o app.exe $^
	
%.o: %.c
	$(CC) $(FLAGS) -c $<