/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-21
Description:quantum instruction handle API
*****************************************************************************************************************/
#ifndef _QUANTUM_INSTRUCTION_HANDLE_API_H
#define _QUANTUM_INSTRUCTION_HANDLE_API_H
#include "QuantumInstructionGet.h"

#include <vector>
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

class DLL_EXPORTS_API QuantumInstructionHandleAPI
{
public:

    /*************************************************************************************************************
    Name:        QuantumInstructionHandleAPI
    Description: initialize the quantum gates
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    QuantumInstructionHandleAPI();

    /*************************************************************************************************************
    Name:        ~QuantumInstructionHandleAPI
    Description: destroy the quantum gates
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    ~QuantumInstructionHandleAPI();

    /*************************************************************************************************************
    Name:        transmit
    Description: transmit the quantum instruction
    Argin:       qInstructionList  quantum instruction list
                 pQuantumProParam  quantum program param pointer
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool transmit(QList            &qInstructionList,
                  QuantumGateParam *pQuantumProParam);

    /*************************************************************************************************************
    Name:        initState
    Description: init state
    Argin:       pQuantumProParam quantum param
    Argout:      pQuantumProParam quantum param
    return:      true or false
    *************************************************************************************************************/
    bool initState(QuantumGateParam *pQuantumProParam);

    /*************************************************************************************************************
    Name:        destroyState
    Description: destroyState state
    Argin:       pQuantumProParam quantum param
    Argout:      pQuantumProParam quantum param
    return:      true or false
    *************************************************************************************************************/
    bool destroyState(QuantumGateParam *pQuantumProParam);

    /*************************************************************************************************************
    Name:        setComputeUnit
    Description: set CalculationUnit
    Argin:       iCalculationUnitType  Calculation Unit Type
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool setComputeUnit(int iCalculationUnitType);

    /*************************************************************************************************************
    Name:        getState
    Description: get quantum state
    Argin:       sState              state string
                 pQuantumProParam    quantum program param pointer
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool getState(string & sState, QuantumGateParam *pQuantumProParam);
private:

    QuantumGates           *mpQGate = NULL;
};

#endif
