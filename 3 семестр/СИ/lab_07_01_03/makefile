CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -I inc/

SRC := src/
INC := inc/
OUT := out/
UNITC := unit_tests/

OBJS := $(OUT)main.o $(OUT)element.o $(OUT)array.o $(OUT)file.o
APP = app.exe

UNIT_OBJS := $(OUT)check_main.o $(OUT)check_key.o $(OUT)check_sort.o $(OUT)array.o $(OUT)element.o
UNIT_TEST = unit_tests.exe

mkdir_out := $(shell mkdir -p $(OUT))

release: release.lastbuildstate | $(APP) 

debug: CFLAGS += -g3 --coverage
debug: debug.lastbuildstate | $(APP)

debug.lastbuildstate:
	touch debug.lastbuildstate
	rm -f app.exe out/*.o
	rm -f release.lastbuildstate
	
release.lastbuildstate:
	touch release.lastbuildstate
	rm -f app.exe out/*.o
	rm -f debug.lastbuildstate

func: release
	bash make_func.sh 
	
unit: $(UNIT_TEST)
	./$(UNIT_TEST)

clean :
	rm -r out
	rm -f *.exe
	rm -f *.lastbuildstate

$(APP) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OUT)main.o : $(SRC)main.c $(INC)element.h $(INC)array.h $(INC)file.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)file.o : $(SRC)file.c $(INC)file.h
	$(CC) $(CFLAGS) -o $@ -c $<


$(UNIT_TEST) : $(UNIT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lcheck
	
$(OUT)check_main.o : $(UNITC)check_main.c $(INC)check_sort.h $(INC)check_key.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)check_sort.o : $(UNITC)check_sort.c $(INC)check_sort.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)check_key.o : $(UNITC)check_key.c $(INC)check_key.h
	$(CC) $(CFLAGS) -o $@ -c $<


$(OUT)element.o : $(SRC)element.c $(INC)element.h
	$(CC) $(CFLAGS) -o $@ -c $<
    
$(OUT)array.o : $(SRC)array.c $(INC)array.h
	$(CC) $(CFLAGS) -o $@ -c $<
    