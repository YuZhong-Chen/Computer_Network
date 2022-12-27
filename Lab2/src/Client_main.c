#include "Client.h"

int sockfd = 0;
UDP_pkt snd_pkt, rcv_pkt;
struct sockaddr_in info, client_info;
socklen_t len;
time_t t1, t2;

int main(int argc, char *argv[]) {
    //==============
    // Create socket
    //==============
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        printf("Fail to create a socket.");
    }

    //==================
    // Input server info
    //==================
    bzero(&info, sizeof(info));
    info.sin_family = AF_INET;

    char *server_ip = (char *)malloc(sizeof(char) * 30);
    int server_port;

    printf("give me an IP to send: ");
    scanf("%s", server_ip);
    printf("server's's port? ");
    scanf("%d", &server_port);

    //==================================
    // Just test how to convert the type
    //==================================
    info.sin_addr.s_addr = inet_addr(server_ip);
    info.sin_port = htons(server_port);

    server_port = htons(info.sin_port);
    server_ip = inet_ntoa(info.sin_addr);
    // printf("server %s : %d\n", server_ip, server_port);

    //====================================
    // Create send packet & receive packet
    //====================================
    memset(snd_pkt.data, '\0', sizeof(snd_pkt.data));
    len = sizeof(info);

    printf("Waiting for a commands...\n");
    getchar();
    while (fgets(snd_pkt.data, 30, stdin)) {
        // ================================
        // command "exit": close the client
        // ================================
        if (strncmp(snd_pkt.data, "exit", 4) == 0) {
            break;
            // ==============================================================
            // command "download filename": download the file from the server
            // ==============================================================
        } else if (strncmp(snd_pkt.data, "download", 8) == 0) {
            snd_pkt.header.seq_num = 0;
            snd_pkt.header.ack_num = 0;
            snd_pkt.header.isLast = 1;
            // We first set is_last to 1 so that server know its our first message.

            int numbytes;
            FILE *fd;
            //========================
            // Send filename to server
            //========================
            if ((numbytes = sendto(sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&info, len)) == -1) {
                perror("error");
                return 0;
            }
            printf("client: sent %d bytes to %s\n", numbytes, inet_ntoa(info.sin_addr));

            //=========================================
            // Get server response if file exist or not
            //=========================================
            if ((numbytes = recvfrom(sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&info, (socklen_t *)&len)) == -1) {
                printf("recvfrom error\n");
                return 0;
            }
            printf("client: receive %d bytes from %s\n", numbytes, inet_ntoa(info.sin_addr));
            // printf("%s", buf);

            //====================
            // File does not exist
            //====================
            if (strcmp(rcv_pkt.data, "FILE_NOT_EXISTS") == 0) {
                printf("FILE_NOT_EXISTS\n");
            }

            //==========================
            // File exists, receive file
            //==========================
            else if (strcmp(rcv_pkt.data, "FILE_EXISTS") == 0) {
                t1 = time(NULL);
                recvFile(fd, snd_pkt);
                t2 = time(NULL);
                printf("Total cost %ld secs\n", t2 - t1);
            }

        } else {
            printf("Illegal command\n");
        }

        printf("Waiting for a commands...\n");
    }
}
