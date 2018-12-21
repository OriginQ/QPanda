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
Date:2017-02-01
Description: quantum cloud http
*****************************************************************************************************************/
#include <sstream>
#include <fstream>
#include <string>
#include "QuantumCloudHTTP.h"

#include <algorithm>
using std::string;
using std::ifstream;
using std::stringstream;
using namespace Json;

#define COMPUTEAPI    "https://qcode.qubitonline.cn/api/QCode/submitTask.json"
#define INQUREAPI     "https://qcode.qubitonline.cn/api/QCode/queryTask.json"
#define TERMINATEAPI  "https://qcode.qubitonline.cn/api/QCode/terminateTask.json"

#define GET_RESPONSE        if (!requestHttps(sUrl, sJson, root)) \
                            { \
                                return false; \
                            }\
                            bool bSuccess = root["success"].asBool(); \
                            if (!bSuccess) \
                            { \
                                return false; \
                            }

QuantumCloudHTTP::QuantumCloudHTTP(std::string & sKeyFilePath) : 
    msKeyFilePath(sKeyFilePath),
    mpv(nullptr),
    mpDict(nullptr),
    mpModule(nullptr)
{
    Py_Initialize();
    ifstream fin;
    string temp;
    fin.open("./ConfigFile/HTTPFile", std::ios::in);
    int i = 0;
    while (std::getline(fin, temp, '\n'))
    {
        switch (i)
        {
        case 0 :
            msComputeAPI = temp;
            break;
        case 1:
            msInqureAPI = temp;
            break;
        case 2:
            msTerminateAPI = temp;
        default:
            break;
        }
        i++;
    }

    string      sPyPath("../include");
    string      sDirCmd = string("sys.path.append(\"") + sPyPath + "\")";
    const char *pcDirCmd = sDirCmd.c_str();


    PyRun_SimpleString("import  sys"); // Ö´ÐÐ python ÖÐµÄ¶ÌÓï¾ä  
    PyRun_SimpleString("print('come in python')");
    PyRun_SimpleString("sys.path.append('./')");


    mpModule = PyImport_ImportModule("https");
    if (!mpModule)
    {
        PyErr_Print();
        std::cout << "can not find https.py" << std::endl;
        return ;
    }
    else
        std::cout << "open Module" << std::endl;
    mpDict = PyModule_GetDict(mpModule);
    mpv = PyDict_GetItemString(mpDict, "requestHttps");
}

QuantumCloudHTTP::~QuantumCloudHTTP()
{
    Py_DECREF(mpDict);
    Py_DECREF(mpModule);
    Py_Finalize();
}
/*****************************************************************************************************************
Name:        requestQProgram
Description: request quantum program
Argin:       sFilePath  quantum program file path
             iRepeat    quantum program repeat
Argout:      sTaskID    task id
return:      true or false
*****************************************************************************************************************/
bool QuantumCloudHTTP::requestQProgram(std::string  sFilePath,
                                       int          iRepeat,
                                       std::string &sTaskID)
{
    if (0 == sFilePath.size())
    {
        return false;
    }
    Value        root;
    Value        vJson;

    ifstream     fin;
    stringstream sscontent;
    string       sJson;
    string       sUrl(msComputeAPI);
        
    int          iTaskType = 0;
    int          iQum;

    fin.open(sFilePath, std::ios::in);
    if (!fin)
    {
        return false;
    }

    sscontent << fin.rdbuf();

    fin.seekg(0, std::ios::beg);

    iQum = getQnumAndTaksType(fin, iTaskType);

    if (iQum <= 0)
    {
        return false;
    }
    
    fin.close();

    vJson["qprog"] = Json::Value(sscontent.str());
    stringstream ssRepeat;
    ssRepeat << iRepeat;
    switch (iTaskType)
    {
    case 2:
        vJson["typ"] = Json::Value("mcpr");
        vJson["repeat"] = Json::Value(ssRepeat.str());
        break;
    case 3:
        vJson["typ"] = Json::Value("smapr");
        break;
    case 4:
        vJson["typ"] = Json::Value("midpr");
        break;
    default:
        return false;
    }

    vJson["token"] = Json::Value(msAPIKey);
    vJson["meaarr"] = Json::Value("{1,10}");
    vJson["taskTyp"] = Json::Value(iTaskType);
   
    sJson = vJson.toStyledString();
 
    GET_RESPONSE

    sTaskID.append(root["obj"]["taskid"].asCString());
    return true;
}

/*****************************************************************************************************************
Name:        requsetQProgramResult
Description: request quantum program result
Argin:       sTaskID  task id
Argout:      sQResult quantum result    
return:      true or false
*****************************************************************************************************************/
bool QuantumCloudHTTP::requsetQProgramResult(const std::string &sTaskID, std::string &sQResult)
{
    if (0 == sTaskID.size())
    {
        return false;
    }

    string sUrl(msInqureAPI);
    string sJson;
    string sTaskSta;
    int    iTaskSta;

    Value  vJson;
    Value  root;

    vJson["impTyp"] = Json::Value(1);
    vJson["taskTyp"] = Json::Value("mcpr");
    vJson["token"] = Json::Value(msAPIKey);
    vJson["typ"] = Json::Value("qrytask");
    std::cout << sTaskID << std::endl;
    vJson["taskid"] = Json::Value(sTaskID.c_str());
   
    sJson = vJson.toStyledString();
    
    try
    {
        GET_RESPONSE
    }
    catch (const std::exception&e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }


    sTaskSta = root["obj"]["tasksta"].asString();
    iTaskSta = atoi(sTaskSta.c_str());

    if (iTaskSta == 3)
    {
        Value        vTaskRS;
        Reader       rTaskRS;
        stringstream ssTaskRS;

        ssTaskRS << root["obj"]["taskrs"].asString();
        rTaskRS.parse(ssTaskRS, vTaskRS);
        if (vTaskRS["key"].isArray())
        {
            int i        = 0;
            int iRsArray = vTaskRS["key"].size();
            stringstream ssTemp;

            for (;i<iRsArray;i++)
            {
                ssTemp << vTaskRS["key"][i].asCString()<< " : " << vTaskRS["value"][i];
            }
            sQResult.append(ssTemp.str());
        }
        return true;
    }
    return false;
}

