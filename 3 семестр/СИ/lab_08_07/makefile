CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -I inc/

SRC := src/
INC := inc/
OUT := out/
UNITC := unit_tests/

OBJS := $(OUT)main.o $(OUT)matrices.o $(OUT)matrix.o $(OUT)row_column.o
APP = app.exe

UNIT_OBJS := $(OUT)check_main.o $(OUT)check_mul.o $(OUT)check_do_square.o $(OUT)check_find_pos_min.o $(OUT)check_equalization.o $(OUT)matrix.o $(OUT)row_column.o
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

$(OUT)main.o : $(SRC)main.c $(INC)matrices.h $(INC)matrix.h $(INC)row_column.h $(INC)errors.h $(INC)structure.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)matrices.o : $(SRC)matrices.c $(INC)matrices.h $(INC)errors.h $(INC)structure.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)matrix.o : $(SRC)matrix.c $(INC)matrix.h $(INC)errors.h $(INC)structure.h
	$(CC) $(CFLAGS) -o $@ -c $<
    
$(OUT)row_column.o : $(SRC)row_column.c $(INC)row_column.h $(INC)errors.h $(INC)structure.h
	$(CC) $(CFLAGS) -o $@ -c $<
    

$(UNIT_TEST) : $(UNIT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lcheck
	
$(OUT)check_main.o : $(UNITC)check_main.c $(INC)check_mul.h $(INC)check_do_square.h $(INC)check_find_pos_min.h $(INC)check_equalization.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)check_mul.o : $(UNITC)check_mul.c $(INC)check_mul.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)check_do_square.o : $(UNITC)check_do_square.c $(INC)check_do_square.h
	$(CC) $(CFLAGS) -o $@ -c $<
    
$(OUT)check_find_pos_min.o : $(UNITC)check_find_pos_min.c $(INC)check_find_pos_min.h
	$(CC) $(CFLAGS) -o $@ -c $<
    
$(OUT)check_equalization.o : $(UNITC)check_equalization.c $(INC)check_equalization.h
	$(CC) $(CFLAGS) -o $@ -c $<




