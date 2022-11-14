# ----------------------------------------------------------------------------

CC = gcc
CFLAGS = -O3
OBJS = TCP_server.o TCP_client.o
EXE = ${OBJS:.o=}

# ----------------------------------------------------------------------------

all: TCP_server TCP_client clear

TCP_server: TCP_server.o
	@${CC} TCP_server.o ${CFLAGS} -o TCP_server

TCP_server.o: TCP_server.c
	@${CC} TCP_server.c ${CFLAGS} -c

TCP_client: TCP_client.o
	@${CC} TCP_client.o ${CFLAGS} -o TCP_client

TCP_client.o: TCP_client.c
	@${CC} TCP_client.c ${CFLAGS} -c

%.o: %.c 
	@${CC} -c $^ -o $@

clear:
	@rm -f ${OBJS}

clean: clear
	@rm -f ${EXE}