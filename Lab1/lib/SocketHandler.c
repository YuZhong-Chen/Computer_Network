#include "SocketHandler.h"

UniformResourceLocator URL;
ADDRESS_INFO AddressInfo;

char Request[REQUEST_SIZE];
char Response[REQUEST_SIZE];

void SocketHandlerInit() {
    strcpy(URL.PortNum, "80");
    memset(&(AddressInfo.hints), 0, sizeof(struct addrinfo));
    AddressInfo.res = NULL;
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
        perror("getaddrinfo ");
        assert(false);
    }
}

int temp() {
    char *RequestLine = "GET /index.php HTTP/1.1\r\n";
    char *Header = "Host: %s\r\n";
    char *CRLF = "\r\n";

    int BufferLen = strlen(Header) + strlen(URL.DomainName) + 1;
    char *Buffer = (char *)malloc(BufferLen);

    strcpy(Request, RequestLine);

    sprintf(Buffer, Header, URL.DomainName);
    strcat(Request, Buffer);
    strcat(Request, CRLF);

    int sock = 0;
    if ((sock = socket(AddressInfo.res->ai_family, AddressInfo.res->ai_socktype, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    if (connect(sock, AddressInfo.res->ai_addr, AddressInfo.res->ai_addrlen) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    if (send(sock, Request, strlen(Request), 0) == -1) {
        perror("Send error");
        return EXIT_FAILURE;
    }
    printf("Message sent\n\n");

    int ResponseLength = 0;
    while (1) {
        int num = read(sock, Response, RESPONSE_SIZE);
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

    free(Buffer);
    Buffer = NULL;

    return 0;
}