/*****************************************************************************************************************
Name:        stopQProgram
Description: stop quantum program 
Argin:       sTaskID  task id
Argout:      None  
return:      true or false
*****************************************************************************************************************/
bool QuantumCloudHTTP::stopQProgram(std::string sTaskID)
{
    if (0 == sTaskID.size())
    {
        return false;
    }

    string sJson;
    string sUrl(msTerminateAPI);

    Value  vJson;
    Value  root; 

    int iTaskSta;

    vJson["impTyp"] = Json::Value(2);
    vJson["taskTyp"] = Json::Value(2);
    vJson["token"] = Json::Value(msAPIKey);
    vJson["typ"] = Json::Value("updtask");
    vJson["taskid"] = Json::Value(sTaskID.c_str());
   
    sJson = vJson.toStyledString();

    try
    {
        GET_RESPONSE
    }
    catch (const std::exception&e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    iTaskSta = root["obj"]["tasksta"].asInt();

    if (4 == iTaskSta)
    {
        return true;
    }

    return false;
}

/*****************************************************************************************************************
Name:        getAPIKey
Description: get api key
Argin:       None
Argout:      None  
return:      true or false
*****************************************************************************************************************/
bool QuantumCloudHTTP::getAPIKey()
{
    if (0 != msAPIKey.size())
    {
        return false;
    }

    ifstream    fout;
    std::string sTemp;

    fout.open(msKeyFilePath, std::ios::out);
    if (!fout)
    {
        return false;
    }

    if (!getline(fout, sTemp, '\n'))
    {
        return false;
    }
    
    if (0 == sTemp.size())
    {
        return false;
    }

    msAPIKey.append(sTemp);
    fout.close();
    return true;
}

/*****************************************************************************************************************
Name:        getQnumAndTaksType
Description: get quantum bit and task type
Argin:       fin         file stream
Argout:      iTaskType   task type
return:      true or false
*****************************************************************************************************************/
int QuantumCloudHTTP::getQnumAndTaksType(ifstream &fin,int & iTaskType)
{
    int    iQnum = 0;
    string sTemp;

    stringstream ssBuf; 
    ssBuf << fin.rdbuf();

    fin.seekg(0, std::ios::beg);

    /*
     * get the number of quantum bit through  QINT 
     */
    while (getline(fin,sTemp,'\n'))
    {
        auto aSharp = sTemp.find('#');
        if (aSharp == 0)
        {
            continue;
        }

        auto aPos = sTemp.find("QINIT");

        if (aPos != sTemp.npos)
        {
            int i = 0;

            stringstream ssLine;
            string       sSubTemp;

            ssLine << sTemp;
            
            while (getline(ssLine,sSubTemp,' '))
            {
                if (1 == i)
                {
                    iQnum = atoi(sSubTemp.c_str());
                }
                i++;
            }
        }
    }

    if (iQnum <= 0)
    {
        return -1;
    }

    string content(ssBuf.str());
    size_t stPmeasure = 0;

    /*
     * find PMEASURE
     */
    do
    {
        stPmeasure = content.rfind("PMEASURE");
        if (stPmeasure ==content.npos)
        {
            iTaskType = 2;
            break;
        }

        if (content[stPmeasure-1]=='\n')
        {
            if (iQnum > 20)
            {
                iTaskType = 4;
                break;
            }
            else
            {
                iTaskType = 3;
                break;
            }
        }
    } while (stPmeasure = (content.rfind("PMEASURE"),stPmeasure-1)!=content.npos);

    if (0 == iTaskType)
    {
        return -1;
    }
    return iQnum;
}

/*****************************************************************************************************************
Name:        requestHttps
Description: request https
Argin:       sUrl         url string
             sJson        request json string
Argout:      root         json value
return:      true or false
*****************************************************************************************************************/
bool QuantumCloudHTTP::requestHttps(const string &sUrl,string & sJson,Value &root)
{


    try
    {


        PyObject* pArgs = Py_BuildValue("ss", sUrl.c_str(), sJson.c_str());
        if (nullptr == mpv)
        {
            return false;
        }
        PyObject* pRet = PyObject_CallObject(mpv, pArgs);
        PyErr_Print();
        if (!pRet)
        {
            return false;
        }
        char *  ssRet;
        int a = 0;
        PyArg_ParseTuple(pRet, "si", &ssRet, &a);
        Reader rJson;
        return rJson.parse(ssRet, root);
    }
    catch (const std::exception&e)
    {
        std::cout << "hahahha"<< std::endl;
        std::cout << e.what() << std::endl;
        return false;
    }

}
