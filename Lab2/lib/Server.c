#include "Server.h"

// Global variables
int sockfd;
struct sockaddr_in info, client_info;
socklen_t len;
UDP_pkt snd_pkt, rcv_pkt;
pthread_t th1, th2;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Local variables
static bool isCreateThread = false;

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
}

void *timeout_thread() {
    //------------------------------------------
    // Keep the thread alive not to uncomment it
    //------------------------------------------
    // pthread_exit(NULL);
}

//==================================
// You should complete this function
//==================================
// Send file function, it call receive_thread function at the first time.
bool sendFile(FILE *fd) {
    int filesize = ftell(fd);
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

    printf("send file successfully\n");
    fclose(fd);

    return true;
}