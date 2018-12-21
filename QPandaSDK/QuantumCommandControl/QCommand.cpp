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
#include "QuantumCloudHTTP/VirtualQCHttp.h"
#include "TinyXML/tinystr.h"
#include "TinyXML/tinyxml.h"
#include "QuantumInstructionHandle/QError.h"
#include "QSqlist.h"
#include <regex>
using namespace std;
using namespace QPanda;

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
    string sAction(ssAction.str());
    regex  pattern("(( )(.+))");
    smatch results;
    string::const_iterator start = sAction.begin();
    string::const_iterator end = sAction.end();
    if (regex_search(start, end, results, pattern))
    {
        string sTemp(results[1].str());
        sTemp.erase(0,sTemp.find_first_not_of(" "));
        if (2 == loadFileAPI((char *)(sTemp.c_str())))
        {
            return true;
        }
    }
    return false;
}


void QCommandRun::regexAction(string & sAction, const string & action)
{
    stringstream ssAction;
    string::const_iterator start = sAction.begin();
    string::const_iterator end = sAction.end();
    ssAction << "(" << action << ")" << "{1}";
    string sRegex(ssAction.str());
    regex pattern(sRegex);
    smatch result;
    if (regex_search(start, end, result, pattern))
    {
        string sTemp(result[1].str());
        auto aiter = mFunction.find(action);
        if (aiter != mFunction.end())
        {
            aiter->second();
        }
    }
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
    mbIsHelp          = false;
    miCalculationUnit = CPU;
    miRepeat = 0;
    string sAction(ssAction.str());
    string::const_iterator start = sAction.begin();
    string::const_iterator end = sAction.end();

    regex iRepeatPattern("(-n( )(.*)){1}");
    smatch iRepeatResult;
    if (regex_search(start, end, iRepeatResult, iRepeatPattern))
    {
        string sTemp(iRepeatResult[1].str());
        string::const_iterator start = sTemp.begin();
        string::const_iterator end = sTemp.end();
        regex pattern("((( )(.*))|(( )(.*)( ))){1}");
        smatch result;
        if (regex_search(start, end, result, pattern))
        {
            miRepeat = atoi(result[1].str().c_str());
        }
        else
        {
            cout << "repeat error" << endl;
            return false;
        }
    }
    else
    {
        regex pattern("(-n){1}");
        smatch result;
        if (regex_search(start, end, result, pattern))
        {
            miRepeat = 0;
        }
        else
        {
            miRepeat = 1;
        }
    }

    for ( auto aiter : mFunction)
    {
        regexAction(sAction, aiter.first);
    }
    
    if (mbIsHelp)
    {
        return false;
    }

    if (qErrorNone != setComputeUnitAPI(miCalculationUnit))
    {
        return false;
    }

    if (miRepeat <= 0)
    {
        cout << "repeat error" << endl;
        return false;
    }

    if (2 != runAPI(miRepeat))
    {
        return false;
    }
    /*
     *  get result
     */
    char * pcTempBuf = nullptr;
    int iResultLength = 0;

    getResultAPI(pcTempBuf,&iResultLength);

    char * pcResult = new char[iResultLength+1];
    memset(pcResult, 0, iResultLength + 1);

    getResultAPI(pcResult, &iResultLength);
    string sResult(pcResult);
    cout << sResult << endl;


    int iFileNameLength = 0;

    getResultAPI(pcTempBuf, &iFileNameLength);

    char * pcFileName = new char[iFileNameLength + 1];
    memset(pcFileName, 0, iFileNameLength + 1);

    getFileNameAPI(pcFileName, &iFileNameLength);
    string sFileName(pcFileName);

    /*
     *  Save Results
     */
    if (mbIsO)
    {
        saveMeasure(sResult, sFileName);
    }

    /*
     *  Save QStat Results
     */
    if ((!mbIsF) && (!mbIsFB))
    {
        delete [] pcResult;
        return true;
    }

    int iQStatLength = 0;

    getQuantumStateAPI(pcTempBuf, &iQStatLength);

    char * pcQStat = new char[iQStatLength+1];
    memset(pcQStat, 0, iQStatLength + 1);
    getQuantumStateAPI(pcQStat, &iQStatLength);
    string sQStat(pcQStat);
    cout << sQStat << endl;
    if (mbIsF)
    {
        saveQstate(sQStat,sFileName);
    }

    /*
     *  Save QState Results in binary mode
     */
    if (mbIsFB)
    {
        saveQstateBinary(sQStat, sFileName);
    }


    delete [] pcQStat;
    delete [] pcResult;
    delete[]pcFileName;

    mbIsF = false;
    mbIsFB = false;
    return true;
}

