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
TARGET = main

# ----------------------------------------------------------------------------

.PHONY: all
all: ${TARGET}

.PHONY: main
main: $(OBJECTS)
	@$(CC) $(C_FLAGS) -I $(INC_PATH) ${LIB_PATH}/* ${SRC_PATH}/* -o ${BIN_PATH}/main

.PHONY: clean
clean:
	@rm -rf ${BIN_PATH}/*