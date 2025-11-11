CUR_DIR := .
SRC_DIR := $(CUR_DIR)/src
BIN_DIR := $(CUR_DIR)/bin

all: $(SRC_DIR)/Process_A.c $(SRC_DIR)/Process_B.c $(SRC_DIR)/Process_Zombie $(SRC_DIR)/Process_Orphan
	gcc -o $(BIN_DIR)/Process_A $(SRC_DIR)/Process_A.c
	gcc -o $(BIN_DIR)/Process_B $(SRC_DIR)/Process_B.c 
	gcc -o $(BIN_DIR)/Process_Zombie $(SRC_DIR)/Process_Zombie.c 
	gcc -o $(BIN_DIR)/Process_Orphan $(SRC_DIR)/Process_Orphan.c

clean:
	rm -rf $(BIN_DIR)/*