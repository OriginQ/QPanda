#pragma once
#define API _declspec(dllexport)
#include "LinkedListController.h"
API int parser(const char* filename, QList & parser);