#include "Server.h"

int main(int argc, char *argv[]) {
    // Create socket.
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        printf("Fail to create a socket.");
    }

    //=======================
    // input server info
    // IP address = 127.0.0.1
    //=======================
    bzero(&info, sizeof(info));
    info.sin_family = AF_INET;
    int port = atoi(argv[1]);  // Server port
    info.sin_addr.s_addr = INADDR_ANY;
    info.sin_port = htons(port);
    // printf("server %s : %d\n", inet_ntoa(info.sin_addr), htons(info.sin_port));

    //================
    // Bind the socket
    //================
    if (bind(sockfd, (struct sockaddr *)&info, sizeof(info)) == -1) {
        perror("server_sockfd bind failed: ");
        return 0;
    }

    //====================================
    // Create send packet & receive packet
    //====================================
    memset(rcv_pkt.data, '\0', sizeof(rcv_pkt.data));

    //====================
    // Use for client info
    //====================
    bzero(&client_info, sizeof(client_info));
    client_info.sin_family = AF_INET;
    len = sizeof(client_info);

    printf("====Parameter====\n");
    printf("Server's IP is 127.0.0.1\n");
    printf("Server is listening on port %d\n", port);
    printf("==============\n");

    while (true) {
        //=========================
        // Initialization parameter
        //=========================
        snd_pkt.header.seq_num = 0;
        snd_pkt.header.ack_num = 0;
        snd_pkt.header.isLast = 0;
        FILE *fd;

        printf("server waiting.... \n");
        char *str;
        while ((recvfrom(sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_info, (socklen_t *)&len)) != -1) {
            // In client, we set is_last 1 to confirm server get client's first message.
            if (rcv_pkt.header.isLast == 1)
                break;
        }
        printf("process command.... \n");
        str = strtok(rcv_pkt.data, " ");

        //===============================================================
        // command "download filename": download the file from the server
        // and then check if filename is exist
        //===============================================================
        if (strcmp(str, "download") == 0) {
            str = strtok(NULL, " \n");
            printf("filename is %s\n", str);

            // if file not exists
            if ((fd = fopen(str, "rb")) == NULL) {
                //=======================================
                // Send FILE_NOT_EXISTS msg to the client
                //=======================================
                printf("FILE_NOT_EXISTS\n");
                strcpy(snd_pkt.data, "FILE_NOT_EXISTS");
                int numbytes;
                if ((numbytes = sendto(sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_info, len)) == -1) {
                    printf("sendto error\n");
                    return 0;
                }
                printf("server: sent %d bytes to %s\n", numbytes, inet_ntoa(client_info.sin_addr));
            } else {  // else, file exists
                fseek(fd, 0, SEEK_END);
                printf("FILE_EXISTS\n");
                strcpy(snd_pkt.data, "FILE_EXISTS");

                //==================================
                // Send FILE_EXIST msg to the client
                //==================================
                int numbytes;
                if ((numbytes = sendto(sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_info, len)) == -1) {
                    printf("sendto error\n");
                    return 0;
                }
                printf("server: sent %d bytes to %s\n", numbytes, inet_ntoa(client_info.sin_addr));

                //==========================================================================
                // Sleep 1 seconds before transmitting data to make sure the client is ready
                //==========================================================================
                sleep(1);
                printf("transmitting...\n");

                //=====================================
                // Start to send the file to the client
                //=====================================
                sendFile(fd);
            }
        } else {
            printf("Illegal request!\n");
        }
    }
}
