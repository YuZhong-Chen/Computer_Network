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
void ParseHTML();

extern float HTTP_Protocol;
extern int StatusCode;
extern char HREF[1000][200];
extern int Total_HREF;

extern int temp;

#endif