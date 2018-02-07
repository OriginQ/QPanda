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
Description: quantum system command
*****************************************************************************************************************/
#include "QCommand.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "../QuantumCloudHTTP/VirtualQCHttp.h"
#include "../include/TinyXML/tinystr.h"
#include "../include/TinyXML/tinyxml.h"
#include "../QuantumInstructionHandle/QError.h"
#include "QSqlist.h"

using namespace std;
using namespace QPanda;

QPROGCLASS * _G_pParserProg = nullptr;
string  sDBPath = "./ConfigFile/Cloud.db";

/*****************************************************************************************************************
Name:        QCommandSelectMode:action
Description: Comannd action
Argin:       ssAction  action name
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandSelectMode::action(stringstream & ssAction,QPROGCLASS * pParserProg)
{

    if (ssAction.str().empty())
    {
        return false;
    }

   
    string sTemp;
    while (getline(ssAction, sTemp, ' '))
    {
        auto aiter = mFunction.find(sTemp);
        if (mFunction.end() != aiter)
        {
            if (aiter->second)
            {
                aiter->second();
            }
            return false;
        }
    }

    int iMode;
    try
    {
         iMode= stoi(sTemp);
    }
    catch (exception msg)
    {
        return false;
    }

#if 0
    VirtualQCHttp * test2;
    string sUrl = "https://qcode.qubitonline.cn/api/QCode/submitTask.json";
    string path = "key";
    test2 = createQCHttp(path);
    test2->getAPIKey();
    string staskID;
    test2->requstQProgram("shor_15.txt",1000,staskID);
    string sQResult;
    test2->stopQProgram(staskID);
    cout << sQResult << endl;
#endif // 0



    if (1 == iMode)
    {
        /*
        _G_modeDLL = LoadLibraryA("QParserSDK.dll");
        if (NULL == _G_modeDLL)
        {
			cout << "load dll error" << endl;
            return false;
        }
        */
    }
    return false;

}

/*****************************************************************************************************************
Name:        QCommandLoadFile:action
Description: Comannd action
Argin:       ssAction  action name
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandLoadFile::action(stringstream & ssAction,QPROGCLASS * pParserProg)
{
    if (ssAction.str().empty())
    {
        return false;
    }

    if (nullptr !=_G_pParserProg)
    {
        delete(_G_pParserProg);
        _G_pParserProg = nullptr;
    }

    string sTemp;
    string sFilePath;
    while (getline(ssAction, sTemp, ' '))
    {
        auto aiter = mFunction.find(sTemp);
        if (mFunction.end() != aiter)
        {
            if (aiter->second)
            {
                aiter->second();
            }
            return false;
        }
        sFilePath.append(sTemp.c_str());
    }

    _G_pParserProg = new QPandaAPI();
    //pParserProg = mpParserProg;
    int iQnum = 0;
    if (qErrorNone != _G_pParserProg->loadfile(sFilePath,iQnum))
    {
        return false;
    }
    return true;
}

/*****************************************************************************************************************
Name:        QCommandRun:action
Description: Comannd action
Argin:       ssAction  action name
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandRun::action(stringstream & ssAction,QPROGCLASS * pParserProg)
{
    /*
    if ((NULL == _G_modeDLL)||())
    {
        return false;
    }
    */

    mbIsHelp          = false;
    miCalculationUnit = CPU;
    string sTemp;

    vector<string> vsCommand;
    while (getline(ssAction, sTemp, ' '))
    {
        vsCommand.push_back(sTemp);
    }

    for (size_t i = 0; i < vsCommand.size(); i++)
    {
        auto aiter = mFunction.find(vsCommand[i]);
        if (mFunction.end() == aiter)
        {
            cout << "command error" << endl;
            return false;
        }
        if (aiter->first == "-n")
        {
            if (i+1 >= vsCommand.size())
            {
                return false;
            }
            int iRepeat = 0;
            try
            {
                iRepeat = atoi(vsCommand[++i].c_str());
            }
            catch (const std::exception& e)
            {
                cout << e.what() << endl;
                return false;
            }
            aiter->second(iRepeat);
        }
        else
        {
            aiter->second(0);
        }

    }

    if (mbIsHelp)
    {
        return false;
    }

    if (nullptr == _G_pParserProg)
    {
        return false;
    }

    if (qErrorNone != _G_pParserProg->setComputeUnit(miCalculationUnit))
    {
        return false;
    }

    if (miRepeat <= 0)
    {
        miRepeat = 1;
    }

    if (qErrorNone != _G_pParserProg->run(miRepeat))
    {
        return false;
    }
    /*
     *  get result
     */
    string sResult;

    if (qErrorNone != _G_pParserProg->getResult(sResult))
    {
        return false;
    }
    cout << sResult << endl;

    /*
     *  Save Results
     */
    if (mbIsO)
    {
        saveMeasure(sResult,_G_pParserProg->msFileName);
    }

    /*
     *  Save QState Results
     */
    if ((!mbIsF) && (!mbIsFB))
    {
        return true;
    }

    string sQState;
    if (qErrorNone != _G_pParserProg->getQuantumState(sQState))
    {
        return false;
    }
    if (mbIsF)
    {
        saveQstate(sQState,_G_pParserProg->msFileName);
    }

    /*
     *  Save QState Results in binary mode
     */
    if (mbIsFB)
    {
        saveQstateBinary(sQState,_G_pParserProg->msFileName);
    }

    return true;
}

