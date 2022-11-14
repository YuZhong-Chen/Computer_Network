#ifndef _SOCKET_HANDLER_H_
#define _SOCKET_HANDLER_H_

#include <arpa/inet.h>
#include <assert.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define REQUEST_SIZE 1000
#define RESPONSE_SIZE 1000

#define PORT_NUM "80"

void SocketHandlerInit();
void SocketHandlerEnd();
void URL_Parser(int argc, char **argv);

#endif