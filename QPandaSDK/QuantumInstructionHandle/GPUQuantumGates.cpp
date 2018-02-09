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
Date:2017-11-10
Description:gpu quantum logic gates class
*****************************************************************************************************************/
#include "GPUQuantumGates.h"
#include <algorithm>
#include <thread>
#include <map>
#include <iostream>


using std::map;
using std::pair;

GPUQuantumGates::GPUQuantumGates()
{
    #ifdef _WIN32
        mGPUDll = dllLoad("GPUEmulator.dll");
    #elif __linux__
        mGPUDll = dllLoad("GPUEmulator.so");
    #endif

    if (NULL == mGPUDll)
    {
        throw runtime_error("open QuantumGPU dll fail ");
    }
}

GPUQuantumGates::~GPUQuantumGates()
{
    dllFree(mGPUDll);
}

/*****************************************************************************************************************
Name:        getQState
Description: get quantum state
Argin:       pQuantumProParam       quantum program prarm pointer
Argout:      sState                 string state
return:      quantum error
*****************************************************************************************************************/
bool GPUQuantumGates::getQState(string & sState, QuantumGateParam *pQuantumProParam)
{
    GATEGPU::pGetState pGState = (GATEGPU::pGetState)dllFun(mGPUDll,"getState");
    pGState(mvCPUQuantumStat, mvQuantumStat, pQuantumProParam->mQuantumBitNumber);
    size_t uiDim = 1u << (pQuantumProParam->mQuantumBitNumber);
    stringstream ssTemp;
    for (size_t i = 0; i < uiDim; i++)
    {
        ssTemp << "state[" << i << "].real = " 
               << mvCPUQuantumStat.real[i] 
               << " " << "state[" << i << "].imag = " 
               << mvCPUQuantumStat.imag[i] << "\n";
    }
    sState.append(ssTemp.str());
    return true;
}

