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

#define TIMEOUT 100

bool sendFile(FILE *fd);

void *receive_thread();
void *timeout_thread();

// Global variables
extern int sockfd;
extern struct sockaddr_in info, client_info;
extern socklen_t len;
extern UDP_pkt snd_pkt, rcv_pkt;

extern pthread_mutex_t mutex;

#endif