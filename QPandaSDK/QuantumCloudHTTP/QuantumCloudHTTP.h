/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-02-01
Description: quantum cloud http
*****************************************************************************************************************/
#ifndef _QUANTUM_CLOUD_HTTP_H
#define _QUANTUM_CLOUD_HTTP_H
 
#include <iostream>
#include <fstream>
#include "json/json.h"
#include "json/forwards.h"
#include "VirtualQCHttp.h"
#include "python.h" 
class QuantumCloudHTTP:public VirtualQCHttp
{
private:
    PyObject * mpv = nullptr;
    PyObject * mpDict = nullptr;
    PyObject * mpModule = nullptr;
public:
    QuantumCloudHTTP(std::string &sKeyFilePath);
    ~QuantumCloudHTTP();
    /*************************************************************************************************************
    Name:        requestQProgram
    Description: request quantum program
    Argin:       sFilePath  quantum program file path
                 iRepeat    quantum program repeat
    Argout:      sTaskID    task id
    return:      true or false
    *************************************************************************************************************/
    bool requestQProgram(std::string sFilePath,int repeat, std::string &sTaskID);

    /*************************************************************************************************************
    Name:        requsetQProgramResult
    Description: request quantum program result
    Argin:       sTaskID  task id
    Argout:      sQResult quantum result    
    return:      true or false
    *************************************************************************************************************/
    bool requsetQProgramResult(const std::string &sTaskID, std::string &sQResult);

    /*************************************************************************************************************
    Name:        stopQProgram
    Description: stop quantum program 
    Argin:       sTaskID  task id
    Argout:      None  
    return:      true or false
    *************************************************************************************************************/
    bool stopQProgram(std::string sTaskID);

    /*************************************************************************************************************
    Name:        getAPIKey
    Description: get api key
    Argin:       None
    Argout:      None  
    return:      true or false
    *************************************************************************************************************/
    bool getAPIKey();


private:
     
    std::string msAPIKey;
    std::string msKeyFilePath;
    std::string msComputeAPI;
    std::string msInqureAPI;
    std::string msTerminateAPI;
    /*************************************************************************************************************
    Name:        getQnumAndTaksType
    Description: get quantum bit and task type
    Argin:       fin         file stream
    Argout:      iTaskType   task type
    return:      true or false
    *************************************************************************************************************/
    int getQnumAndTaksType(std::ifstream &fin,int & iTaskType);

    /*************************************************************************************************************
    Name:        requestHttps
    Description: request https
    Argin:       sUrl         url string
                 sJson        request json string
    Argout:      root         json value
    return:      true or false
    *************************************************************************************************************/
    bool requestHttps(const std::string &sUrl, std::string & sJson, Json::Value &root);
};

#endif // !_QUANTUM_CLOUD_HTTP_H