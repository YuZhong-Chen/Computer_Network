#include "SocketHandler.h"

char *Hostname;
char *Target;

char Request[REQUEST_SIZE];
char Response[REQUEST_SIZE];

void SocketHandlerInit() {
}

void SocketHandlerEnd() {
    free(Hostname);
    free(Target);
}

void URL_Parser(int argc, char **argv) {
    char Buffer[100];

    if (argc == 1) {
        printf("Wrong Input : There must have one input.");
        assert(false);
    } else if (argc > 2) {
        printf("Wrong Input : There must have only one input.");
        assert(false);
    }

    size_t i = 0;
    for (i = 0; i < strlen(argv[1]); i++) {
        Buffer[i] = argv[1][i];
    }
    printf("%s\n\n\n", Buffer);
}

void Hostname_to_IP_Address() {
}

int temp() {
    char *RequestLine = "GET /index.php HTTP/1.1\r\n";
    char *Header = "Host: %s\r\n";
    char *CRLF = "\r\n";

    int BufferLen = strlen(Header) + strlen(Hostname) + 1;
    char *Buffer = (char *)malloc(BufferLen);

    strcpy(Request, RequestLine);

    sprintf(Buffer, Header, Hostname);
    strcat(Request, Buffer);
    strcat(Request, CRLF);

    // -------------------------------------------
    // hints 參數，設定 getaddrinfo() 的回傳方式
    struct addrinfo hints;

    // getaddrinfo() 執行結果的 addrinfo 結構指標
    struct addrinfo *result;

    // 以 memset 清空 hints 結構
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;      // 使用 IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;  // 串流 Socket
    hints.ai_flags = AI_NUMERICSERV;  // 將 getaddrinfo() 第 2 參數 (PORT_NUM) 視為數字

    if (getaddrinfo(Hostname, PORT_NUM, &hints, &result) != 0) {
        perror("Test");
        return EXIT_FAILURE;
    }

    int sock = 0;
    if ((sock = socket(result->ai_family, result->ai_socktype, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    if (connect(sock, result->ai_addr, result->ai_addrlen) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    free(result);
    result = NULL;

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