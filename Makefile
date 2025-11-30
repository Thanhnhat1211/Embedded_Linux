CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
SRC_DIR := $(CUR_DIR)/src

all:
	gcc -o $(BIN_DIR)/mypipe $(SRC_DIR)/mypipe.c

clean:
	rm -rf $(BIN_DIR)/*