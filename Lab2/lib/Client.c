#include "Client.h"

static int sockfd = 0;
static UDP_pkt snd_pkt, rcv_pkt;
static struct sockaddr_in info;
static socklen_t len;

bool CreateSocket() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        printf("Fail to create a socket.");
        return false;
    }
    return true;
}

void SetupServerInfo() {
    // Input server info
    bzero(&info, sizeof(info));
    info.sin_family = AF_INET;

    char *server_ip = (char *)malloc(sizeof(char) * 30);
    int server_port;

    printf("give me an IP to send: ");
    if (scanf("%s", server_ip)) {
    }
    printf("server's's port? ");
    if (scanf("%d", &server_port)) {
    }
    getchar();

    // Just test how to convert the type
    info.sin_addr.s_addr = inet_addr(server_ip);
    info.sin_port = htons(server_port);

    server_port = htons(info.sin_port);
    server_ip = inet_ntoa(info.sin_addr);
    // printf("server %s : %d\n", server_ip, server_port);

    len = sizeof(info);
}

static void InitSendPkt() {
    memset(snd_pkt.data, '\0', sizeof(snd_pkt.data));
}

//=====================
// Simulate packet loss
//=====================
static bool isLoss() {
    if (PACKET_LOSS_RATE >= 1.0)  // All packets are loss.
        return true;
    else
        return (rand() <= (PACKET_LOSS_RATE * RAND_MAX));
}

//====================
// Reply ack to server
//====================
static bool SendACK(int num) {
    snd_pkt.header.seq_num = 0;
    snd_pkt.header.ack_num = num;
    snd_pkt.header.isLast = 0;

    // Send Command to server
    int numbytes;
    if ((numbytes = sendto(sockfd, &snd_pkt, sizeof(snd_pkt.header), 0, (struct sockaddr *)&info, len)) == -1) {
        perror("sendto error");
        return false;
    }

    return true;
}

bool CheckFileStatus(char *FileName) {
    snd_pkt.header.seq_num = 0;
    snd_pkt.header.ack_num = 0;
    snd_pkt.header.isLast = 1;
    // We first set is_last to 1 so that server know its our first message.

    char Command[50];
    sprintf(Command, "download ");
    strcat(Command, FileName);
    strcpy(snd_pkt.data, Command);

    int numbytes;
    // Send Command to server
    if ((numbytes = sendto(sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&info, len)) == -1) {
        perror("sendto error");
        return false;
    }
    printf("Client: sent %d bytes to %s\n", numbytes, inet_ntoa(info.sin_addr));

    // Get server response.
    if ((numbytes = recvfrom(sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&info, (socklen_t *)&len)) == -1) {
        printf("recvfrom error\n");
        return false;
    }
    printf("Client: receive %d bytes from %s\n", numbytes, inet_ntoa(info.sin_addr));

    if (strcmp(rcv_pkt.data, "FILE_NOT_EXISTS") == 0) {
        printf("FILE_NOT_EXISTS\n");
        return false;
    } else if (strcmp(rcv_pkt.data, "FILE_EXISTS") == 0) {
        printf("FILE_EXISTS\n");
        return true;
    }

    return false;
}

bool recvFile(char *FileName) {
    char FilePath[30];
    sprintf(FilePath, CLIENT_DATABASE_PATH);
    strcat(FilePath, FileName);

    FILE *fd = fopen(FilePath, "wb");

    char Buffer[200000];
    int ReceiveBytes;
    int Received_Seq_num = -1;

    memset(Buffer, '\0', sizeof(Buffer));
    memset(snd_pkt.data, '\0', sizeof(snd_pkt.data));

    InitSendPkt();

    while (true) {
        // Get server response.
        if ((ReceiveBytes = recvfrom(sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&info, (socklen_t *)&len)) == -1) {
            printf("recvfrom error\n");
            return false;
        }

        if (isLoss()) {
            printf("\tOops! Packet loss!\n");
        } else {
            printf("\tReceive %4d bytes from %s\n", ReceiveBytes, inet_ntoa(info.sin_addr));
            printf("\t             Sequence number %3d\n", rcv_pkt.header.seq_num);
            SendACK(rcv_pkt.header.seq_num);

            if ((int)rcv_pkt.header.seq_num == Received_Seq_num + 1) {
                fwrite(rcv_pkt.data, 1, ReceiveBytes - sizeof(rcv_pkt.header), fd);
                Received_Seq_num++;
            }
            if (rcv_pkt.header.isLast == true) {
                break;
            }
        }
    }

    fclose(fd);
    return true;
}

long long getCurrentTime() {
    static struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}