#ifndef _RESPONSE_PARSER_H_
#define _RESPONSE_PARSER_H_

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SocketHandler.h"

void HtmlParserInit();
void HtmlParserEnd();

void ParseHeader();

extern float HTTP_Protocol;
extern int StatusCode;
extern char *HREF[1000];

extern int temp;

#endif