/*****************************************************************************************************************
Name:        endGate
Description: end gate
Argin:       pQuantumProParam       quantum program param pointer
             pQGate                 quantum gate
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::endGate(QuantumGateParam *pQuantumProParam, QuantumGates * pQGate)
{
    GATEGPU::pClearState pCState = (GATEGPU::pClearState)dllFun(mGPUDll,"clearState");

    if (nullptr == pCState)
    {
        return undefineError;
    }

    if (!pCState(mvCPUQuantumStat, mvQuantumStat, pQuantumProParam->mQuantumBitNumber))
    {
        return undefineError;
    }

    return qErrorNone;
}



/*****************************************************************************************************************
Name:        Hadamard
Description: Hadamard gate,the matrix is:[1/sqrt(2),1/sqrt(2);1/sqrt(2),-1/sqrt(2)]
Argin:       qn          qubit number that the Hadamard gate operates on.
error_rate   the errorrate of the gate
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::Hadamard(size_t qn, double error_rate)
{
    GATEGPU::pHadamard ph = (GATEGPU::pHadamard)dllFun(mGPUDll, "Hadamard");

    if (nullptr == ph)
    {
        return undefineError;
    }

    if (!ph(mvQuantumStat, qn, error_rate))
    {
        return undefineError;
    }
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        Reset
Description: reset bit gate
Argin:       qn          qubit number that the Hadamard gate operates on.
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::Reset(size_t qn)
{
    GATEGPU::pQbReset pQReset = (GATEGPU::pQbReset)dllFun(mGPUDll, "qbReset");

    if (nullptr == pQReset)
    {
        return undefineError;
    }
    
    if (!pQReset(mvQuantumStat, qn, 0))
    {
        return undefineError;
    }
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        pMeasure
Description: pMeasure gate
Argin:       qnum        qubit bit number vector
mResult     reuslt vector
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::pMeasure(Qnum& qnum, vector<pair<size_t, double>> &mResult)
{
    GATEGPU::pPMeasurenew pPmeasure = (GATEGPU::pPMeasurenew)dllFun(mGPUDll, "pMeasurenew");

    if (nullptr == pPmeasure)
    {
        return undefineError;
    }

    if (!pPmeasure(mvQuantumStat, mResult, qnum))
    {
        return undefineError;
    }
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        Hadamard
Description: controled-Hadamard gate
Argin:       qn                 qubit number that the Hadamard gate operates on.
             error_rate         the errorrate of the gate
             vControlBit        control bit vector
             stQuantumBitNumber quantum bit number
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::Hadamard(size_t  qn,
                                 double  error_rate,
                                 Qnum    vControlBit,
                                 size_t  stQuantumBitNumber)
{
    GATEGPU::pControlHadamard pCH= (GATEGPU::pControlHadamard)dllFun(mGPUDll, "controlHadamard");

    if (nullptr == pCH)
    {
        return undefineError;
    }

    if (!pCH(mvQuantumStat, vControlBit, error_rate))
    {
        return undefineError;
    }

    return qErrorNone;
}

/*****************************************************************************************************************
Name:        RX
Description: RX gate,quantum state rotates ¦È by x axis.The matric is:
             [cos(¦È/2),-i*sin(¦È/2);i*sin(¦È/2),cos(¦È/2)]
Argin:       qn          qubit number that the Hadamard gate operates on.
             theta       rotation angle
             error_rate  the errorrate of the gate
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::RX(size_t qn, double theta, double error_rate)
{
    GATEGPU::pRX pRX = (GATEGPU::pRX)dllFun(mGPUDll, "RX");

    if (nullptr == pRX)
    {
        return undefineError;
    }

    if (!pRX(mvQuantumStat, qn, theta, error_rate))
    {
        return undefineError;
    }

    
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        RX
Description: RX dagger gate,quantum state rotates ¦È by x axis.The matric is:
             [cos(¦È/2),-i*sin(¦È/2);i*sin(¦È/2),cos(¦È/2)]
Argin:       qn          qubit number that the Hadamard gate operates on.
             theta       rotation angle
             error_rate  the errorrate of the gate
             iDagger     is dagger
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::RX(size_t qn, double theta, double error_rate, int iDagger)
{
    if (!iDagger)
    {
        return undefineError;
    }

    GATEGPU::pRXdagger pRXDagger = (GATEGPU::pRXdagger)dllFun(mGPUDll, "RXdagger");

    if (nullptr == pRXDagger)
    {
        return undefineError;
    }

    if (!pRXDagger(mvQuantumStat, qn, theta, error_rate))
    {
        return undefineError;
    }
    
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        RX
Description: controled-RX gate
Argin:       qn                 qubit number that the Hadamard gate operates on.
             theta              rotation angle
             error_rate         the errorrate of the gate
             vControlBitNumber  control bit number
             stQuantumBitNumber quantum bit number
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::RX(size_t   qn,
                           double   theta,
                           double   error_rate,
                           Qnum     vControlBitNumber,
                           size_t   stQuantumBitNumber)
{
    GATEGPU::pControlRX pCRX = (GATEGPU::pControlRX)dllFun(mGPUDll, "controlRX");

    if (nullptr == pCRX)
    {
        return undefineError;
    }

    if (!pCRX(mvQuantumStat, vControlBitNumber, theta, error_rate))
    {
        return undefineError;
    }

    return qErrorNone;
}

/*****************************************************************************************************************
Name:        RX
Description: controled-RX dagger gate
Argin:       qn                 qubit number that the Hadamard gate operates on.
             theta              rotation angle
             error_rate         the errorrate of the gate
             vControlBitNumber  control bit number
             stQuantumBitNumber quantum bit number
             iDagger            is dagger
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::RX(size_t  qn,
                           double  theta,
                           double  error_rate,
                           Qnum    vControlBitNumber,
                           size_t  stQuantumBitNumber,
                           int     iDagger)
{
    if (!iDagger)
    {
        return undefineError;
    }

    GATEGPU::pControlRXdagger pCRXDagger = (GATEGPU::pControlRXdagger)dllFun(mGPUDll, "controlRXdagger");

    if (nullptr == pCRXDagger)
    {
        return undefineError;
    }

    if (!pCRXDagger(mvQuantumStat, vControlBitNumber, theta, error_rate))
    {
        return undefineError;
    }

    return qErrorNone;
}

/*****************************************************************************************************************
Name:        RY
Description: RY control gate
Argin:       qn                 qubit number that the Hadamard gate operates on.
             theta              rotation angle
             error_rate         the errorrate of the gate
             vControlBit        control bit vector
             stQuantumBitNumber quantum bit number
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::RY(size_t   qn,
                           double   theta,
                           double   error_rate,
                           Qnum     vControlBit,
                           size_t   stQuantumBitNumber,
                           int      iDagger)
{
    if (iDagger)
    {
        GATEGPU::pControlRYdagger pCRYDagger = (GATEGPU::pControlRYdagger)dllFun(mGPUDll, "controlRYdagger");

        if (nullptr == pCRYDagger)
        {
            return undefineError;
        }

        if (!pCRYDagger(mvQuantumStat, vControlBit, theta, error_rate))
        {
            return undefineError;
        }
    }
    else
    {
        GATEGPU::pControlRY pCRY = (GATEGPU::pControlRY)dllFun(mGPUDll, "controlRY");

        if (nullptr == pCRY)
        {
            return undefineError;
        }

        if (!pCRY(mvQuantumStat, vControlBit, theta, error_rate))
        {
            return undefineError;
        }
    }
    
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        RY

Description: RY gate,quantum state rotates ¦È by y axis.The matric is
             [cos(¦È/2),-sin(¦È/2);sin(¦È/2),cos(¦È/2)]
Argin:       qn          qubit number that the Hadamard gate operates on.
             theta        rotation angle
             error_rate   the errorrate of the gate
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::RY(size_t qn, double theta, double error_rate,int iDagger)
{
    if (iDagger)
    {
        GATEGPU::pRYdagger pRYdagger = (GATEGPU::pRYdagger)dllFun(mGPUDll, "RYdagger");

        if (nullptr == pRYdagger)
        {
            return undefineError;
        }

        if (!pRYdagger(mvQuantumStat, qn, theta, error_rate))
        {
            return undefineError;
        }
    }
    else
    {
        GATEGPU::pRY pRY = (GATEGPU::pRY)dllFun(mGPUDll, "RY");

        if (nullptr == pRY)
        {
            return undefineError;
        }

        if (!pRY(mvQuantumStat, qn, theta, error_rate))
        {
            return undefineError;
        }
    }
    
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        RZ
Description: RZ gate,quantum state rotates ¦È by z axis.The matric is
[1 0;0 exp(i*¦È)]
Argin:       qn          qubit number that the Hadamard gate operates on.
             theta       rotation angle
             error_rate  the errorrate of the gate
             iDagger     is dagger
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::RZ(size_t qn, double theta, double error_rate, int iDagger)
{
    if (!iDagger)
    {
        GATEGPU::pRZ pRZ = (GATEGPU::pRZ)dllFun(mGPUDll, "RZ");

        if (nullptr == pRZ)
        {
            return undefineError;
        }

        if (!pRZ(mvQuantumStat, qn, theta, error_rate))
        {
            return undefineError;
        }
    }
    else
    {
        GATEGPU::pRZdagger pRZDagger = (GATEGPU::pRZdagger)dllFun(mGPUDll, "RZdagger");

        if (nullptr == pRZDagger)
        {
            return undefineError;
        }

        if (!pRZDagger(mvQuantumStat, qn, theta, error_rate))
        {
            return undefineError;
        }
    }
    
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        RZ
Description: RZ gate
Argin:       qn                 qubit number that the Hadamard gate operates on.
             theta              rotation angle
             error_rate         the errorrate of the gate
             vControlBitNumber  control bit number
             stQuantumBitNumber quantum bit number
             iDagger            is dagger
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::RZ(size_t   qn,
                           double   theta,
                           double   error_rate,
                           Qnum     vControlBitNumber,
                           size_t   stQuantumBitNumber,
                           int      iDagger)
{
    if (!iDagger)
    {
        GATEGPU::pControlRZ pCRZ = (GATEGPU::pControlRZ)dllFun(mGPUDll, "controlRZ");

        if (nullptr == pCRZ)
        {
            return undefineError;
        }

        if (!pCRZ(mvQuantumStat, vControlBitNumber, theta, 0))
        {
            return undefineError;
        }
    }
    else
    {
        GATEGPU::pControlRZdagger pCRZDagger = (GATEGPU::pControlRZdagger)dllFun(mGPUDll, "controlRZdagger");

        if (nullptr == pCRZDagger)
        {
            return undefineError;
        }

        if (!pCRZDagger(mvQuantumStat, vControlBitNumber, theta, 0))
        {
            return undefineError;
        }
    }
    
    return qErrorNone;
}

/*****************************************************************************************************************
Name: CNOT
Description: CNOT gate,when control qubit is |0>,goal qubit does flip,
             when control qubit is |1>,goal qubit flips.the matric is:
             [1 0 0 0;0 1 0 0;0 0 0 1;0 0 1 0]
Argin:       qn_1        control qubit number
             qn_2        goal qubit number
             error_rate  the errorrate of the gate
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::CNOT(size_t qn_1, size_t qn_2, double error_rate)
{
    GATEGPU::pCNOT pCNOT = (GATEGPU::pCNOT)dllFun(mGPUDll, "CNOT");

    if (nullptr == pCNOT)
    {
        return undefineError;
    }

    if (!pCNOT(mvQuantumStat, qn_1, qn_2, error_rate))
    {
        return undefineError;
    }
    
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        CNOT
Description: CNOT control gate
Argin:       qn_1               control qubit number
             qn_2               goal qubit number
             error_rate         the errorrate of the gate
             vControlBitNumber  control bit number
             stQuantumBitNumber quantum bit number
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::CNOT(size_t  qn_1,
                             size_t  qn_2,
                             double  error_rate,
                             Qnum    vControlBitNumber,
                             int     stQuantumBitNumber)
{
    return qErrorNone;
}


/*****************************************************************************************************************
Name:        CR
Description: CR gate,when control qubit is |0>,goal qubit does not rotate,
             when control qubit is |1>,goal qubit rotate ¦È by z axis.the matric is:
             [1 0 0 0;0 1 0 0;0 0 1 0;0 0 0 exp(i*¦È)]
Argin:       qn_1        control qubit number
             qn_2        goal qubit number
             theta       roration angle
             error_rate  the errorrate of the gate
             iDagger     is dagger
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::CR(size_t  qn_1,
                           size_t  qn_2,
                           double  theta,
                           double  error_rate,
                           int     iDagger)
{
    if (!iDagger)
    {
        GATEGPU::pCR pCR = (GATEGPU::pCR)dllFun(mGPUDll, "CR");

        if (nullptr == pCR)
        {
            return undefineError;
        }

        if (!pCR(mvQuantumStat, qn_1, qn_2, theta, error_rate))
        {
            return undefineError;
        }
        
    }
    else
    {
        GATEGPU::pCRdagger pCRDagger = (GATEGPU::pCRdagger)dllFun(mGPUDll, "pCRdagger");

        if (nullptr == pCRDagger)
        {
            return undefineError;
        }

        if (!pCRDagger(mvQuantumStat, qn_1, qn_2, theta, error_rate))
        {
            return undefineError;
        }
    }

    return qErrorNone;
}

/*****************************************************************************************************************
Name:        iSWAP
Description: iSWAP gate,both qubits swap and rotate ¦Ð by z-axis,the matric is:
[1 0 0 0;0 0 -i 0;0 -i 0 0;0 0 0 1]
Argin:       qn_1        first qubit number
             qn_2        second qubit number
             error_rate  the errorrate of the gate
             iDagger     is dagger
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::iSWAP(size_t qn_1,
                              size_t qn_2,
                              double error_rate,
                              int    iDagger)
{
    if (!iDagger)
    {
        GATEGPU::piSWAP pISWAP = (GATEGPU::piSWAP)dllFun(mGPUDll, "iSWAP");

        if (nullptr == pISWAP)
        {
            return undefineError;
        }

        if (!pISWAP(mvQuantumStat, qn_1, qn_2, 0))
        {
            return undefineError;
        }
    }
    else
    {
        GATEGPU::pISWAPdagger pISWAPDagger = (GATEGPU::pISWAPdagger)dllFun(mGPUDll, "iSWAPdagger");

        if (nullptr == pISWAPDagger)
        {
            return undefineError;
        }

        if (!pISWAPDagger(mvQuantumStat, qn_1, qn_2, 0))
        {
            return undefineError;
        }
    }
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        iSWAP
Description: iSWAP gate,both qubits swap and rotate ¦Ð by z-axis,the matric is:
             [1 0 0 0;0 0 -i 0;0 -i 0 0;0 0 0 1]
Argin:       qn_1               first qubit number
             qn_2               second qubit number
             error_rate         the errorrate of the gate
             vControlBitNumber  control bit number
             stQuantumBitNumber quantum bit number
             iDagger            is dagger
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::iSWAP(size_t  qn_1,
                              size_t  qn_2,
                              double  error_rate,
                              Qnum    vControlBitNumber,
                              int     stQuantumBitNumber,
                              int     iDagger)
{
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        controlSwap
Description: iSWAP gate,both qubits swap and rotate ¦Ð by z-axis,the matric is:
[1 0 0 0;0 0 -i 0;0 -i 0 0;0 0 0 1]
Argin:       qn_1        first qubit number
             qn_2        second qubit number
             error_rate  the errorrate of the gate
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::controlSwap(size_t qn_1, size_t qn_2, size_t qn_3, double error_rate)
{

    return qErrorNone;
}

/*****************************************************************************************************************
Name:        sqiSWAP
Description: sqiSWAP gate,both qubits swap and rotate ¦Ð by z-axis,the matrix is:
             [1 0 0 0;0 1/sqrt(2) -i/sqrt(2) 0;0 -i/sqrt(2) 1/sqrt(2) 0;0 0 0 1]
Argin:       qn_1        first qubit number
             qn_2        second qubit number
             error_rate  the errorrate of the gate
             iDagger     is dagger
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::sqiSWAP(size_t  qn_1,
                                size_t  qn_2,
                                double  error_rate,
                                int     iDagger)
{
    if (!iDagger)
    {
        GATEGPU::pSqiSWAP pSqiSwap = (GATEGPU::pSqiSWAP)dllFun(mGPUDll, "sqiSWAP");

        if (nullptr == pSqiSwap)
        {
            return undefineError;
        }

        if (!pSqiSwap(mvQuantumStat, qn_1, qn_2,0))
        {
            return undefineError;
        }
        
    }
    else
    {
        GATEGPU::SqiSWAPdagger pSqiSwapDagger = (GATEGPU::SqiSWAPdagger)dllFun(mGPUDll, "sqiSWAPdagger");

        if (nullptr == pSqiSwapDagger)
        {
            return undefineError;
        }

        if (!pSqiSwapDagger(mvQuantumStat, qn_1, qn_2, 0))
        {
            return undefineError;
        }
    }
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        sqiSWAP
Description: sqiSWAP gate,both qubits swap and rotate ¦Ð by z-axis,the matrix is:
             [1 0 0 0;0 1/sqrt(2) -i/sqrt(2) 0;0 -i/sqrt(2) 1/sqrt(2) 0;0 0 0 1]
Argin:       qn_1               first qubit number
             qn_2               second qubit number
             error_rate         the errorrate of the gate
             vControlBitNumber  control bit number
             stQuantumBitNumber quantum bit number
             iDagger            is dagger
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::sqiSWAP(size_t  qn_1,
                                size_t  qn_2,
                                double  error_rate,
                                Qnum    vControlBitNumber,
                                int     stQuantumBitNumber,
                                int     iDagger)
{
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        qubitMeasure
Description: measure qubit and the state collapsed
Argin:       qn    qubit number of the measurement
Argout:      None
return:      quantum error
*****************************************************************************************************************/
int GPUQuantumGates::qubitMeasure(size_t qn)
{
    GATEGPU::pQubitmeasure pQmeasure = (GATEGPU::pQubitmeasure)dllFun(mGPUDll, "qubitmeasure");

    if (nullptr == pQmeasure)
    {
        return undefineError;
    }

    return pQmeasure(mvQuantumStat, 1<<qn);
}


