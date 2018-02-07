/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-23
Description:instruction class
*****************************************************************************************************************/
#pragma once
#include "../include/QuantumInstructionSimulateAPI.h"
#include "../include/QParamStruct.h"
#include "../include/LinkedListController.h"
#include <sstream>
using namespace std;

/*****************************************************************************************************************
  Instruction:the parent of instruction class
*****************************************************************************************************************/
class Instruction
{
public:
    Instruction(){};
    ~Instruction(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    virtual bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber) = 0;

public:
    int mType;                                                          /* instruction type                     */
};

/*****************************************************************************************************************
  Hadamard:Hadamard instruction
*****************************************************************************************************************/
class Hadamard:public Instruction
{
public:
    inline Hadamard()
    {
        mType = HADAMARD_GATE;                                          /* set instruction type                 */
    }
    ~Hadamard();

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);

};

/*****************************************************************************************************************
  RX:RX instruction
*****************************************************************************************************************/
class RX : public Instruction
{
public:
    inline RX()
    {
        mType = RX_GATE;                                                /* set instruction type                 */
    }
    ~RX();

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
  RY:RY instruction
*****************************************************************************************************************/
class RY : public Instruction
{
public:
    inline RY()
    {
        mType = RY_GATE;                                                /* set instruction type                 */
    }
    ~RY();

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
  RZ:RZ instruction
*****************************************************************************************************************/
class RZ : public Instruction
{
public:
    inline RZ()
    {
        mType = RZ_GATE;                                                /* set instruction type                 */
    }
    ~RZ(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
CNOT:CNOT instruction
*****************************************************************************************************************/
class CNOT : public Instruction
{
public:
    inline CNOT()
    {
        mType = CNOT_GATE;                                              /* set instruction type                 */
    }
    ~CNOT(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
NOT:NOT instruction
*****************************************************************************************************************/
class NOT : public Instruction
{
public:
    inline NOT()
    {
        mType = NOT_GATE;                                               /* set instruction type                 */
    }
    ~NOT(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
    stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
NOT:NOT instruction
*****************************************************************************************************************/
class TOFFOLI : public Instruction
{
public:
    inline TOFFOLI()
    {
        mType = TOFFOLI_GATE;                                           /* set instruction type                 */
    }
    ~TOFFOLI(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
    stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
  CR:CR instruction
*****************************************************************************************************************/
class CR : public Instruction
{
public:
    inline CR()
    {
        mType = 0;                                                      /* set instruction type                 */
    }
    ~CR(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
  iSWAP:iSWAP instruction
*****************************************************************************************************************/
class iSWAP : public Instruction
{
public:
    inline iSWAP()
    {
        mType = ISWAP_GATE;                                             /* set instruction type                 */
    }
    ~iSWAP(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
iSWAP:iSWAP instruction
*****************************************************************************************************************/
class sqiSWAP : public Instruction
{
public:
    inline sqiSWAP()
    {
        mType = SQISWAP_GATE;                                           /* set instruction type                 */
    }
    ~sqiSWAP(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
controlSwap:controlSwap instruction
*****************************************************************************************************************/
class controlSwap : public Instruction
{
public:
    inline controlSwap()
    {
        mType = -1;
    }
    ~controlSwap(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
qubitMeasure:qubitMeasure instruction
*****************************************************************************************************************/
class qubitMeasure : public Instruction
{
public:
    qubitMeasure()
    {
        mType = MEASURE_GATE;                                           /* set instruction type                 */
    };
    ~qubitMeasure(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
unitarySingleQubit:unitarySingleQubit instruction
*****************************************************************************************************************/
class unitarySingleQubit : public Instruction
{
public:
    unitarySingleQubit(){};
    ~unitarySingleQubit(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};

/*****************************************************************************************************************
endProgram:endProgram instruction
*****************************************************************************************************************/
class endProgram : public Instruction
{
public:

    endProgram()
    {
        mType = END;                                                    /* set instruction type                 */
    }
    ~endProgram(){};

    /*************************************************************************************************************
    Name:        addInstructionToRingMemory
    Description: add instruction to Ring Memory
    Argin:       pQInstructionNode  quantum Instruction node
                 stNumber           Instruction number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool addInstructionToRingMemory(QNode * pQInstructionNode, size_t stNumber);
};