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
Date:2017-11-20
Description:get quantum instruction
*****************************************************************************************************************/
#include "QuantumInstructionGet.h"
#include <fstream>
#include <sstream>
#include "../QRunesParser/LinkedListController.h"
using namespace std;

/*****************************************************************************************************************
Name:        QuantumInstructionGet
Description: structure QuantumInstructionGet
Argin:       None
Argout:      None
return:      None
*****************************************************************************************************************/
QuantumInstructionGet::QuantumInstructionGet()
{
    /*
     * init quantum gate
     */
    Instruction *phadamard     = (Instruction *)new Hadamard;
    Instruction *pRX           = (Instruction *)new RX;
    Instruction *pRY           = (Instruction *)new RY;
    Instruction *pRZ           = (Instruction *)new RZ;
    Instruction *pCNOT         = (Instruction *)new CNOT;
    Instruction *pCR           = (Instruction *)new CR;
    Instruction *piSWAP        = (Instruction *)new iSWAP;
    Instruction *psqiSWAP      = (Instruction *)new sqiSWAP;
    Instruction *pcontrolSwap  = (Instruction *)new controlSwap;
    Instruction *pqubitMeasure = (Instruction *)new qubitMeasure;
    Instruction *pNOT          = (Instruction *)new NOT;
    Instruction *pTOFFOLI      = (Instruction *)new TOFFOLI;
    Instruction *pPMeasure     = (Instruction *)new pMeasure;
    Instruction *pReset        = (Instruction *)new reset;
    Instruction *pEndProgram   = (Instruction *)new endProgram;

    mInstructionMap.insert(pair<int, Instruction*>(phadamard->mType, phadamard));
    mInstructionMap.insert(pair<int, Instruction*>(pRX->mType, pRX));
    mInstructionMap.insert(pair<int, Instruction*>(pRY->mType, pRY));
    mInstructionMap.insert(pair<int, Instruction*>(pRZ->mType, pRZ));
    mInstructionMap.insert(pair<int, Instruction*>(pCNOT->mType, pCNOT));
    mInstructionMap.insert(pair<int, Instruction*>(pCR->mType, pCR));
    mInstructionMap.insert(pair<int, Instruction*>(piSWAP->mType, piSWAP));
    mInstructionMap.insert(pair<int, Instruction*>(psqiSWAP->mType, psqiSWAP));
    mInstructionMap.insert(pair<int, Instruction*>(pcontrolSwap->mType, pcontrolSwap));
    mInstructionMap.insert(pair<int, Instruction*>(pqubitMeasure->mType, pqubitMeasure));
    mInstructionMap.insert(pair<int, Instruction*>(pNOT->mType, pNOT));
    mInstructionMap.insert(pair<int, Instruction*>(pTOFFOLI->mType, pTOFFOLI));
    mInstructionMap.insert(pair<int, Instruction*>(pPMeasure->mType, pPMeasure));
    mInstructionMap.insert(pair<int, Instruction*>(pReset->mType, pReset));
    mInstructionMap.insert(pair<int, Instruction*>(pEndProgram->mType, pEndProgram));
}

/*****************************************************************************************************************
Name:        ~QuantumInstructionGet
Description: destruct QuantumInstructionGet
Argin:       None
Argout:      None
return:      None
*****************************************************************************************************************/
QuantumInstructionGet::~QuantumInstructionGet()
{
    for (auto aiter : mInstructionMap)
    {
        if (NULL != aiter.second)
        {
            delete(aiter.second);
        }
    }
}

/*****************************************************************************************************************
Name:        transmit
Description: transmit the quantum instruction
Argin:       pQInstructionNode  quantum instruction node
             pQuantumProParam   quantum program param pointer
             pQGate             quantum gates
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool QuantumInstructionGet::transmit(QNode            *pQInstructionNode,
                                     QuantumGateParam *pQuantumProParam, 
                                     QuantumGates     *pQGate)
{
    if (nullptr == pQInstructionNode)
    {
        return false;
    }

    
    auto aiter = mInstructionMap.find(pQInstructionNode->gateSpecifier);

    if (mInstructionMap.end() != aiter)
    {
        return aiter->second->getInstruction(pQInstructionNode,
                                             pQuantumProParam,
                                             pQGate);
    }

    return false;
}

