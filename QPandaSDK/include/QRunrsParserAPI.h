/*********************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-10
Description:the Parent of quantum logic gates class
*********************************************************************************************************/
#pragma once
#include "QRunesParser.h"
#include <iostream>
#include "LinkedListController.h"
#define API _declspec(dllexport)

using namespace std;

/*****************************************************************************************************************
Name:        QRunesParser
Description: quantum run parser 
Argin:       sFilePath        quantum program file path
             QInstructionList quantum instruction list
Argout:      QInstructionList quantum instruction list
return:      number of quantum bit 
*****************************************************************************************************************/
API int QRunesParser(string &sFilePath,QList &QInstructionList);