int IntegerToBinary(int number, stringstream &ssRet, int ret_len)
{
    unsigned int index;
    int i = 0;

    index = 1 << (ret_len - 1);                         
    for (i = 0; i<ret_len; ++i)
    {
        ssRet << (((number&index) == 0) ? '0' : '1'); 
        index >>= 1;                          
    }
    return 1;
}

/*****************************************************************************************************************
Name:        getStringResult
Description: get String Result
Argin:       sResult                measure result
             pQuantumGateParam      quantum gate param
Argout:      pQuantumGateParam      quantum gate param
return:      true or false
*****************************************************************************************************************/
bool QCommandRun :: getStringResult(string & sResult, QuantumGateParam *pQuantumGateParam)
{
    stringstream ssResult;
    if (0 != pQuantumGateParam->mPMeasureSize)
    {
        stringstream ssBinResult;
        for (auto aiter : pQuantumGateParam->mPMeasure)
        {
            IntegerToBinary(aiter.first, ssBinResult, pQuantumGateParam->mPMeasureSize);
            ssResult << "Result = " << ssBinResult.str() << " probability = " << aiter.second << endl;
            ssBinResult.str("");
        }
    }
    else
    {
        for (auto aiter : pQuantumGateParam->mReturnValue)
        {
            ssResult << "CREG = " << aiter.first << " VALUE = " << aiter.second << endl;
        }
    }
    sResult = ssResult.str();
    return true;
}

/*****************************************************************************************************************
Name:        saveMeasure
Description: save Measure
Argin:       sResult measure result
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandRun::saveMeasure(string &sResult,string sFilePath)
{
    stringstream ssFilePath;

    if (0 == sFilePath.size())
    {
        return false;
    }

    ssFilePath << sFilePath << ".o";

    ofstream fout;

    fout.open(ssFilePath.str(), ios::out | ios::app);
    if (!fout)
    {
        cout << "open file error" << endl;
        return false;
    }

    fout.write(sResult.c_str(), sResult.size());
    fout.close();

    return true;
}

/*****************************************************************************************************************
Name:        saveQstate
Description: save QState
Argin:       qsResult quantum state  result
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandRun::saveQstate(string & qsResult,string sFilePath)
{
    stringstream ssFilePath;

    if (0 == sFilePath.size())
    {
        return false;
    }

    ssFilePath << sFilePath << ".fullstate";

    ofstream fout;

    fout.open(ssFilePath.str(), ios::out);
    if (!fout)
    {
        cout << "open file error" << endl;
        return false;
    }

    int i = 0;

    fout << qsResult;

    fout.close();
    return true;
}

/*****************************************************************************************************************
Name:        saveQstateBinary
Description: save QState
Argin:       qsResult quantum state  result
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandRun::saveQstateBinary(string & qsResult,string sFilePath)
{
    stringstream ssFilePath;

    ssFilePath << sFilePath << ".fullstate.binary";

    ofstream fout;

    fout.open(ssFilePath.str(), ios::out | ios::binary);
    if (!fout)
    {
        cout << "open file error" << endl;
        return false;
    }

    struct dcomplex
    {
        double real;
        double imag;
    };

    dcomplex state;

    string sTemp;
    stringstream ssTemp;
    ssTemp << qsResult;
    while (getline(ssTemp,sTemp,'\n'))
    {
        string sMyTemp;
        stringstream ssMyTemp;
        int i = 0;
        ssMyTemp << sTemp;
        while (getline(ssMyTemp, sMyTemp, '\n'))
        {
            if (i == 0)
            {
                 state.real = atof(sMyTemp.c_str());
            }
            else
            {
                state.imag = atof(sMyTemp.c_str());
            }
            i++;
        }
        fout.write((char *)&state, sizeof(state));
    }


    fout.close();
    return true;
}

/*****************************************************************************************************************
Name:        QCommandExit:actiom
Description: Comannd action
Argin:       ssAction  action name
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandExit::action(stringstream & ssAction,QPROGCLASS * pParserProg)
{
    /*
    if (NULL == _G_modeDLL)
    {
        return true;
    }
    */
    string sTemp;
    while (getline(ssAction, sTemp, ' '))
    {
        auto aiter = mFunction.find(sTemp);
        if (mFunction.end() != aiter)
        {
            if (aiter->second)
            {
                aiter->second();
            }
            return false;
        }
    }

    delete(_G_pParserProg);
    //FreeLibrary(_G_modeDLL);
    return true;
}

