CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -I inc/
UFLAGS := -lcheck -lpthread

SRC := src/
CFILES := $(wildcard $(SRC)*.c)
INC := inc/
HFILES := $(wildcard $(INC)/*.h)
UNITC := unit_tests/
UFILES := $(wildcard $(UNITC)*.c)
OUT := out/

OBJECTS := $(CFILES:$(SRC)%.c=$(OUT)%.o)
UNIT_OBJECTS := $(UFILES:$(UNITC)%.c=$(OUT)%.o)
UNIT_OBJECTS += $(filter-out $(OUT)main.o,$(OBJECTS))

APP = app.exe
UNIT_APP = unit_tests.exe

mkdir_out := $(shell mkdir -p $(OUT))

release: release.lastbuildstate | $(APP)

debug: CFLAGS += -g3 -ggdb
debug: debug.lastbuildstate | $(APP)

debug.lastbuildstate:
	touch debug.lastbuildstate
	rm -f *.exe out/*.o
	rm -f release.lastbuildstate
	
release.lastbuildstate:
	touch release.lastbuildstate
	rm -f *exe out/*.o
	rm -f debug.lastbuildstate

func: $(APP)
	bash make_func.sh 

unit: $(UNIT_APP)
	./$(UNIT_APP)

clean :
	rm -r out/
	rm -f *.exe
	rm -f *.lastbuildstate

$(APP): $(OBJECTS)
	$(CC) $^ -o $@

$(UNIT_APP): $(UNIT_OBJECTS)
	$(CC) $(UNIT_OBJECTS) -o $@ $(UFLAGS)

$(OUT)%.o: $(SRC)%.c $(HFILES)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)%.o: $(UNITC)%.c $(HFILES)
	$(CC) $(CFLAGS) $(UFLAGS) -c $< -o $@