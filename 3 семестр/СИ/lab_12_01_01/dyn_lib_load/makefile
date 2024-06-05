CC := gcc
CFLAGS := -std=c99 -Wall -I inc/ -ggdb
UFLAGS := -lcheck `pkg-config --cflags --libs check`

LIB := lib/
LIB_FILES := $(wildcard $(LIB)*.c)
LIB_OBJECTS := $(LIB_FILES:$(LIB)%.c=lib%.dll)

OUT := out/
mkdir_out := $(shell mkdir -p $(OUT))

UNIT_TESTS := unit_tests/
UNIT_FILES := $(wildcard $(UNIT_TESTS)*.c)
UNIT_OBJECTS := $(UNIT_FILES:$(UNIT_TESTS)%.c=$(OUT)%.o)

app: lib
	$(CC) $(CFLAGS) main.c -o app.exe

unit: lib $(UNIT_OBJECTS)
	$(CC) $(CFLAGS) -o unit_tests.exe $(UNIT_OBJECTS) $(UFLAGS)
	./unit_tests.exe

$(OUT)%.o: $(UNIT_TESTS)%.c
	$(CC) $(CFLAGS) -o $@ -c $<
	 
func: app
	bash make_func.sh 
	
lib: $(LIB_OBJECTS)

lib%.dll: $(LIB)%.o
	$(CC) -shared $< -Wl,--subsystem,windows -o $@

$(LIB)%.o: $(LIB)%.c
	$(CC) $(CFLAGS)  -o $@ -c $<
	
clean:
	rm -r $(OUT)
	rm -f $(LIB)*.o
	rm -f *.exe *.o *.dll