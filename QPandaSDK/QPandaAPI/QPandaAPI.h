/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2018-01-19
Description: QParserSDK
*****************************************************************************************************************/
#ifndef  _QPARSER_SDK_API_H
#define  _QPARSER_SDK_API_H
#include <iostream>
#include "../QRunesParser/QRunesParserAPI.h"
#include "../QuantumInstructionHandle/QuantumGateParameter.h"
#include "../QuantumInstructionHandle/QuantumInstructionHandleAPI.h"
#include "../QuantumInstructionHandle/QError.h"
#include <memory>
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
namespace QPanda 
{
#define STRING     std::string
#define CPU        1
#define GPU        2
#define MEASURE    1
#define PMEASURE   2
#define PAIR       pair<string,double>

class  QPandaSDK 
{
public:
    STRING                        msFileName;                           /* file name                            */
    DLL_EXPORTS_API QPandaSDK();
    DLL_EXPORTS_API ~QPandaSDK();


    static  QPandaSDK * getIntance()
    {
        static QPandaSDK * temp = new QPandaSDK();
        return temp;
    }

    /*************************************************************************************************************
    Name:        getResult
    Description: get quantum program result
    Argin:       None
    return:      qerror
    *************************************************************************************************************/
    STRING DLL_EXPORTS_API getResult();

    /*************************************************************************************************************
    Name:        getQuantumState
    Description: get quantum program qstate
    Argin:       None
    return:      qerror
    *************************************************************************************************************/
    STRING DLL_EXPORTS_API  getQuantumState();


    /*************************************************************************************************************
    Name:        loadFile
    Description: load quantum program
    Argin:       sFilePath  quantum program file path
    Argout:      Qnum       quantum bit num
    return:      qerror
    *************************************************************************************************************/
    int DLL_EXPORTS_API  loadFile(const string &sFilePath);

    /*************************************************************************************************************
    Name:        setComputeUnit
    Description: set compute unit,you have two options:CPU or GPU.you can not choose again when you have 
                 already selected a compute unit
    Argin:       iComputeUnit  the type of compute unit
    Argout:      None
    return:      qerror
    *************************************************************************************************************/
    int DLL_EXPORTS_API setComputeUnit(int iComputeUnit);

    /*************************************************************************************************************
    Name:        run
    Description: run quantum program
    Argin:       iRepeat    quantum program repeat
    Argout:      None
    return:      qerror
    *************************************************************************************************************/
    int DLL_EXPORTS_API run(int iRepeat);



 private:
    map<string,double>            mQResultMap;                          /* quantum program result map           */
    QList                         mQList;
    bool                          mbIsRead = false;                     /* is read quantum program file         */
    QuantumGateParam *             mQGatesParam;
    QuantumInstructionHandleAPI   mQHandle;
    int                           miComputeType;                        /* quantum program file is read         */
    int                           miMeasureType;                        /* quantum program measure type         */
    bool                          mbIsRun = false;                      /* quantum program is run               */
    /*************************************************************************************************************
    Name:        statisticalResults
    Description: statistical results
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    void countState();

    /*************************************************************************************************************
    Name:        integerToBinary
    Description: integer to binary
    Argin:       number     src number
                 iRetLen    ssRet len
    Argout:      ssRet      binary result
    return:      true or false
    *************************************************************************************************************/
    bool integerToBinary(size_t number,stringstream &ssRet, size_t iRetLen);



};
}

using namespace QPanda;
/*************************************************************************************************************
Name:        loadFile
Description: load quantum program
Argin:       sFilePath  quantum program file path
Argout:      Qnum       quantum bit num
return:      qerror
*************************************************************************************************************/
int  loadFileAPI(char * pcFilePath);

/*************************************************************************************************************
Name:        setComputeUnit
Description: set compute unit,you have two options:CPU or GPU.you can not choose again when you have
already selected a compute unit
Argin:       iComputeUnit  the type of compute unit
Argout:      None
return:      qerror
*************************************************************************************************************/
int  setComputeUnitAPI(int iComputeUnit);

/*************************************************************************************************************
Name:        run
Description: run quantum program
Argin:       iRepeat    quantum program repeat
Argout:      None
return:      qerror
*************************************************************************************************************/
int  runAPI(int iRepeat);

int  getFileNameAPI(char * buf, int * pLength);

/*************************************************************************************************************
Name:        getResult
Description: get quantum program result
Argin:       None
return:      qerror
*************************************************************************************************************/
int  getResultAPI(char * buf, int * pLength);

/*************************************************************************************************************
Name:        getQuantumState
Description: get quantum program qstate
Argin:       None
return:      qerror
*************************************************************************************************************/
int  getQuantumStateAPI(char * buf, int * pLength);

#endif
