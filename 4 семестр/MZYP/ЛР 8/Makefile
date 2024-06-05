CC = gcc
CFLAGS = -Wall -Werror

SRC_DIR = ./src
OUT_DIR = ./out

APP = app.exe

.PHONY : clean run

$(APP): $(OUT_DIR)/main.o $(OUT_DIR)/strcopy.o
	$(CC) $^ -o $@

$(OUT_DIR)/strcopy.o: $(SRC_DIR)/strcopy.asm
	nasm -f macho64 $< -o $@

$(OUT_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(APP)
	./$^

clean:
	$(RM) $(OUT_DIR)/*.o *.exe