/*****************************************************************************************************************
Name:        initState
Description: initialize the quantum state
Argin:       stNumber  Quantum number
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::initState(QuantumGateParam * pQuantumProParam)
{
    GATEGPU::pInitstate pInit = (GATEGPU::pInitstate)dllFun(mGPUDll, "initstate");

    if (nullptr == pInit)
    {
        return undefineError;
    }
    if (!pInit(mvCPUQuantumStat, mvQuantumStat, pQuantumProParam->mQuantumBitNumber))
    {
        return undefineError;
    }
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        destroyState
Description: destroy the quantum state
Argin:       stNumber  Quantum number
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::destroyState(size_t stNumber)
{
    GATEGPU::pDestroyState pDestroy = (GATEGPU::pDestroyState)dllFun(mGPUDll, "destroyState");

    if (nullptr == pDestroy)
    {
        return undefineError;
    }

    if (!pDestroy(mvCPUQuantumStat, mvQuantumStat, stNumber))
    {
        return undefineError;
    }
    return qErrorNone;
}


/*****************************************************************************************************************
Name:        unitarySingleQubitGate
Description: unitary single qubit gate
Argin:       qn          target qubit number
             matrix      matrix of the gate
             error_rate  the errorrate of the gate
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::unitarySingleQubitGate(size_t qn, void* matrix, double error_rate)
{
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        matReverse
Description: change the position of the qubits in 2-qubit gate
Argin:       (*mat)[4]       pointer of the origin 2D array
             (*mat_rev)[4]   pointer of the changed 2D array
Argout:      2D array
return:      quantum error
*****************************************************************************************************************/
QError  GPUQuantumGates::matReverse(COMPLEX(*mat)[4], COMPLEX(*mat_rev)[4])
{
    COMPLEX  temp;
    /*  mat_rev = { { mat[0][0],mat[0][2],mat[0][1],mat[0][3] },
    *            { mat[2][0],mat[2][2],mat[2][1],mat[2][3] },
    *            { mat[1][0],mat[1][2],mat[1][1],mat[1][3] },
    *            { mat[3][0],mat[3][2],mat[3][1],mat[3][3] }, };
    */
    for (size_t j = 0; j != 4; j++)                                     /* swap 2nd and 3rd row                 */
    {
        *(*mat_rev + j) = *(*mat + j);
        *(*(mat_rev + 1) + j) = *(*(mat + 2) + j);
        *(*(mat_rev + 2) + j) = *(*(mat + 1) + j);
        *(*(mat_rev + 3) + j) = *(*(mat + 3) + j);
    }

    for (size_t j = 0; j != 4; j++)                                     /* swap 2nd and 3rd column              */
    {
        temp = *(*(mat_rev + j) + 1);
        *(*(mat_rev + j) + 1) = *(*(mat_rev + j) + 2);
        *(*(mat_rev + j) + 2) = temp;
    }
    return qErrorNone;
}
/*****************************************************************************************************************
Name:        getCalculationUnitType
Description: compare calculation unit type
Argin:       sCalculationUnitType   external calculation unit type
Argout:      None
return:      comparison results
*****************************************************************************************************************/
bool GPUQuantumGates::compareCalculationUnitType(string& sCalculationUnitType)
{
    bool bResult = false;

    if (0 == sCalculationUnitType.compare(this->sCalculationUnitType))
    {
        bResult = true;
    }
    else
    {
        bResult = false;
    }

    return bResult;
}

