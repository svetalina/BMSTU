CC := gcc
CFLAGS := -std=gnu99 -Wall -Werror -pedantic -I inc/

SRC := src/
INC := inc/
OUT := out/
UNITC := unit_tests/

OBJS := $(OUT)main.o $(OUT)items.o $(OUT)item.o
APP = app.exe

UNIT_OBJS := $(OUT)check_main.o $(OUT)check_sort.o $(OUT)items.o $(OUT)item.o
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

$(OUT)main.o : $(SRC)main.c $(INC)items.h $(INC)item.h $(INC)errors.h $(INC)structure.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)items.o : $(SRC)items.c $(INC)items.h $(INC)item.h $(INC)errors.h $(INC)structure.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)item.o : $(SRC)item.c $(INC)item.h $(INC)errors.h $(INC)structure.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(UNIT_TEST) : $(UNIT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lcheck
	
$(OUT)check_main.o : $(UNITC)check_main.c $(INC)check_sort.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)check_sort.o : $(UNITC)check_sort.c $(INC)check_sort.h
	$(CC) $(CFLAGS) -o $@ -c $<
