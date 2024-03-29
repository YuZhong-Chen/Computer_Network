#include "Server.h"

static int sockfd;
static struct sockaddr_in info, client_info;
static socklen_t len;
static UDP_pkt snd_pkt, rcv_pkt;

// static pthread_t th1, th2;
// static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// static bool isCreateThread = false;

bool CreateSocket(int PORT) {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        printf("Fail to create a socket.");
        return false;
    }

    //=======================
    // Set up server info
    // IP address = 127.0.0.1
    //=======================
    bzero(&info, sizeof(info));
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = INADDR_ANY;
    info.sin_port = htons(PORT);

    //================
    // Bind the socket
    //================
    if (bind(sockfd, (struct sockaddr *)&info, sizeof(info)) == -1) {
        perror("server_sockfd bind failed: ");
        return false;
    }

    printf("=============Parameter=============\n");
    printf("Server's IP is 127.0.0.1\n");
    printf("Server is listening on port %d\n", PORT);
    printf("===================================\n\n");

    return true;
}

void SetupClientInfo() {
    bzero(&client_info, sizeof(client_info));
    client_info.sin_family = AF_INET;
    len = sizeof(client_info);
}

//=========================================================
// Initialization sending packet parameter.
//=========================================================
static void InitSendPkt() {
    snd_pkt.header.seq_num = 0;
    snd_pkt.header.ack_num = 0;
    snd_pkt.header.isLast = 0;
}

//=========================================================
// Return the command.
// Ther rest command is stored in the "strtok".
//=========================================================
char *ReceiveCmd() {
    memset(rcv_pkt.data, '\0', sizeof(rcv_pkt.data));

    // Disable socket timeout.
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));

    while ((recvfrom(sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_info, (socklen_t *)&len)) != -1) {
        // In client, we set is_last 1 to confirm server get client's first message.
        if (rcv_pkt.header.isLast == 1)
            break;
    }

    return strtok(rcv_pkt.data, " ");
}

static bool SendData(char *Data, int Data_Len, bool isLast) {
    snd_pkt.header.isLast = isLast;
    for (int i = 0; i < Data_Len; i++) {
        snd_pkt.data[i] = Data[i];
    }

    int SendBytes;
    if ((SendBytes = sendto(sockfd, &snd_pkt, sizeof(snd_pkt.header) + Data_Len, 0, (struct sockaddr *)&client_info, len)) == -1) {
        perror("sendto error ");
        return false;
    }

    printf("\tSend     %4d bytes to   %s\n", SendBytes, inet_ntoa(client_info.sin_addr));
    return true;
}

static int ReceiveData() {
    // Set the Socket Timeout.
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = TIMEOUT;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));

    int ReceiveBytes;
    if ((ReceiveBytes = recvfrom(sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&info, (socklen_t *)&len)) == -1) {
        // printf("recvfrom error\n");
        return -1;
    }

    printf("\tReceive  %4d bytes from %s\n", ReceiveBytes, inet_ntoa(client_info.sin_addr));
    return ReceiveBytes;
}

// Default the client always receives this packet, so don't need to wait for ack.
bool SendMsg(char *msg) {
    return SendData(msg, strlen(msg), false);
}

// Send file function, it call receive_thread function at the first time.
bool SendFile(FILE *fd) {
    fseek(fd, 0, SEEK_END);
    long FileSize = ftell(fd);
    printf("File size: %ld\n", FileSize);
    rewind(fd);  // Set the position to the beginning of the file.

    // // At the first time, we need to create thread.
    // if (!isCreateThread) {
    //     isCreateThread = true;
    //     // pthread_create(&th1, NULL, receive_thread, NULL);
    //     // pthread_create(&th2, NULL, timeout_process, NULL);
    // }
    int ReadBytes;
    char Buffer[PACKET_DATA_SIZE];
    bool isEndOfFile = false;

    InitSendPkt();

    while (!isEndOfFile) {
        // Read data from the file descriptor.
        ReadBytes = fread(Buffer, 1, sizeof(Buffer), fd);
        isEndOfFile = feof(fd);

        // Send data to client
        SendData(Buffer, ReadBytes, isEndOfFile);

        while (true) {
            // Receive client ack
            if (ReceiveData() > 0) {
                printf("\t\t ACK number %3d\n", rcv_pkt.header.ack_num);
                if (rcv_pkt.header.ack_num == snd_pkt.header.seq_num) {
                    snd_pkt.header.seq_num++;
                    break;
                }
            }

            // Timeout, send the packet again.
            printf("\tTimeout! Resend packet\n");
            SendData(Buffer, ReadBytes, isEndOfFile);
        }
    }

    printf("Sending file successfully.\n");
    fclose(fd);

    return true;
}

/*******************notice*******************************
 * Use it like following block.
 *
 * pthread_mutex_lock( &mutex );
 * ...
 * critical section
 * ...
 * pthread_mutex_unlock( &mutex );
 *
 *********************************************************/
void *receive_thread() {
    //--------------------------------------
    // Checking timeout & Receive client ack
    //--------------------------------------

    //------------------------------------------
    // Keep the thread alive not to uncomment it
    //------------------------------------------
    // pthread_exit(NULL);
    return NULL;
}

void *timeout_thread() {
    //------------------------------------------
    // Keep the thread alive not to uncomment it
    //------------------------------------------
    // pthread_exit(NULL);
    return NULL;
}