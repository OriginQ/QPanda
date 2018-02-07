/****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-10
Description:the Parent of quantum logic gates class
*****************************************************************************************************************/
#ifndef _QRUNRS_PARSERAPI_H
#define _QRUNRS_PARSERAPI_H

#include "QRunesParser.h"
#include <iostream>
#include "LinkedListController.h"

#ifdef _WIN32
#define DLLAPI  _declspec(dllexport)
#elif __linux__
#define DLLAPI
#endif

using namespace std;

/*****************************************************************************************************************
Name:        QRunesParser
Description: quantum run parser 
Argin:       sFilePath        quantum program file path
             QInstructionList quantum instruction list
Argout:      QInstructionList quantum instruction list
return:      number of quantum bit 
*****************************************************************************************************************/
extern "C" DLLAPI int QRunesParser(string &sFilePath,QList &QInstructionList);

#endif
