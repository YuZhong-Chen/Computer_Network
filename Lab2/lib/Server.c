#include "Server.h"

static int sockfd;
static struct sockaddr_in info, client_info;
static socklen_t len;
static UDP_pkt snd_pkt, rcv_pkt;

// static pthread_t th1, th2;
// static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static bool isCreateThread = false;

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

    printf("====Parameter====\n");
    printf("Server's IP is 127.0.0.1\n");
    printf("Server is listening on port %d\n", PORT);
    printf("==============\n");

    return true;
}

void SetupClientInfo() {
    bzero(&client_info, sizeof(client_info));
    client_info.sin_family = AF_INET;
    len = sizeof(client_info);
}

//============================================
// Initialization sending packet parameter.
//============================================
void InitSendPkt() {
    snd_pkt.header.seq_num = 0;
    snd_pkt.header.ack_num = 0;
    snd_pkt.header.isLast = 0;
}

// Return the command.
// Ther rest command is stored in the "strtok".
char *ReceiveCmd() {
    memset(rcv_pkt.data, '\0', sizeof(rcv_pkt.data));
    while ((recvfrom(sockfd, &rcv_pkt, sizeof(rcv_pkt), 0, (struct sockaddr *)&client_info, (socklen_t *)&len)) != -1) {
        // In client, we set is_last 1 to confirm server get client's first message.
        if (rcv_pkt.header.isLast == 1)
            break;
    }

    return strtok(rcv_pkt.data, " ");
}

bool SendMsg(char *msg) {
    strcpy(snd_pkt.data, msg);

    int numbytes;
    if ((numbytes = sendto(sockfd, &snd_pkt, sizeof(snd_pkt), 0, (struct sockaddr *)&client_info, len)) == -1) {
        perror("sendto error ");
        return false;
    }

    printf("server: sent %d bytes to %s\n", numbytes, inet_ntoa(client_info.sin_addr));
    return true;
}

//==================================
// You should complete this function
//==================================
// Send file function, it call receive_thread function at the first time.
bool SendFile(FILE *fd) {
    int filesize = ftell(fd);
    printf("File size: %d\n", filesize);
    //----------------------------------------------------------------
    // Bonus part for declare timeout threads if you need bonus point,
    // uncomment it and manage the thread by yourself
    //----------------------------------------------------------------
    // At the first time, we need to create thread.
    if (!isCreateThread) {
        isCreateThread = true;
        // pthread_create(&th1, NULL, receive_thread, NULL);
        // pthread_create(&th2, NULL, timeout_process, NULL);
    }

    //==========================
    // Send video data to client
    //==========================

    //======================================
    // Checking timeout & Receive client ack
    //======================================

    //=============================================
    // Set is_last flag for the last part of packet
    //=============================================

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