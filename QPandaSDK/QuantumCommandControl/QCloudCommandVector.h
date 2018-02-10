#pragma once
#include "QCommandVectorBase.h"
#include <sstream>
#include <map>
#include <iostream>
#include "QCommand.h"

class QCloudCommandVector : public QCommandVectorBase
{
public:
    typedef pair< std::string, QCommand* >  QCPAIR;
    QCloudCommandVector();
    ~QCloudCommandVector();

    /*************************************************************************************************************
    Name:        commandAction
    Description: command  action
    Argin:       ssAction  command name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool commandAction(std::stringstream & ssAction);

    /*************************************************************************************************************
    Name:        commandDescription
    Description: command  Description
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    void commandDescription();
private:
    std::map<std::string,QCommand *>        mCommandMap;
    VirtualQCHttp *                         mpVirQCHttp;

};

