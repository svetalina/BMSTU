CC := gcc
CFILES := $(wildcard *.c)

FLAGS := -std=c99 -Wall 

include $(wildcard *.d)


build: $(patsubst %.c, %.o, $(CFILES))
	$(CC) $(FLAGS) -o app.exe $^

%.o: %.c
	$(CC) $(FLAGS) -c $<


run: build
	./app.exe < in.txt > out.txt


clean:
	rm -f *.exe *.o *.d