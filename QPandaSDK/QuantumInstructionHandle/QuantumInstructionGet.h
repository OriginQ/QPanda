/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-20
Description:get quantum instruction
*****************************************************************************************************************/
#ifndef _QUANTUM_INSTRUCTION_GET_H
#define _QUANTUM_INSTRUCTION_GET_H
#include <map>
#include <thread>
#include "Instruction.h"

/*****************************************************************************************************************
QuantumInstructionGet:get quantum instruction
*****************************************************************************************************************/
class QuantumInstructionGet
{
public:


     ~QuantumInstructionGet();

     /*****************************************************************************************************************
     Name:        getInstance
     Description: get instance
     Argin:       None
     Argout:      None
     return:      QuantumInstructionHandleAPI pointer
     *****************************************************************************************************************/
     inline static QuantumInstructionGet * getInstance()
     {
         static QuantumInstructionGet pInstance;//= new QuantumInstructionGet;
         return &pInstance;
     }

    /*************************************************************************************************************
    Name:        transmit
    Description: transmit the quantum instruction
    Argin:       pQInstructionNode  quantum instruction node
                 pQuantumProParam   quantum program param pointer
                 pQGate             quantum gates
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool transmit(QNode * pQInstructionNode, QuantumGateParam *pQuantumProParam, QuantumGates * pQGate);

private:
    std::map<int,Instruction *> mInstructionMap;                        /* Instruction map                      */

    /*************************************************************************************************************
    Name:        QuantumInstructionGet
    Description: structure QuantumInstructionGet
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    QuantumInstructionGet();
};

#endif
