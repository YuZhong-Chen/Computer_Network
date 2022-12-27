# ----------------------------------------------------------------------------

# Tool
CC = gcc

# Compiler Flags
C_FLAGS = -O3 -Wall -Wextra 

# PATH
INC_PATH = include
LIB_PATH = lib
SRC_PATH = src
BIN_PATH = bin

# TARGET
TARGET = Server_main Client_main

# The -lm flag is used to link the libraries that are not in the standard library. Such as <math.h>.

# ----------------------------------------------------------------------------

.PHONY: all
all: ${TARGET}

Server_main:
	@$(CC) $(C_FLAGS) -lpthread -lm -I $(INC_PATH) ${LIB_PATH}/Server.c ${SRC_PATH}/Server_main.c -o ${BIN_PATH}/Server_main

Client_main:
	@$(CC) $(C_FLAGS) -I $(INC_PATH) ${LIB_PATH}/Client.c ${SRC_PATH}/Client_main.c -o ${BIN_PATH}/Client_main

test:
	@$(CC) $(C_FLAGS) test/test_clock.c -o ${BIN_PATH}/test_clock -lm

.PHONY: clean
clean:
	@rm -rf ${BIN_PATH}/*