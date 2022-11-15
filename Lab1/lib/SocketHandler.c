#include "SocketHandler.h"

UniformResourceLocator URL;
ADDRESS_INFO AddressInfo;

// File descriptor of Socket.
static int Socket;

char Request[REQUEST_SIZE];
char Response[REQUEST_SIZE];

void SocketHandlerInit() {
    strcpy(URL.PortNum, "80");
    memset(&(AddressInfo.hints), 0, sizeof(struct addrinfo));
    AddressInfo.res = NULL;
    Socket = -1;
}

void SocketHandlerEnd() {
    free(AddressInfo.res);
    AddressInfo.res = NULL;
}

void URL_Parser(char *url) {
    size_t i, j;
    size_t urlLength = strlen(url);

    // Get Domain Name.
    for (i = 0; i < urlLength; i++) {
        if (url[i] == '/') {
            break;
        }
        URL.DomainName[i] = url[i];
    }
    URL.DomainName[i] = '\0';

    // Get the Path.
    for (j = 0; i < urlLength; i++, j++) {
        URL.Path[j] = url[i];
    }
    URL.Path[j] = '\0';
}

void GetAddressInfo() {
    AddressInfo.hints.ai_family = AF_UNSPEC;
    AddressInfo.hints.ai_socktype = SOCK_STREAM;
    AddressInfo.hints.ai_flags = AI_NUMERICSERV;

    if (getaddrinfo(URL.DomainName, URL.PortNum, &(AddressInfo.hints), &(AddressInfo.res))) {
        perror("Fail to get address info");
        assert(false);
    }
}

void SettingSocket() {
    Socket = socket(AddressInfo.res->ai_family, AddressInfo.res->ai_socktype, 0);
    if (Socket == -1) {
        perror("Fail to create socket");
        assert(false);
    }

    if (connect(Socket, AddressInfo.res->ai_addr, AddressInfo.res->ai_addrlen)) {
        perror("Connection Failed");
        assert(false);
    }
}

void ConstructRequest() {
    char *GetRequest = "GET %s HTTP/1.1";
    char *Host = "Host: %s";
    char *CRLF = "\r\n";

    char Buffer[200];
    memset(Buffer, 0, strlen(Buffer));

    // Assemble Get and Path.
    sprintf(Buffer, GetRequest, URL.Path);
    strcpy(Request, Buffer);
    strcat(Request, CRLF);
    memset(Buffer, 0, strlen(Buffer));

    // Assemble Host and Domain name.
    sprintf(Buffer, Host, URL.DomainName);
    strcat(Request, Buffer);
    strcat(Request, CRLF);

    // End of Request.
    strcat(Request, CRLF);
}

void SendRequest() {
    if (send(Socket, Request, strlen(Request), 0) == -1) {
        perror("Send error");
        assert(false);
    }
}

void ReceiveResponse() {
    int ResponseLength = 0;
    while (1) {
        int num = read(Socket, Response, RESPONSE_SIZE);
        if (num == 0) {
            break;
        } else if (num == -1) {
            continue;
        }

        int i = 0;
        for (i = 0; i < num; i++) {
            printf("%c", Response[i]);
        }
        ResponseLength += num;
    }
    printf("\nLen : %d\n", ResponseLength);
}