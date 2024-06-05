CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic

CFILES := $(wildcard *.c)

INCLUDES := $(wildcard *.h)

OBJECTS := $(CFILES:%.c=%.o)

APP = app.exe

.PHONY : clean run

$(APP): $(OBJECTS)
	$(CC) $^ -o $@


%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@$(RM) *.o *.exe *.gv *.png
 