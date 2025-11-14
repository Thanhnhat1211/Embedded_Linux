CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
SRC_DIR := $(CUR_DIR)/src

all: $(SRC_DIR)/Thread.c $(SRC_DIR)/Mutex.c $(SRC_DIR)/Cond_Variable.c
	gcc -o $(BIN_DIR)/Thread $(SRC_DIR)/Thread.c
	gcc -o $(BIN_DIR)/Mutex $(SRC_DIR)/Mutex.c
	gcc -o $(BIN_DIR)/Cond_Variable $(SRC_DIR)/Cond_Variable.c

clean:
	rm -rf $(BIN_DIR)/*
