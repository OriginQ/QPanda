/*********************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-23
Description: quantum system command vector 
*********************************************************************************************************/

#include "QCommand.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include "QCommandVectorBase.h"
using namespace std;

class QSimulateCommandVector:public QCommandVectorBase
{
public:
    typedef pair< std::string, QCommand* >  QCPAIR;
    /*************************************************************************************************************
    Name:        QCommandVector
    Description: structure QCommandVector
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    QSimulateCommandVector();

    /*************************************************************************************************************
    Name:        ~QCommandVector
    Description: destruct QCommandVector
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    ~QSimulateCommandVector();

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
    map<string,QCommand *>        mCommandMap;
    QPanda::QPandaSDK   *mpParserProg;

};


