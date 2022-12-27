#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "UDP_pkt.h"

#define LOSS_RATE 0.9
#define CLIENT_DATABASE_PATH "./output/"

bool CreateSocket();

void InitSendPkt();

void SetupServerInfo();

bool CheckFileStatus(char *FileName);

bool recvFile(char *FileName);

#endif