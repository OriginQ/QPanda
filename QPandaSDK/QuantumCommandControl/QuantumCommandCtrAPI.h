/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-23
Description: quantum system command control API
*****************************************************************************************************************/
#pragma once
#include <sstream>
using std::stringstream;

#define API _declspec(dllexport)

/*****************************************************************************************************************
Name:        QCommandVector
Description: structure QCommandVector
Argin:       None
Argout:      None
return:      None
*****************************************************************************************************************/
API bool initCommandVector(int iMode);

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

/*****************************************************************************************************************
Name:        exitCommand
Description: exit command
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
API bool exitCommand();