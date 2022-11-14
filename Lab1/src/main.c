#include "HtmlParser.h"
#include "SocketHandler.h"

int main(int argc, char **argv) {
    SocketHandlerInit();
    HtmlParserInit();

    URL_Parser(argc, argv);

    SocketHandlerEnd();
    HtmlParserEnd();

    return EXIT_SUCCESS;
}