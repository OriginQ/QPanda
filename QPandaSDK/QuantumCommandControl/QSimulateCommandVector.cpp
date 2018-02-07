/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-23
Description: quantum system command vector
*****************************************************************************************************************/
#include "QSimulateCommandVector.h"


/*****************************************************************************************************************
Name:        QCommandVector
Description: structure QCommandVector
Argin:       None
Argout:      None
return:      None
*****************************************************************************************************************/
QSimulateCommandVector::QSimulateCommandVector()
{

    
    QCommand * pSelectMode = new QCommandSelectMode();
    QCommand * pLoadFile   = new QCommandLoadFile();
    QCommand * pRun        = new QCommandRun();
    QCommand * pExit       = new QCommandExit();
    QCommand * pMemory     = new QCommandMemory();
    QCommand * pCheckCUDA  = new QCommandCheckCUDA();

    mCommandMap.insert(QCPAIR("mode", pSelectMode));
    mCommandMap.insert(QCPAIR("load", pLoadFile));
    mCommandMap.insert(QCPAIR("run", pRun));
    mCommandMap.insert(QCPAIR("exit", pExit));
    mCommandMap.insert(QCPAIR("memory", pMemory));
    mCommandMap.insert(QCPAIR("checkCUDA", pCheckCUDA));
}

/*************************************************************************************************************
Name:        ~QCommandVector
Description: destruct QCommandVector
Argin:       None
Argout:      None
return:      None
*************************************************************************************************************/
QSimulateCommandVector::~QSimulateCommandVector()
{ 
    for (auto aiter :mCommandMap)
    {
        delete(aiter.second);
    }
}

/*************************************************************************************************************
Name:        commandAction
Description: command  action
Argin:       ssAction  command name
Argout:      None
return:      true or false
*************************************************************************************************************/
bool QSimulateCommandVector::commandAction(stringstream & ssAction)
{
    string sTemp;
    if (ssAction.str().empty())
    {
        return false;
    }

    getline(ssAction,sTemp, ' ');
    
    auto aiter = mCommandMap.find(sTemp);
    if (aiter != mCommandMap.end())
    {
        return aiter->second->action(ssAction,this ->mpParserProg);
    }

    cout << "error command" << endl;
    return false;
}

void QSimulateCommandVector::commandDescription()
{
    for (auto aiter : mCommandMap)
    {
        aiter.second->description();
    }
}