/*****************************************************************************************************************
Name:        NOT
Description: NOT gate,invert the state.The matrix is
             [0 1;1 0]
Argin:       qn          qubit number that the Hadamard gate operates on.
             error_rate  the errorrate of the gate
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::NOT(size_t qn, double error_rate)
{
    GATEGPU::pNOT pNot = (GATEGPU::pNOT)dllFun(mGPUDll, "NOT");

    if (nullptr == pNot)
    {
        return undefineError;
    }

    if (!pNot(mvQuantumStat, qn, 0))
    {
        return undefineError;
    }
    
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        NOT
Description: NOT gate,invert the state.The matrix is
             [0 1;1 0]
Argin:       qn                 qubit number that the Hadamard gate operates on.
             error_rate         the errorrate of the gate
             vControlBit        control bit vector
             stQuantumBitNumber quantum bit number
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::NOT(size_t  qn,
                            double  error_rate,
                            Qnum    vControlBit,
                            int     stQuantumBitNumber)
{
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        toffoli
Description: toffoli gate,the same as toffoli gate
Argin:       stControlBit1       first control qubit
             stControlBit2       the second control qubit
             stQuantumBit        target qubit
             errorRate           the errorrate of the gate
             stQuantumBitNumber  quantum bit number
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError GPUQuantumGates::toffoli(size_t stControlBit1,
                                size_t stControlBit2,
                                size_t stQuantumBit,
                                double errorRate,
                                int    stQuantumBitNumber)
{
    GATEGPU::pToffoli pToffoli = (GATEGPU::pToffoli)dllFun(mGPUDll, "toffoli");

    if (nullptr == pToffoli)
    {
        return undefineError;
    }

    if (!pToffoli(mvQuantumStat, stControlBit1, stControlBit2, stQuantumBit, 0))
    {
        return undefineError;
    }

    return qErrorNone;
}
