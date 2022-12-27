#ifndef _UDP_PKT_H_
#define _UDP_PKT_H_

//==============
// Packet Header
//==============
typedef struct header {
    unsigned int seq_num;
    unsigned int ack_num;
    unsigned char isLast;
} HEADER;

//==================
// UDP packet & data
//==================
typedef struct udp_pkt {
    HEADER header;
    char data[1024];
} UDP_pkt;

#endif