CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
OBJ_DIR := $(CUR_DIR)/obj
SRC_DIR := $(CUR_DIR)/src
LIB_DIR := $(CUR_DIR)/lib
LIB_SHARED_DIR := $(LIB_DIR)/shared
LIB_STATIC_DIR := $(LIB_DIR)/static
LIB_STATIC_NAME := bstrutils_static
LIB_SHARED_NAME := bstrutils_shared


create_obj: $(SRC_DIR)/main.c $(SRC_DIR)/bstrutils.c
	gcc -c -fPIC $(SRC_DIR)/bstrutils.c -o $(OBJ_DIR)/bstrutils_shared.o -I$(INC_DIR)
	gcc -c  $(SRC_DIR)/bstrutils.c -o $(OBJ_DIR)/bstrutils_static.o -I$(INC_DIR)
	gcc -c  $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o -I$(INC_DIR)

create_static_lib: $(OBJ_DIR)/bstrutils_static.o
	ar rcs $(LIB_STATIC_DIR)/lib$(LIB_STATIC_NAME).a $(OBJ_DIR)/bstrutils_static.o

create_shared_lib: $(OBJ_DIR)/bstrutils_shared.o
	gcc -shared $(OBJ_DIR)/bstrutils_shared.o -o $(LIB_SHARED_DIR)/lib$(LIB_SHARED_NAME).so

all: create_obj create_static_lib create_shared_lib
	gcc   $(OBJ_DIR)/main.o  -L$(LIB_STATIC_DIR) -l $(LIB_STATIC_NAME) -o $(BIN_DIR)/statically-linked
	gcc  $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -l $(LIB_SHARED_NAME) -o $(BIN_DIR)/use-shared-library

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_SHARED_DIR)/*
	rm -rf $(LIB_STATIC_DIR)/*
	rm -rf $(BIN_DIR)/*
