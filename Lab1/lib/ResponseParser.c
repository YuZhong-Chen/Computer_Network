#include "ResponseParser.h"

float HTTP_Protocol;
int StatusCode;
char HREF[1000][200];
int Total_HREF;

int temp = 0;

static int CurrentResponsePoint;
static char *CRLF = "\r\n";
static char *Target = "<a href=";
static char *CommentStart = "<!--";
static char *CommentEnd = "-->";
static char Buffer[2000];
static int TargetLength;
static int CommentLength;

static int Char2Int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return '0';
}

static char ReadResponse(void) {
    return Response[CurrentResponsePoint++];
}

static bool ReadOneTag(void) {
    int i;

    // Check whether a Tag.
    if (Response[CurrentResponsePoint] != '<') {
        while (Response[CurrentResponsePoint] != '<') {
            ReadResponse();
        }
        return false;
    }

    // Check whether comment.
    if (CurrentResponsePoint + CommentLength - 1 < ResponseLength) {
        bool isComment = true;
        for (i = 0; i < 3; i++) {
            if (Response[CurrentResponsePoint + i] != CommentStart[i]) {
                isComment = false;
                break;
            }
        }
        if (isComment) {
            // Read the rest of the comment.
            while (true) {
                for (i = 0; i < 3; i++) {
                    if (ReadResponse() != CommentEnd[i]) {
                        break;
                    }
                }
                if (i == 3) {
                    break;
                }
            }

            return false;
        }
    }

    // Check whether target.
    if (CurrentResponsePoint + TargetLength - 1 < ResponseLength) {
        bool isTarget = true;
        for (i = 0; i < TargetLength; i++) {
            if (ReadResponse() != Target[i]) {
                isTarget = false;
                break;
            }
        }
        if (isTarget) {
            ReadResponse();  // Read "
            for (i = 0;; i++) {
                Buffer[i] = ReadResponse();
                if (Buffer[i] == '"') {
                    Buffer[i] = '\0';
                    break;
                }
            }
            strcpy(HREF[Total_HREF++], Buffer);
        }
    }

    // Read the rest of tags.
    while (ReadResponse() != '>') {
    }

    return true;
}

void HtmlParserInit() {
    CurrentResponsePoint = 0;
    StatusCode = 0;
    HTTP_Protocol = 0.0;
    TargetLength = strlen(Target);
    CommentLength = strlen(CommentStart) + strlen(CommentEnd);
}

void HtmlParserEnd() {
}

void ParseHeader() {
    int i;

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

void ParseHTML() {
    Total_HREF = 0;

    while (CurrentResponsePoint + TargetLength < ResponseLength) {
        ReadOneTag();
    }
}