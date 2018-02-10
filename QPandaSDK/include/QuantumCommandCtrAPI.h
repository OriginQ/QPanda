/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-23
Description: quantum system command control API
*****************************************************************************************************************/
#pragma once

#include "QCommandVector.h"
#define API _declspec(dllexport)

/*****************************************************************************************************************
Name:        QCommandVector
Description: structure QCommandVector
Argin:       None
Argout:      None
return:      None
*****************************************************************************************************************/
API bool initCommandVector();

/*************************************************************************************************************
Name:        ~QCommandVector
Description: destruct QCommandVector
Argin:       None
Argout:      None
return:      None
*************************************************************************************************************/
API bool deleteCommandVector();

/*****************************************************************************************************************
Name:        commandAction
Description: add Command
Argin:       pCommand  command class pointer
Argout:      None
return:      true or false
*****************************************************************************************************************/
API bool commandAction(stringstream& ssAction);
