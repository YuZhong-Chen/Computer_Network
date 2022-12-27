#ifndef _UDP_PKT_H_
#define _UDP_PKT_H_

#define PACKET_DATA_SIZE 1024

//==============
// Packet Header
//==============
typedef struct {
    unsigned int seq_num;
    unsigned int ack_num;
    unsigned char isLast;
} HEADER;

//==================
// UDP packet & data
//==================
typedef struct {
    HEADER header;
    char data[PACKET_DATA_SIZE];
} UDP_pkt;

#endif