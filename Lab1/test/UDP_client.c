// Client side implementation of UDP client-server model
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define MAX_LINE 1024

// Driver code
int main() {
    int sockfd;
    char buffer[MAX_LINE];
    char *hello = "Hello from client";
    struct sockaddr_in ServerAddress;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&ServerAddress, 0, sizeof(ServerAddress));
    // Filling server information
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(PORT);
    ServerAddress.sin_addr.s_addr = INADDR_ANY;
    int n, len;

    sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *)&ServerAddress, sizeof(ServerAddress));
    printf("Hello message sent.\n");

    n = recvfrom(sockfd, (char *)buffer, MAX_LINE, MSG_WAITALL, (struct sockaddr *)&ServerAddress, &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    close(sockfd);
    return 0;
}