/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-21
Description:quantum instruction handle API
*****************************************************************************************************************/
#pragma once

#include "QuantumInstructionGet.h"
#include "../include/LinkedListController.h"
#define API _declspec(dllexport)

/*****************************************************************************************************************
Name:        init
Description: initialize the quantum gates
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
extern "C"_declspec(dllexport) bool init();

/*****************************************************************************************************************
Name:        destroy
Description: destroy the quantum gates
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
extern "C"_declspec(dllexport) bool destroy();

/*****************************************************************************************************************
Name:        transmit
Description: transmit the quantum instruction
Argin:       qInstructionList  quantum instruction list  
             stQbit            qBit
Argout:      None
return:      true or false
*****************************************************************************************************************/
extern "C"_declspec(dllexport) bool transmit(QList & qInstructionList,int stQbit);

/*****************************************************************************************************************
Name:        getProgramResult
Description: get quantum program result
Argin:       sResult    quantum program result
Argout:      sResult    quantum program result
return:      true or false
*****************************************************************************************************************/
extern "C"_declspec(dllexport) bool getProgramResult(string & sResult);