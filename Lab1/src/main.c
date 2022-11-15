#include "HtmlParser.h"
#include "SocketHandler.h"

void Init();
void Ending();

int main(int argc, char **argv) {
    Init();

    if (argc <= 1) {
        printf("Wrong Input: There must have one input.");
        assert(false);
    } else if (argc > 2) {
        printf("Wrong Input: There must have only one input.");
        assert(false);
    }

    URL_Parser(argv[1]);
    printf("Input URL: %s%s\n", URL.DomainName, URL.Path);

    printf("Getting the address info ...\n");
    GetAddressInfo();
    printf("Gotten.\n");

    printf("Creating socket and connect to %s\n", URL.DomainName);
    SettingSocket();
    printf("Connected.\n");

    ConstructRequest();

    printf("Sending request ...\n");
    SendRequest();
    printf("Sent.\n");

    printf("Receiving response ...\n");
    ReceiveResponse();
    printf("Received.\n");

    printf("%s\n", Response);

    Ending();
    return EXIT_SUCCESS;
}

void Init() {
    SocketHandlerInit();
    HtmlParserInit();
}

void Ending() {
    SocketHandlerEnd();
    HtmlParserEnd();
}