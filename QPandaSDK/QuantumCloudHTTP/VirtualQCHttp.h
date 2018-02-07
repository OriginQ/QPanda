#pragma once
#include <iostream>
#ifdef _WIN32
#define DLL_EXPORTS
#ifdef DLL_EXPORTS
#define DLL_EXPORTS_API __declspec(dllexport)
#else
#define DLL_EXPORTS_API __declspec(dllimport)
#endif
#elif __linux__
#define DLL_EXPORTS_API  
#endif
class DLL_EXPORTS_API VirtualQCHttp
{
public:
    VirtualQCHttp();
    virtual ~VirtualQCHttp();
    /*************************************************************************************************************
    Name:        requestQProgram
    Description: request quantum program
    Argin:       sFilePath  quantum program file path
                 iRepeat    quantum program repeat
    Argout:      sTaskID    task id
    return:      true or false
    *************************************************************************************************************/
    virtual bool requestQProgram(std::string sFilePath,int iRepeat, std::string &sTaskID) { return true; };

    /*************************************************************************************************************
    Name:        requsetQProgramResult
    Description: request quantum program result
    Argin:       sTaskID  task id
    Argout:      sQResult quantum result    
    return:      true or false
    *************************************************************************************************************/
    virtual bool requsetQProgramResult(const std::string &sTaskID, std::string &sQResult) {return true;};

    /*************************************************************************************************************
    Name:        stopQProgram
    Description: stop quantum program 
    Argin:       sTaskID  task id
    Argout:      None  
    return:      true or false
    *************************************************************************************************************/
    virtual bool stopQProgram(std::string sTaskID) {return true;};

    /*************************************************************************************************************
    Name:        getAPIKey
    Description: get api key
    Argin:       None
    Argout:      None  
    return:      true or false
    *************************************************************************************************************/
    virtual bool getAPIKey() {return true;};


};

/*****************************************************************************************************************
Name:        createQCHttp
Description: create quantum http class
Argin:       sKeyFilePath   key file path
Argout:      None  
return:      true or false
*****************************************************************************************************************/
DLL_EXPORTS_API VirtualQCHttp * createQCHttp(std::string  &sKeyFilePath);

/*****************************************************************************************************************
Name:        destroyQCHttp
Description: destroy quantum http class
Argin:       pVQCHttp   virtual quantum http class pointer
Argout:      None  
return:      true or false
*****************************************************************************************************************/
DLL_EXPORTS_API bool destroyQCHttp(VirtualQCHttp * pVQCHttp);

