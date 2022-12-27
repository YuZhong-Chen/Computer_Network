#ifndef _SERVER_H_
#define _SERVER_H_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "UDP_pkt.h"

#define SERVER_DATABASE_PATH "./data/"
#define TIMEOUT 100

bool CreateSocket(int PORT);

void SetupClientInfo();

void InitSendPkt();

char *ReceiveCmd();
bool SendMsg(char *msg);
bool SendFile(FILE *fd);

void *receive_thread();
void *timeout_thread();

#endif