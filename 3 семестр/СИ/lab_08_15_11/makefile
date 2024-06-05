CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -I inc/

SRC := src/
INC := inc/
OUT := out/
UNITC := unit_tests/

HEAD := $(INC)errors.h $(INC)structure.h
OBJS := $(OUT)main.o $(OUT)matrix.o $(OUT)file.o
APP = app.exe

UNIT_OBJS := $(OUT)check_main.o $(OUT)check_addition.o $(OUT)check_multiplication.o  $(OUT)check_inversion.o $(OUT)matrix.o $(OUT)file.o
UNIT_TEST = unit_tests.exe

mkdir_out := $(shell mkdir -p $(OUT))

release: release.lastbuildstate | $(APP)

debug: CFLAGS += -g3 -ggdb --coverage
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
	./$^

clean :
	rm -r out
	rm -f *.exe
	rm -f *.lastbuildstate

$(APP) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OUT)main.o : $(SRC)main.c $(INC)matrix.h $(INC)file.h $(HEAD)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)matrix.o : $(SRC)matrix.c $(INC)matrix.h $(INC)file.h $(HEAD)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)file.o : $(SRC)file.c $(INC)file.h $(HEAD)
	$(CC) $(CFLAGS) -o $@ -c $<

$(UNIT_TEST) : $(UNIT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lcheck
	
$(OUT)check_main.o : $(UNITC)check_main.c $(INC)check_multiplication.h $(INC)check_addition.h $(INC)check_inversion.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)check_addition.o : $(UNITC)check_addition.c $(INC)check_addition.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)check_multiplication.o : $(UNITC)check_multiplication.c $(INC)check_multiplication.h
	$(CC) $(CFLAGS) -o $@ -c $<
   
$(OUT)check_inversion.o : $(UNITC)check_inversion.c $(INC)check_inversion.h
	$(CC) $(CFLAGS) -o $@ -c $<



