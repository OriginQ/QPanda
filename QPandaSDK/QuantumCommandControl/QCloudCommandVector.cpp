#include "QCloudCommandVector.h"



QCloudCommandVector::QCloudCommandVector()
{
    QCommand * pSubmit    = (QCommand *)new QCommandSubmit;
    QCommand * pTaskList  = (QCommand *)new QCommandTaskList;
    QCommand * pGetResult = (QCommand *)new QCommandGetResult;

    mCommandMap.insert(QCPAIR("submit",pSubmit));
    mCommandMap.insert(QCPAIR("tasklist",pTaskList));
    mCommandMap.insert(QCPAIR("getresult",pGetResult));
}


QCloudCommandVector::~QCloudCommandVector()
{
    for (auto aiter :mCommandMap)
    {
        delete(aiter.second);
    }
}
/*****************************************************************************************************************
Name:        commandAction
Description: command  action
Argin:       ssAction  command name
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCloudCommandVector::commandAction(std::stringstream & ssAction)
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
        return aiter->second->action(ssAction,this->mpVirQCHttp);
    }

    cout << "error command" << endl;
    return false;
}

void QCloudCommandVector::commandDescription()
{
    for (auto aiter : mCommandMap)
    {
        aiter.second->description();
    }
}

