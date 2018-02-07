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
Date:2017-11-23
Description:instruction class
*****************************************************************************************************************/
#include "Instruction.h"
#include <string>

using namespace std;

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool Hadamard::getInstruction(QNode            *pQInstructionNode,
                              QuantumGateParam *pQuantumProParam,
                              QuantumGates     *pQGate)
{
    if ((nullptr == pQInstructionNode)||
        (nullptr == pQGate)||
        (nullptr == pQuantumProParam))
    {
        return false;
    }

    QError qResult;

    SingleGateNode * pSingleGateNode = (SingleGateNode *)pQInstructionNode;


    /*
     *  Hadamard gate
     */
    if (pSingleGateNode->controlList.size()!= 0)
    {
        pSingleGateNode->controlList.push_back(pSingleGateNode->opQubit);
        qResult = pQGate->Hadamard(pSingleGateNode->opQubit,
                                   0,
                                   pSingleGateNode->controlList, 
                                   pQuantumProParam->mQuantumBitNumber);
        pSingleGateNode->controlList.pop_back();
    }
    else
    {
        qResult = pQGate->Hadamard(pSingleGateNode->opQubit,
                                   0);
    }

    if (qErrorNone != qResult)
    {
        return false;
    }

    return true;
    
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool reset::getInstruction(QNode            *pQInstructionNode,
                           QuantumGateParam *pQuantumProParam,
                           QuantumGates     *pQGate)
{
    if ((nullptr == pQInstructionNode) ||
        (nullptr == pQGate) ||
        (nullptr == pQuantumProParam))
    {
        return false;
    }

    SingleGateNode * pSingleGateNode = (SingleGateNode *)pQInstructionNode;


    QError qResult;

    /*
     *  reset gate
     */
    qResult = pQGate->Reset(pSingleGateNode->opQubit);

    if (qErrorNone != qResult)
    {
        return false;
    }

    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool RX::getInstruction(QNode            *pQInstructionNode,
                        QuantumGateParam *pQuantumProParam,
                        QuantumGates     *pQGate)
{
    if ((nullptr == pQInstructionNode) || 
        (nullptr == pQGate) || 
        (nullptr == pQuantumProParam))
    {
        return false;
    }
    QError qResult;

    SingleAngleGateNode * pSingleAngleGateNode = (SingleAngleGateNode *)pQInstructionNode;

    /*
     *  rx gate
     */
    if (pSingleAngleGateNode->controlList.size()!= 0)                   /* gate have control bit                */
    {
        pSingleAngleGateNode->controlList.push_back(pSingleAngleGateNode->opQubit);
        /*
         *  is Dagger ?
         */
        if (pSingleAngleGateNode->isDagger)
        {
            qResult =  pQGate->RX(pSingleAngleGateNode->opQubit,
                                  pSingleAngleGateNode->angle,
                                  0,
                                  pSingleAngleGateNode->controlList,
                                  pQuantumProParam->mQuantumBitNumber,
                                  pSingleAngleGateNode->isDagger);
        }
        else
        {
            qResult = pQGate->RX(pSingleAngleGateNode->opQubit ,
                                 pSingleAngleGateNode->angle, 
                                 0,
                                 pSingleAngleGateNode->controlList,
                                 pQuantumProParam->mQuantumBitNumber);

        }
        pSingleAngleGateNode->controlList.pop_back();
    }
    else                                                                /* gate without control bit             */
    {
        /*
         *  is Dagger ?
         */
        if (pSingleAngleGateNode->isDagger)
        {
            qResult = pQGate->RX(pSingleAngleGateNode->opQubit,
                                 pSingleAngleGateNode->angle,
                                 0,
                                 pSingleAngleGateNode->isDagger);

        }
        else
        {
            qResult = pQGate->RX(pSingleAngleGateNode->opQubit,
                                 pSingleAngleGateNode->angle,
                                 0);
        }
    }

    if (qErrorNone != qResult)
    {
        return false;

    }
    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool RY::getInstruction(QNode            *pQInstructionNode,
                        QuantumGateParam *pQuantumProParam,
                        QuantumGates     *pQGate)
{
    if ((nullptr == pQInstructionNode) ||
        (nullptr == pQGate) || 
        (nullptr == pQuantumProParam))
    {
        return false;
    }


    QError qResult;

    SingleAngleGateNode * pSingleAngleGateNode = (SingleAngleGateNode *)pQInstructionNode;

    /*
     * ry gate
     */
    if (pSingleAngleGateNode->controlList.size()!= 0)                   /* gate have control bit                */
    {
        pSingleAngleGateNode->controlList.push_back(pSingleAngleGateNode->opQubit);
        qResult = pQGate->RY(pSingleAngleGateNode->opQubit,
                             pSingleAngleGateNode->angle,
                             0,
                             pSingleAngleGateNode->controlList, 
                             pQuantumProParam->mQuantumBitNumber,
                             pSingleAngleGateNode->isDagger);
        pSingleAngleGateNode->controlList.pop_back();
    }
    else                                                                /* gate without control bit             */
    {
        qResult = pQGate->RY(pSingleAngleGateNode->opQubit,
                             pSingleAngleGateNode->angle,
                             0,
                             pSingleAngleGateNode->isDagger);
    }

    if (qErrorNone != qResult)
    {
        return false;
    }

    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool RZ::getInstruction(QNode * pQInstructionNode,QuantumGateParam *pQuantumProParam,QuantumGates * pQGate)
{
    if ((nullptr == pQInstructionNode) || 
        (nullptr == pQGate) ||  
        (nullptr == pQuantumProParam))
    {
        return false;
    }


    QError qResult;

    SingleAngleGateNode * pSingleAngleGateNode = (SingleAngleGateNode *)pQInstructionNode;

    /*
     * rz gate
     */
    if (0==pSingleAngleGateNode->controlList.size())                    /* gate without control bit             */
    {
        qResult = pQGate->RZ(pSingleAngleGateNode->opQubit,
                             pSingleAngleGateNode->angle,
                             0,
                             pSingleAngleGateNode->isDagger);
    }
    else                                                                /* gate have control bit                */
    {
        pSingleAngleGateNode->controlList.push_back(pSingleAngleGateNode->opQubit);
        qResult = pQGate->RZ(pSingleAngleGateNode->opQubit,
                             pSingleAngleGateNode->angle,
                             0,
                             pSingleAngleGateNode->controlList,
                             pQuantumProParam->mQuantumBitNumber,
                             pSingleAngleGateNode->isDagger);       
        pSingleAngleGateNode->controlList.pop_back();
    }

    if (qErrorNone != qResult)
    {
        return false;
    }

    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool CNOT::getInstruction(QNode * pQInstructionNode,QuantumGateParam *pQuantumProParam,QuantumGates * pQGate)
{
    if ((nullptr == pQInstructionNode) || 
        (nullptr == pQGate) || 
        (nullptr == pQuantumProParam))
    {
        return false;
    }

    QError qResult;

    DoubleGateNode * pDoubleGate = (DoubleGateNode *)pQInstructionNode;
    
    /*
     *  CNOT gate
     */
    qResult = pQGate->CNOT(pDoubleGate->opQubit1,
                           pDoubleGate->opQubit2, 
                           0);
    if (qErrorNone != qResult)
    {
        return false;
    }

    return true;
}


/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool NOT::getInstruction(QNode * pQInstructionNode,QuantumGateParam *pQuantumProParam,QuantumGates * pQGate)
{
    if ((nullptr == pQInstructionNode) ||
        (nullptr == pQGate) || 
        (nullptr == pQuantumProParam))
    {
        return false;
    }

    SingleGateNode * pSingleGate = (SingleGateNode *)pQInstructionNode;

    QError qResult;
    
    /*
     *  NOT gate
     */
    if (pSingleGate->controlList.size()==0)                             /* gate without control bit             */
    {

        qResult = pQGate->NOT(pSingleGate->opQubit,
                              0);
    }
    else                                                                /* gate have control bit                */
    {
        pSingleGate->controlList.push_back(pSingleGate->opQubit);
        qResult = pQGate->NOT(pSingleGate->opQubit,
                              0,
                              pSingleGate->controlList,
                              pQuantumProParam->mQuantumBitNumber);
        pSingleGate->controlList.pop_back();
    }

    if(qErrorNone !=  qResult)
    {
        return false;
    }

    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool TOFFOLI::getInstruction(QNode * pQInstructionNode,QuantumGateParam *pQuantumProParam,QuantumGates * pQGate)
{
    if ((nullptr == pQInstructionNode) || 
        (nullptr == pQGate) || 
        (nullptr == pQuantumProParam))
    {
        return false;
    }

    QError qResult;

    TripleGateNode * pTripleGate = (TripleGateNode *)pQInstructionNode;

    /*
     * toffoli gate
     */
    qResult = pQGate->toffoli(pTripleGate->opQubit1,
                              pTripleGate->opQubit2,
                              pTripleGate->opQubit3,
                              0,
                              pQuantumProParam->mQuantumBitNumber);

    if (qErrorNone != qResult)
    {
        return false;
    }

    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool CR::getInstruction(QNode * pQInstructionNode,QuantumGateParam *pQuantumProParam,QuantumGates * pQGate)
{

    if ((nullptr == pQInstructionNode) || 
        (nullptr == pQGate) || 
        (nullptr == pQuantumProParam))
    {
        return false;
    }
    QError qResult;

    DoubleAngleGateNode * pDoubleAngle = (DoubleAngleGateNode *)pQInstructionNode;

    /*
     *   CR gate
     */
    qResult = pQGate->CR(pDoubleAngle->opQubit1,
                         pDoubleAngle->opQubit2, 
                         pDoubleAngle->angle,
                         0, 
                         pDoubleAngle->isDagger);

    if (qErrorNone != qResult)
    {
        return true;
    }

    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool iSWAP::getInstruction(QNode * pQInstructionNode,QuantumGateParam *pQuantumProParam,QuantumGates * pQGate)
{
    if ((nullptr == pQInstructionNode) || 
        (nullptr == pQGate) || 
        (nullptr == pQuantumProParam))
    {
        return false;
    }

    QError qResult;

    DoubleAngleGateNode * pDoubleAngle = (DoubleAngleGateNode *)pQInstructionNode;

    /*
     *   iSWAP gate
     */
    if (pDoubleAngle->controlList.size()!= 0)                           /* gate without control bit             */
    {
        pDoubleAngle->controlList.push_back(pDoubleAngle->opQubit1);
        pDoubleAngle->controlList.push_back(pDoubleAngle->opQubit2);
        qResult =  pQGate->iSWAP(pDoubleAngle->opQubit1,
                                 pDoubleAngle->opQubit2,
                                 0,
                                 pDoubleAngle->isDagger);
        pDoubleAngle->controlList.pop_back();
        pDoubleAngle->controlList.pop_back();
    }
    else                                                                /* gate have control bit                */
    {
        qResult = pQGate->iSWAP(pDoubleAngle->opQubit1,
                                pDoubleAngle->opQubit2,
                                0,
                                pDoubleAngle->controlList, 
                                pQuantumProParam->mQuantumBitNumber, 
                                pDoubleAngle->isDagger);
    }

    if (qErrorNone != qResult)
    {
        return false;
    }

    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool sqiSWAP::getInstruction(QNode            *pQInstructionNode,
                             QuantumGateParam *pQuantumProParam,
                             QuantumGates     *pQGate)
{
    if ((nullptr == pQInstructionNode) || 
        (nullptr == pQGate) || 
        (nullptr == pQuantumProParam))
    {
        return false;
    }

    QError qResult;
    
    DoubleGateNode * pDoubleGate = (DoubleGateNode *)pQInstructionNode;


    /*
     *  sqiSWAP gate
     */
    if (pDoubleGate->controlList.size()== 0)                            /* gate without control bit             */
    {

        qResult = pQGate->sqiSWAP(pDoubleGate->opQubit1,
                                  pDoubleGate->opQubit2,
                                  0,
                                  pDoubleGate->isDagger);
    }
    else                                                                /* gate have control bit                */
    {
        pDoubleGate->controlList.push_back(pDoubleGate->opQubit1);
        pDoubleGate->controlList.push_back(pDoubleGate->opQubit2);
        qResult = pQGate->sqiSWAP(pDoubleGate->opQubit1,
                                  pDoubleGate->opQubit2,
                                  0,
                                  pDoubleGate->controlList,
                                  pQuantumProParam->mQuantumBitNumber,
                                  pDoubleGate->isDagger);
        pDoubleGate->controlList.pop_back();
        pDoubleGate->controlList.pop_back();
    }

    if (qErrorNone != qResult)
    {
        return false;
    }

    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool controlSwap::getInstruction(QNode            *pQInstructionNode,
                                 QuantumGateParam *pQuantumProParam,
                                 QuantumGates     *pQGate)
{
    /*
    if (NULL == pQInstructionNode)
    {
        return false;
    }
    string sTemp, sQubitNumber1, sQubitNumber2, scontrolQubitNumber;
    controlSwapParameter controlSwapParam;
    controlSwapParam.stNumber = stNumber;
    controlSwapParam.iGatesType = controlSwapType;
    controlSwapParam.dErrorRate = 0;

    ssParam >> sTemp >> scontrolQubitNumber >> sQubitNumber1 >> sQubitNumber2;
    controlSwapParam.stcontrolQubitNumber = stoi(scontrolQubitNumber);
    controlSwapParam.stQubitNumber1       = stoi(sQubitNumber1);
    controlSwapParam.stQubitNumber2       = stoi(sQubitNumber2);
    return setQuantumInstruction((char *)&controlSwapParam, sizeof(controlSwapParam));
    */
    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool qubitMeasure::getInstruction(QNode            *pQInstructionNode,
                                  QuantumGateParam *pQuantumProParam,
                                  QuantumGates     *pQGate)
{
    if ((nullptr == pQInstructionNode) || 
        (nullptr == pQGate) || 
        (nullptr == pQuantumProParam))
    {
        return false;
    }
    int Result;

    MeasureNode *pMeasure = (MeasureNode *)pQInstructionNode;

    /*
     *  measure qubit and the state collapsed
     */
    Result = pQGate->qubitMeasure(pMeasure->opQubit);

    if (-1 == Result)
    {
        return false;
    }
    else
    {
        map<size_t, int>::iterator mitera;
        mitera = pQuantumProParam->mReturnValue.find(pMeasure->creg);
        if (mitera != pQuantumProParam->mReturnValue.end())
        {
            mitera->second = Result;
        }
        else
        {
            pQuantumProParam->mReturnValue.insert(pair<size_t,int>(pMeasure->creg, Result));
        }

        pQuantumProParam->mReturnValue.insert(pair<size_t,int>(pMeasure->creg, Result));
    }

    return true;;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool unitarySingleQubit::getInstruction(QNode            *pQInstructionNode,
                                        QuantumGateParam *pQuantumProParam,
                                        QuantumGates     *pQGate)
{
    /*
    if (NULL == pQInstructionNode)
    {
        return false;
    }
    string sTemp, sQubitNumber;
    unitarySingleQubitGateParameter unitarySingleQubitGateParam;
    unitarySingleQubitGateParam.stNumber = stNumber;
    unitarySingleQubitGateParam.iGatesType = unitarySingleQubitGateType;
    unitarySingleQubitGateParam.dErrorRate = 0;

    ssParam >> sTemp >> sQubitNumber;
    unitarySingleQubitGateParam.stQubitNumber = stoi(sQubitNumber);
    return setQuantumInstruction((char *)&unitarySingleQubitGateParam, sizeof(unitarySingleQubitGateParam));
    */
    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool endProgram::getInstruction(QNode            *pQInstructionNode,
                                QuantumGateParam *pQuantumProParam,
                                QuantumGates     *pQGate)
{
    if ((nullptr == pQInstructionNode) || 
        (nullptr == pQGate) || 
        (nullptr == pQuantumProParam))
    {
        return false;
    }

    if (qErrorNone != pQGate->endGate(pQuantumProParam, pQGate))
    {
        return false;
    }
    return true;
}

/*****************************************************************************************************************
Name:        getInstruction
Description: add instruction to Ring Memory
Argin:       pQInstructionNode  quantum Instruction node
             pQuantumProParam   quantum program param
             pQGate             quantum gate pointer
Argout:      pQuantumProParam   quantum program param
return:      true or false
*****************************************************************************************************************/
bool pMeasure::getInstruction(QNode            *pQInstructionNode,
                              QuantumGateParam *pQuantumProParam,
                              QuantumGates     *pQGate)
{
    if ((nullptr == pQInstructionNode) || 
        (nullptr == pQGate) || 
        (nullptr == pQuantumProParam))
    {
        return false;
    }

    pMeasureNode *pMeasure = (pMeasureNode *)pQInstructionNode;

    pQuantumProParam->mPMeasureSize=pMeasure->vecint_pmeasure_list.size();
    QError qResult;

    /*
     * pMeasure gate
     */
    qResult = pQGate->pMeasure(pMeasure->vecint_pmeasure_list, pQuantumProParam->mPMeasure);
    
    if (qErrorNone != qResult)
    {
        return false;
    }

    return true;;
}

