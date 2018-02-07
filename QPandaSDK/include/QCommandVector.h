/*********************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-23
Description: quantum system command vector 
*********************************************************************************************************/
#pragma once

#include "QCommand.h"
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
using std::vector;


class QCommandVector
{
public:
    /*************************************************************************************************************
    Name:        QCommandVector
    Description: structure QCommandVector
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    QCommandVector();

    /*************************************************************************************************************
    Name:        ~QCommandVector
    Description: destruct QCommandVector
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    ~QCommandVector();

    /*************************************************************************************************************
    Name:        AddCommand
    Description: add Command
    Argin:       pCommand  command class pointer
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool AddCommand(QCommand* pCommand);
    /*************************************************************************************************************
    Name:        commandAction
    Description: command  action
    Argin:       ssAction  command name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool commandAction(stringstream & ssAction);

    /*************************************************************************************************************
    Name:        commandDescription
    Description: command  Description
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    void commandDescription();



private:
    vector<QCommand *> mCommandVector;

};