/*****************************************************************************************************************
Name:        QCommandMemory:actiom
Description: Comannd action
Argin:       ssAction  action name
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandMemory::action(stringstream & ssAction,QPROGCLASS * pParserProg)
{
    string sTemp;
    while (getline(ssAction, sTemp, ' '))
    {
        auto aiter = mFunction.find(sTemp);
        if (mFunction.end() != aiter)
        {
            if (aiter->second)
            {
                aiter->second();
            }
            return false;
        }
    }

    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);

    GlobalMemoryStatusEx(&statex);

    cout << "Memory : " << statex.ullAvailPhys / 1024 << "KB" << endl;
    
    return true;
}

/*****************************************************************************************************************
Name:        QCommandCheckCUDA:actiom
Description: Comannd action
Argin:       ssAction  action name
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandCheckCUDA::action(stringstream & ssAction,QPROGCLASS * pParserProg)
{
    string sTemp;
    while (getline(ssAction, sTemp, ' '))
    {
        auto aiter = mFunction.find(sTemp);
        if (mFunction.end() != aiter)
        {
            if (aiter->second)
            {
                aiter->second();
            }
            return false;
        }
    }

    auto state = system("nvcc -V");
    if (0 != state)
    {
        return false;
    }
    return true;
}

/*****************************************************************************************************************
Name:        QCommandSubmit:actiom
Description: Comannd action
Argin:       ssAction  action name
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandSubmit::action(stringstream & ssAction, VirtualQCHttp * mpVirQCHttp)
{
    if (nullptr != mpVirQCHttp)
    {
        return true;
    }

    string sTemp;
    string sFilePath;
    vector<string> vsCommand;

    while (getline(ssAction, sTemp, ' '))
    {
        vsCommand.push_back(sTemp);
    }

    if ((vsCommand.size() <2)||(vsCommand.size()>3))
    {
        cout << "command fail" << endl;
        return false;
    }

    int i;
    int iRepeat = 1;
    for (i =0 ; i < vsCommand.size(); i++)
    {
        if (vsCommand[i]=="-n")
        {
            iRepeat = atoi(vsCommand[i + 1].c_str());
            auto atier = mFunction.find(vsCommand[i]);
            atier->second(iRepeat);
            break;
        }
    }

    if (mbIsHelp)
    {
        return true;
    }

    if (miRepeat == 0)
    {
        return true;
    }

    if (0 == i)
    {
        sFilePath.append(vsCommand[i+2]);
    }
    else if (1 == i)
    {
        sFilePath.append(vsCommand[i-1]);
    }

    string sKeyPath = "./ConfigFile/key";
    mpVirQCHttp = createQCHttp(sKeyPath);
    
    if (!mpVirQCHttp->getAPIKey())
    {
        cout << "get api key fail" << endl;
        return false;
    }
    string sTaskID;
    if (!mpVirQCHttp->requestQProgram(sFilePath, miRepeat, sTaskID))
    {
        cout << "request http fail" << endl;
        return false;
    }
    
    stringstream  ssSQL;
    ssSQL << "insert into CloudTask(TaskID,TaskSta) values(" << sTaskID << ", 2);"
        << "select TaskID,TaskSta from CloudTask;";
    char *  cpError = nullptr;
    try
    {
        QSqlite::QSQLite * pSql = QSqlite::QSQLite::getIntance(sDBPath);
        if (!pSql->execSQL(ssSQL.str(), cpError))
        {
            cout << "insert DB fail" << endl;
            return false;
        }
    }
    catch (const std::exception&e)
    {
        cout << e.what() << endl;

        return false;
    }
    cout << "submit success" << endl;
    return true;
}

/*****************************************************************************************************************
Name:        action
Description: Comannd action
Argin:       ssAction  action name
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandTaskList::action(stringstream & ssAction, VirtualQCHttp * mpVirQCHttp)
{


    string sTemp;

    while (getline(ssAction, sTemp, ' '))
    {
        auto aiter = mFunction.find(sTemp);
        if (mFunction.end()!= aiter)
        {
            aiter->second();
        }
    }

    if (mbIsHelp)
    {
        return true;
    }

    string  sSQL    = "select TaskID,TaskSta from CloudTask order by TaskID desc limit 0,10;";
    char *  cpError = nullptr;

    QSqlite::QSQLite * pSql = QSqlite::QSQLite::getIntance(sDBPath);

    if (!pSql->execSQL(sSQL, cpError))
    {
        cout << "get task list fail" << endl;
        return false;
    }

    return true;
}

/*****************************************************************************************************************
Name:        action
Description: Comannd action
Argin:       ssAction  action name
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QCommandGetResult::action(stringstream & ssAction, VirtualQCHttp * mpVirQCHttp)
{
    if (0 == ssAction.str().size())
    {
        return false;
    }

    string         sTemp;

    vector<string> vsCommand;

    while (getline(ssAction, sTemp, ' '))
    {
        vsCommand.push_back(sTemp);
    }

    if (vsCommand.size() < 1)
    {
        return false;
    }

    auto aSubIte = mFunction.find(vsCommand[0]);
    if (aSubIte != mFunction.end())
    {
        aSubIte->second();
    }

    if (mbIsHelp)
    {
        return true;
    }

    if (nullptr == mpVirQCHttp)
    {
        string sKeyPath = "./ConfigFile/key";
        mpVirQCHttp = createQCHttp(sKeyPath);
    
        if (!mpVirQCHttp->getAPIKey())
        {
            cout << "get api key fail" << endl;
            return false;
        }
    }

    string sQResult;
    if (!mpVirQCHttp->requsetQProgramResult(vsCommand[0], sQResult))
    {
        cout << "no result" << endl;
        return false;
    }

    cout << sQResult << endl;

    stringstream ssSQL;
    ssSQL << "update CloudTask set TaskSta = 3 where TaskID = "<<vsCommand[0]<<';';
    char *  cpError = nullptr;

    QSqlite::QSQLite * pSql = QSqlite::QSQLite::getIntance(sDBPath);

    if (!pSql->execSQL(ssSQL.str(), cpError))
    {
        cout << "update data fail" << endl;
        return false;
    }
    
    return true;
}

/*****************************************************************************************************************
Name:        readXML
Description: read xml
Argin:       name command name
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool readXML(char * name)
{
    TiXmlDocument helpDoc("./ConfigFile/help.xml");

    bool loadOk = helpDoc.LoadFile();
    if (!loadOk)
    {
        return false;
    }

    TiXmlElement *pRootElement = helpDoc.RootElement();
    TiXmlElement *pSonElement;
    for (pSonElement = pRootElement->FirstChildElement();
        pSonElement != NULL;
        pSonElement = pSonElement->NextSiblingElement())
    {
        if (0 == strcmp(name, pSonElement->Attribute("name")))
        {
            break;
        }
    }
    if (NULL == pSonElement)
    {
        return false;
    }
    TiXmlElement *checkCUDAElementDes = pSonElement->FirstChildElement();

    for (TiXmlElement * pLineElement = checkCUDAElementDes->FirstChildElement();
        pLineElement != NULL;
        pLineElement = pLineElement->NextSiblingElement())
    {
        cout << pLineElement->GetText() << endl;
    }
    cout << endl;
    return true;
}

/*****************************************************************************************************************
Name:        QCommandSubmit:description
Description: description Command
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
void QCommandSubmit::description()
{
    readXML("submit");
}

/*****************************************************************************************************************
Name:        QCommandCheckCUDA:description
Description: description Command
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
void QCommandCheckCUDA::description()
{
    readXML("checkCUDA");
}

/*****************************************************************************************************************
Name:        QCommandMemory:description
Description: description Command
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
void QCommandMemory::description()
{
    readXML("memory");
}

/*****************************************************************************************************************
Name:        QCommandSelectMode:description
Description: description Command
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
void QCommandSelectMode::description()
{
    readXML("mode");
}

/*****************************************************************************************************************
Name:        QCommandLoadFile:description
Description: description Command
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
void QCommandLoadFile::description()
{
    readXML("load");
}

/*****************************************************************************************************************
Name:        QCommandRun:description
Description: description Command
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
void QCommandRun::description()
{
    readXML("run");

}



/*****************************************************************************************************************
Name:        QCommandExit:description
Description: description Command
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
void QCommandExit::description()
{
    readXML("exit");
}


/*****************************************************************************************************************
Name:        QCommandTaskList:description
Description: description Command
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
void QCommandTaskList::description()
{
    readXML("tasklist");
}

/*****************************************************************************************************************
Name:        description
Description: description Command
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
void QCommandGetResult::description()
{
    readXML("getresult");
}
