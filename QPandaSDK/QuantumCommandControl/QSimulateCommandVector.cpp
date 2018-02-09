/******************************************************************************
Copyright (c) 2017-2018 Origin Quantum Computing Co., Ltd.. All Rights Reserved.


 
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at 

 	http://www.apache.org/licenses/LICENSE-2.0 
 
Unless required by applicable law or agreed to in writing, software

distributed under the License is distributed on an "AS IS" BASIS,

WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

See the License for the specific language
governing permissions and 
limitations under the License.

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

