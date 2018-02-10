#ifndef _QRUNES_PARSER_H
#define _QRUNES_PARSER_H

#ifdef _WIN32
#define API _declspec(dllexport)
#elif __linux__
#endif

#include "LinkedListController.h"
API int parser(const char* filename, QList & parser);

#endif
