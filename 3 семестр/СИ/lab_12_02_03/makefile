CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra
UFLAGS := -lcheck `pkg-config --cflags --libs check`

OUT := out/
mkdir_out := $(shell mkdir -p $(OUT))

LIB := lib/
LIB_FILES := $(wildcard $(LIB)*.c)

OBJECTS := $(LIB_FILES:$(LIB)%.c=$(LIB)%.o)
LIB_OBJECTS := $(LIB_FILES:$(LIB)%.c=lib%.dll)

FUNC_TESTS := func_tests/

UNIT_TESTS := unit_tests/
UNIT_FILES := $(wildcard $(UNIT_TESTS)*.c)
UNIT_OBJECTS := $(UNIT_FILES:$(UNIT_TESTS)%.c=$(OUT)%.o)

app: lib
	python3 interface.py 
    
func: lib
	python3 $(FUNC_TESTS)test_interface.py 

unit: lib $(UNIT_OBJECTS)
	$(CC) $(CFLAGS) -o unit_tests.exe $(UNIT_OBJECTS) $(LIB_OBJECTS) $(UFLAGS)
	./unit_tests.exe

$(OUT)%.o: $(UNIT_TESTS)%.c
	$(CC) $(CFLAGS) -I inc/ -o $@ -c $<

lib: $(LIB_OBJECTS)

lib%.dll: $(OBJECTS)
	$(CC) -shared -Wl,--subsystem,windows  -o $@ $^

$(LIB)%.o: $(LIB)%.c
	$(CC) $(CFLAGS) -fPIC -o $@ -c $<

clean:
	rm -f *.exe *.dll
	rm -r $(OUT)