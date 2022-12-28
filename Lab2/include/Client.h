#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "UDP_pkt.h"

#define PACKET_LOSS_RATE 0.5
#define CLIENT_DATABASE_PATH "./ClientData/"

bool CreateSocket();

void SetupServerInfo();

bool CheckFileStatus(char *FileName);

bool recvFile(char *FileName);

long long getCurrentTime();

#endif