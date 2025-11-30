CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
SRC_DIR := $(CUR_DIR)/src

all:
	gcc -o $(BIN_DIR)/tcp_ipv4_client $(SRC_DIR)/tcp_ipv4_client.c
	gcc -o $(BIN_DIR)/tcp_ipv4_server $(SRC_DIR)/tcp_ipv4_server.c 
	gcc -o $(BIN_DIR)/udp_ipv4_client $(SRC_DIR)/udp_ipv4_client.c
	gcc -o $(BIN_DIR)/udp_ipv4_server $(SRC_DIR)/udp_ipv4_server.c 
	gcc -o $(BIN_DIR)/unix_stream_client $(SRC_DIR)/unix_stream_client.c
	gcc -o $(BIN_DIR)/unix_stream_server $(SRC_DIR)/unix_stream_server.c 
	gcc -o $(BIN_DIR)/unix_dgram_client $(SRC_DIR)/unix_dgram_client.c
	gcc -o $(BIN_DIR)/unix_dgram_server $(SRC_DIR)/unix_dgram_server.c

clean:
	rm -rf $(BIN_DIR)/*