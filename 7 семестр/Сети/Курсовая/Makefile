FLAGS = -lws2_32 -lpthread

release: clean
	gcc -o server.exe ./src/*.c $(FLAGS)
	
clean:
	rm -f *.exe
	
.PHONY: clean
