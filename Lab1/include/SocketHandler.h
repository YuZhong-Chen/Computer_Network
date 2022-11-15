#ifndef _SOCKET_HANDLER_H_
#define _SOCKET_HANDLER_H_

#include <arpa/inet.h>
#include <assert.h>
#include <math.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define REQUEST_SIZE 1000
#define RESPONSE_SIZE 100000

typedef struct {
    char DomainName[100];
    char Path[150];
    char PortNum[5];
} UniformResourceLocator;
extern UniformResourceLocator URL;

typedef struct {
    struct addrinfo hints;
    struct addrinfo *res;
} ADDRESS_INFO;
extern ADDRESS_INFO AddressInfo;

void SocketHandlerInit();
void SocketHandlerEnd();

void URL_Parser(char *url);
void GetAddressInfo();
void SettingSocket();

void ConstructRequest();
void SendRequest();
void ReceiveResponse();

extern char Request[REQUEST_SIZE];
extern char Response[RESPONSE_SIZE];
extern int ResponseLength;

#endif