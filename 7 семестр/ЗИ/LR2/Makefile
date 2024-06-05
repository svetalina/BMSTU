FLAGS = -o

.PHONY: clean run

release: clean
	gcc ./src/*.c $(FLAGS) app.exe
	
run: release
	./app.exe input.txt

clean:
	rm -f *.exe _*.txt
