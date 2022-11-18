#include "ResponseParser.h"

float HTTP_Protocol;
int StatusCode;
char *HREF[1000];

int temp = 0;

static int CurrentPoint;
static char *CRLF = "\r\n";

static int Char2Int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return '0';
}

static char ReadResponse(void) {
    return Response[CurrentPoint++];
}

void HtmlParserInit() {
    CurrentPoint = 0;
    StatusCode = 0;
    HTTP_Protocol = 0.0;
}

void HtmlParserEnd() {
}

void ParseHeader() {
    int i;
    // int j;
    char Buffer[500];

    // -------------------------------------------------------
    // Read HTTP/x.x_
    // -------------------------------------------------------
    for (i = 0; i < 5; i++) {
        ReadResponse();
    }
    HTTP_Protocol += Char2Int(ReadResponse()) * 1;
    ReadResponse();
    HTTP_Protocol += Char2Int(ReadResponse()) * 0.1;
    ReadResponse();

    // -------------------------------------------------------
    // Read Status Code xxx_XXX
    // -------------------------------------------------------
    StatusCode += Char2Int(ReadResponse()) * 100;
    StatusCode += Char2Int(ReadResponse()) * 10;
    StatusCode += Char2Int(ReadResponse()) * 1;
    while (true) {
        Buffer[0] = ReadResponse();
        if (Buffer[0] == CRLF[0]) {
            ReadResponse();
            break;
        }
    }

    // -------------------------------------------------------
    // Read Fields. "FieldName":_"FieldValue"
    // -------------------------------------------------------
    while (true) {
        // End of Header.
        Buffer[0] = ReadResponse();
        if (Buffer[0] == CRLF[0]) {
            ReadResponse();
            break;
        }

        // Read Field Name.
        for (i = 1;; i++) {
            Buffer[i] = ReadResponse();
            if (Buffer[i] == ':') {
                ReadResponse();
                break;
            } else if (Buffer[i] == CRLF[0]) {
                ReadResponse();
                break;
            }
        }

        // Read Field value.
        for (i = 0;; i++) {
            Buffer[i] = ReadResponse();
            if (Buffer[i] == CRLF[0]) {
                ReadResponse();
                break;
            }
        }
    }
}