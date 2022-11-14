// Server side implementation of UDP client-server model
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
    char *hello = "Hello from server";
    struct sockaddr_in ServerAddress, ClientAddress;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&ServerAddress, 0, sizeof(ServerAddress));
    memset(&ClientAddress, 0, sizeof(ClientAddress));

    // Filling server information
    ServerAddress.sin_family = AF_INET;  // IPv4
    ServerAddress.sin_addr.s_addr = INADDR_ANY;
    ServerAddress.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&ServerAddress, sizeof(ServerAddress)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;
    len = sizeof(ClientAddress);  // len is value/result
    n = recvfrom(sockfd, (char *)buffer, MAX_LINE, MSG_WAITALL, (struct sockaddr *)&ClientAddress, &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);

    sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *)&ClientAddress, len);
    printf("Hello message sent.\n");

    return 0;
}