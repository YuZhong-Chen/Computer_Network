#include "ResponseParser.h"
#include "SocketHandler.h"

void Init();
void Ending();

int main(int argc, char **argv) {
    int i;

    Init();

    if (argc <= 1) {
        printf("Wrong Input: There must have one input.");
        assert(false);
    } else if (argc > 2) {
        printf("Wrong Input: There must have only one input.");
        assert(false);
    }

    URL_Parser(argv[1]);
    printf("Enter URL: %s%s\n", URL.DomainName, URL.Path);

    // printf("Getting the address info ...\n");
    GetAddressInfo();
    // printf("Gotten.\n");

    // printf("Creating socket and connect to %s\n", URL.DomainName);
    SettingSocket();
    // printf("Connected.\n");

    ConstructRequest();

    printf("Sending request ...\n");
    SendRequest();
    // printf("Sent.\n");

    printf("Receiving response ...\n");
    ReceiveResponse();
    // printf("Received.\n");
    // printf("%s Len : %d\n", Response, ResponseLength);

    // printf("Start parsing Header ...\n");
    ParseHeader();
    // printf("Finish.\n");
    // printf("HTTP/%.1lf \nStatus Code : %d\n", HTTP_Protocol, StatusCode);
    if (StatusCode != 200) {
        printf("Error : Status Code : %d. Can't get HTML files.\n", StatusCode);
        assert(false);
    }

    // printf("Start parsing HTML file ...\n");
    ParseHTML();
    // printf("Finish\n");

    printf("================= Hyperlinks =================\n");
    for (i = 0; i < Total_HREF; i++) {
        printf("%s\n", HREF[i]);
    }
    printf("==============================================\n");

    printf("There ars %d hyperlinks in http://%s/\n", Total_HREF, URL.DomainName);

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