int IntegerToBinary(size_t number, stringstream &ssRet, size_t ret_len)
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
    miRepeat = 0;
    mbIsHelp = false;
    string sFilePath;
    string sAction(ssAction.str());
    string::const_iterator start = sAction.begin();
    string::const_iterator end = sAction.end();

    regex helpPattern("(-help){1}");
    smatch helpResult;
    if (regex_search(start, end, helpResult, helpPattern))
    {
        mbIsHelp = true;
    }

    if (mbIsHelp)
    {
        description();
        return true;
    }

    regex iRepeatPattern("(-n( )(.*)){1}");
    smatch iRepeatResult;
    if (regex_search(start, end, iRepeatResult, iRepeatPattern))
    {
        string sTemp(iRepeatResult[1].str());
        string::const_iterator start = sTemp.begin();
        string::const_iterator end = sTemp.end();
        regex pattern("((( )(.*))|(( )(.*)( ))){1}");
        smatch result;
        if (regex_search(start, end, result, pattern))
        {
            miRepeat = atoi(result[1].str().c_str());
            
        }
        else
        {
            cout << "repeat error" << endl;
            return false;
        }
    }
    else
    {
        regex pattern("(-n){1}");
        smatch result;
        if (regex_search(start, end, result, pattern))
        {
            miRepeat = 0;
        }
        else
        {
            miRepeat = 1;
        }
    }

    if ((miRepeat <= 0)||(miRepeat >9999))
    {
        cout << "repeat error" << endl;
        return false;
    }

    regex filePathPattern("((( )(.+)( ))|(( )(.+))){1}");
    smatch filePathResult;
    if (regex_search(start, end, filePathResult, filePathPattern))
    {
        string sTemp(filePathResult[1].str());
        string::const_iterator start = sTemp.begin();
        string::const_iterator end = sTemp.end();
        regex pattern("-n");
        smatch result;
        if (regex_search(start, end, result, pattern))
        {
            sFilePath.append(regex_replace(sTemp, pattern, ""));
        }
        else
        {
            sFilePath.append(sTemp);
        }
        sFilePath.erase(0, sFilePath.find_first_not_of(" "));
        sFilePath.erase(sFilePath.find_last_not_of(" ") + 1);
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
    mbIsHelp = false;

    string sAction(ssAction.str());
    string::const_iterator start = sAction.begin();
    string::const_iterator end = sAction.end();

    regex helpPattern("(-help){1}");
    smatch helpResult;
    if (regex_search(start, end, helpResult, helpPattern))
    {
        mbIsHelp = true;
    }

    if (mbIsHelp)
    {
        description();
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
    mbIsHelp = false;

    string sAction(ssAction.str());
    string::const_iterator start = sAction.begin();
    string::const_iterator end = sAction.end();

    regex helpPattern("(-help){1}");
    smatch helpResult;
    if (regex_search(start, end, helpResult, helpPattern))
    {
        mbIsHelp = true;
    }

    if (mbIsHelp)
    {
        description();
        return true;
    }

    string taskID;
    regex  pattern("(( )(.+))");
    smatch results;
    if (regex_search(start, end, results, pattern))
    {
        taskID.append(results[1].str());
        taskID.erase(0, taskID.find_first_not_of(" "));
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
    if (!mpVirQCHttp->requsetQProgramResult(taskID, sQResult))
    {
        cout << "no result" << endl;
        return false;
    }

    cout << sQResult << endl;

    stringstream ssSQL;
    ssSQL << "update CloudTask set TaskSta = 3 where TaskID = "<< taskID <<';';
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
