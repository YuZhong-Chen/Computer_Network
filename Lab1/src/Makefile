# ----------------------------------------------------------------------------

CC = gcc
CFLAGS = -O3 -Wall
OBJS = main.o
EXE = ${OBJS:.o=}

# ----------------------------------------------------------------------------

all: main clear

main: main.o
	@${CC} main.o ${CFLAGS} -o main

main.o: main.c
	@${CC} main.c ${CFLAGS} -c

%.o: %.c 
	@${CC} -c $^ -o $@

clear:
	@rm -f ${OBJS}

clean: clear
	@rm -f ${EXE}