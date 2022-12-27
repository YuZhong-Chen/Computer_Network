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

bool recvFile(FILE *fd, UDP_pkt snd_pkt);

#endif