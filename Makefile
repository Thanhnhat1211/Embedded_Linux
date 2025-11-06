CUR_DIR := .
SRC_DIR := $(CUR_DIR)/src
BIN_DIR := $(CUR_DIR)/bin


create_program: $(SRC_DIR)/main.c
	gcc -o $(BIN_DIR)/program $(SRC_DIR)/main.c

all: hello.txt create_program
	$(BIN_DIR)/program $(CUR_DIR)/hello.txt

clean:
	rm -rf $(BIN_DIR)/*
	rm -rf $(SRC_DIR)/program
