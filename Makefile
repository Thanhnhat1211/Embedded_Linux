CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
SRC_DIR := $(CUR_DIR)/src

all: $(SRC_DIR)/main.c $(SRC_DIR)/SigAlrm.c $(SRC_DIR)/SigInt.c $(SRC_DIR)/SigUsr1.c
	gcc -o $(BIN_DIR)/main $(SRC_DIR)/main.c
	gcc -o $(BIN_DIR)/sigalrm $(SRC_DIR)/SigAlrm.c
	gcc -o $(BIN_DIR)/sigint $(SRC_DIR)/SigInt.c
	gcc -o $(BIN_DIR)/sigusr1 $(SRC_DIR)/SigUsr1.c

clean:
	rm -rf $(BIN_DIR)/*
