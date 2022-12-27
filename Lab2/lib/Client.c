#include "Client.h"

// Global variables

//=====================
// Simulate packet loss
//=====================
static bool isLoss(double prob) {
    if (prob >= 1.0)  // All packets are loss.
        return true;
    else
        return (rand() <= (prob * RAND_MAX));
}

bool recvFile(FILE *fd, UDP_pkt snd_pkt) {
    printf("FILE_EXISTS\n");

    char *str;
    char fileName[30];

    //==================================================================
    // Split the command into "download" & "filename", just get filename
    //==================================================================
    str = strtok(snd_pkt.data, " \n");
    str = strtok(NULL, " \n");

    sprintf(fileName, "download_");
    strcat(fileName, str);

    // FILE *fd;
    fd = fopen(fileName, "wb");

    printf("Receiving...\n");
    char buffer[123431];
    int index = 0;
    int receive_packet = 0;
    memset(snd_pkt.data, '\0', sizeof(snd_pkt.data));

    while (true) {
        if (isLoss(0.5)) {
            printf("\tOops! Packet loss!\n");
            break;
        }
        //==============================================
        // Actually receive packet and write into buffer
        //==============================================

        //==============================================
        // Write buffer into file if is_last flag is set
        //==============================================

        //====================
        // Reply ack to server
        //====================
    }

    return true;
}
