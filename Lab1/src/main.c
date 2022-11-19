#include "ResponseParser.h"
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
    printf("Enter URL: %s%s\n", URL.DomainName, URL.Path);

    GetAddressInfo();

    SettingSocket();

    ConstructRequest();

    printf("Sending request ...\n");
    SendRequest();

    printf("Receiving response ...\n");
    ReceiveResponse();

    ParseHeader();

    if (StatusCode != 200) {
        printf("Warning : Status Code is %d, not 200.\n", StatusCode);
        // assert(false);
    }

    ParseHTML();

    int i;
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