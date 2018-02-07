/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-10
Description:quantum instruction simulate API
*****************************************************************************************************************/
#pragma once
#include "QuantumGatesParameterStructure.h"
#include "QuantumGatesAPI.h"

#define API _declspec(dllexport)
/*****************************************************************************************************************
Name:        initQuantumInstruction
Description: initialize the quantum gates
Argin:       None
Argout:      None
return:      quantum error
*****************************************************************************************************************/
API QError initQuantumInstruction();

/*****************************************************************************************************************
Name:        selectCalculationUnit
Description: select calculation unit type
Argin:       cCalculationUnitType    calculation unit type
Argout:      None
return:      quantum error
*****************************************************************************************************************/
API QError selectCalculationUnit(string & sCalculationUnitType);

/*****************************************************************************************************************
Name:        initState
Description: initialize the quantum state
Argin:       stNumber  Quantum number
Argout:      Nome
return:      quantum error
*****************************************************************************************************************/
API QError initState(size_t stNumber);

/*****************************************************************************************************************
Name:        destroyQuantumInstruction
Description: destroy the quantum gates
Argin:       None
Argout:      None
return:      quantum error
*****************************************************************************************************************/
API QError destroyQuantumInstruction();

/*****************************************************************************************************************
Name:        setQuantumInstruction
Description: set the quantum Instruction
Argin:       pcQInstruction quantum Instruction pointer 
             stSize         quantum Instruction size
Argout:      None
return:      ture or false
*****************************************************************************************************************/
API bool setQuantumInstruction(char *pcQInstruction, size_t stSize,vector<size_t> &vControl);

/*****************************************************************************************************************
Name:        getResult
Description: set the quantum Instruction
Argin:       sResult    measure result
             qsResult   qList result
Argout:      sResult
return:      true or false
*****************************************************************************************************************/
API bool getResult(string & sResult,QState & qsResult);