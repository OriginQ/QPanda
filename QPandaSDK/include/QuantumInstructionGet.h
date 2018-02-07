/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-20
Description:get quantum instruction
*****************************************************************************************************************/
#pragma once
#include "../include/QuantumGatesParameterStructure.h"
#include "../include/QuantumInstructionSimulateAPI.h"
#include "Instruction.h"

class QuantumInstructionGet
{
public:
    QuantumInstructionGet();
    ~QuantumInstructionGet();

    /*************************************************************************************************************
    Name:        transmit
    Description: transmit the quantum instruction
    Argin:       pQInstructionNode  quantum instruction node
                 iNumber  number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool transmit(QNode * pQInstructionNode,int iNumber);

    /*************************************************************************************************************
    Name:        getQuantumProgramResult
    Description: get quantum program result
    Argin:       sResult  quantum program result
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool getQuantumProgramResult(string & sResult);
private:
    vector<Instruction *> mvInstruction;
    

};

