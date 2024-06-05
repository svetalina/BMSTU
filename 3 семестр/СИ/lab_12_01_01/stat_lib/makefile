CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -I inc/
UFLAGS := -lcheck `pkg-config --cflags --libs check`

LIB := lib/
LIB_FILES := $(wildcard $(LIB)*.c)
LIB_OBJECTS := $(LIB_FILES:$(LIB)%.c=$(LIB)lib%.a)

OUT := out/
mkdir_out := $(shell mkdir -p $(OUT))

UNIT_TESTS := unit_tests/
UNIT_FILES := $(wildcard $(UNIT_TESTS)*.c)
UNIT_OBJECTS := $(UNIT_FILES:$(UNIT_TESTS)%.c=$(OUT)%.o)

app: lib
	$(CC) $(CFLAGS) main.c $(LIB_OBJECTS) -o app.exe

unit: lib $(UNIT_OBJECTS)
	$(CC) $(CFLAGS) -o unit_app.exe $(UNIT_OBJECTS) $(LIB_OBJECTS) $(UFLAGS)
	./unit_app.exe

$(OUT)%.o: $(UNIT_TESTS)%.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
func: app
	bash make_func.sh 
	
lib: $(LIB_OBJECTS)

$(LIB)lib%.a: $(LIB)%.o
	ar rc $@ $<

$(LIB)%.o: $(LIB)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -r $(OUT)
	rm -f $(LIB)*.a
	rm -f *.exe