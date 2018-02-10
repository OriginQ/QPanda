/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-10
Description:quantum gates API
*****************************************************************************************************************/
#pragma once
#include "QuantumGates.h"
using std::vector;
using std::complex;
using std::string;

class  QuantumGatesAPI
{
    typedef vector< QuantumGates *> vQuantumGatesClass;                 /* QuantumGatesClass Vector type        */
private:
    vQuantumGatesClass  mQuantumGatesClassQuenue;                       /* QuantumGatesClass Vector             */

    QuantumGates       *mpQuantumGates = NULL;                          /* global Quantum Gates Class pointer   */

    QState  mvQuantumStat;
public:
  
    /*************************************************************************************************************
    Name:        QuantumGatesAPI
    Description: initialize the quantum gates API class
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    QuantumGatesAPI();

    /*************************************************************************************************************
    Name:        ~QuantumGatesAPI
    Description: destruct the quantum gates API class
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    ~QuantumGatesAPI();

    /*************************************************************************************************************
    Name:        getQuantumStat
    Description: get quantum state
    Argin:       qsResult  
    Argout:      qsResult
    return:      None
    *************************************************************************************************************/
    inline void getQuantumStat(QState & qsResult)
    {
        qsResult = mvQuantumStat;
    }

    /*************************************************************************************************************
    Name:        selectCalculationUnit
    Description: select calculation unit type
    Argin:       cCalculationUnitType    calculation unit type
    Argout:      None
    return:      quantum error
    *************************************************************************************************************/
    QError selectCalculationUnit(string & sCalculationUnitType);

    /*****************************************************************************************************************
    Name:        initState
    Description: initialize the quantum state
    Argin:       stNumber  Quantum number
    Argout:      Nome
    return:      quantum error
    *****************************************************************************************************************/
    QError initState(size_t stNumber);

    /*************************************************************************************************************
    Name:        Hadamard
    Description: Hadamard gate,the matrix is:[1/sqrt(2),1/sqrt(2);1/sqrt(2),-1/sqrt(2)]
    Argin:       stQubitNumber      qubit number that the Hadamard gate operates on.
                 errorRate          the errorrate of the gate
                 vControlBit        control bit vector
                 stQuantumBitNumber quantum bit number   
    Argout:      vQuantumStat       quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError Hadamard(size_t stQubitNumber, double errorRate, Qnum &vControlBit,size_t stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        RX
    Description: RX gate,quantum state rotates ¦È by x axis.The matric is:
                 [cos(¦È/2),-i*sin(¦È/2);i*sin(¦È/2),cos(¦È/2)]
    Argin:       stQubitNumber  qubit number that the Hadamard gate operates on.
                 theta              rotation angle
                 errorRate          the errorrate of the gate
                 iDagger            is dagger
                 vControlBit        control bit vector
                 stQuantumBitNumber quantum bit number
    Argout:      vQuantumStat quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError RX(size_t  stQubitNumber,
              double  theta,
              double  errorRate, 
              int     iDagger,
              Qnum   &vControlBit,
              size_t  stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        RY
    Description: RY gate,quantum state rotates ¦È by y axis.The matric is
                 [cos(¦È/2),-sin(¦È/2);sin(¦È/2),cos(¦È/2)]
    Argin:       stQubitNumber      qubit number that the Hadamard gate operates on.
                 theta              rotation angle
                 errorRate          the errorrate of the gate
                 vControlBit        control bit vector
                 stQuantumBitNumber quantum bit number
    Argout:      vQuantumStat  quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError RY(size_t  stQubitNumber,
              double  theta,
              double  errorRate,
              Qnum   &vControlBit,
              size_t  stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        RZ
    Description: RZ gate,quantum state rotates ¦È by z axis.The matric is
                 [1 0;0 exp(i*¦È)]
    Argin:       stQubitNumber      qubit number that the Hadamard gate operates on.
                 theta              rotation angle
                 errorRate          the errorrate of the gate
                 iDagger            is dagger
                 vControlBit        control bit vector
                 stQuantumBitNumber quantum bit number
    Argout:      vQuantumStat       quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError RZ(size_t  stQubitNumber,
              double  theta,
              double  errorRate,
              int     iDagger,
              Qnum   &vControlBit,
              size_t  stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        CNOT
    Description: CNOT gate
    Argin:       stQubitNumber1     control qubit number
                 stQubitNumber2     goal qubit number
                 errorRate          the errorrate of the gate
                 vControlBit        control bit vector
                 stQuantumBitNumber quantum bit number
    Argout:      vQuantumStat       quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError CNOT(size_t  stQubitNumber1,
                size_t  stQubitNumber2,
                double  errorRate,
                Qnum   &vControlBit,
                size_t  stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        CR
    Description: CR gate,when control qubit is |0>,goal qubit does not rotate,
                 when control qubit is |1>,goal qubit rotate ¦È by z axis.the matric is:
                 [1 0 0 0;0 1 0 0;0 0 1 0;0 0 0 exp(i*¦È)]
    Argin:       stQubitNumber1  control qubit number
                 stQubitNumber2  goal qubit number
                 theta           roration angle
                 errorRate       the errorrate of the gate
                 iDagger         is dagger
    Argout:      vQuantumStat  quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError CR(size_t stQubitNumber1,
              size_t stQubitNumber2,
              double theta,
              double errorRate,
              int    iDagger);

    /*************************************************************************************************************
    Name:        iSWAP
    Description: iSWAP gate,both qubits swap and rotate ¦Ð by z-axis,the matric is:
                 [1 0 0 0;0 0 -i 0;0 -i 0 0;0 0 0 1]
    Argin:       stQubitNumber1     first qubit number
                 stQubitNumber2     second qubit number
                 errorRate          the errorrate of the gate
                 iDagger            is dagger
                 vControlBit        control bit vector
                 stQuantumBitNumber quantum bit number
    Argout:      vQuantumStat  quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError iSWAP(size_t  stQubitNumber1,
                 size_t  stQubitNumber2,
                 double  errorRate,
                 int     iDagger,
                 Qnum   &vControlBit,
                 int     stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        sqiSWAP
    Description: sqiSWAP gate,both qubits swap and rotate ¦Ð by z-axis,the matrix is:
                 [1 0 0 0;0 1/sqrt(2) -i/sqrt(2) 0;0 -i/sqrt(2) 1/sqrt(2) 0;0 0 0 1]
    Argin:       stQubitNumber1     first qubit number
                 stQubitNumber2     second qubit number
                 errorRate          the errorrate of the gate
                 iDagger            is dagger
                 vControlBit        control bit vector
                 stQuantumBitNumber quantum bit number
    Argout:      vQuantumStat  quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError sqiSWAP(size_t  stQubitNumber1,
                   size_t  stQubitNumber2,
                   double  errorRate,
                   int     iDagger,
                   Qnum   &vControlBit,
                   int     stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        controlSwap
    Description: c-swap gate
    Argin:       controlstQubitNumber   control qubit number
                 stQubitNumber1         1st swap qubit number
                 stQubitNumber2         2nd swap qubit number
                 errorRate           the errorrate of the gate
    Argout:      vQuantumStat         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError controlSwap(size_t  controlstQubitNumber,
                       size_t  stQubitNumber1,
                       size_t  stQubitNumber2, 
                       double  errorRate);

    /*************************************************************************************************************
    Name:        qubitMeasure
    Description: measure qubit and the state collapsed
    Argin:       stQubitNumber    qubit number of the measurement
    Argout:      vQuantumStat   the state after measurement
    return:      quantum error
    *************************************************************************************************************/
    int qubitMeasure(size_t stQubitNumber);

    /*************************************************************************************************************
    Name:        unitarySingleQubitGate
    Description: unitary single qubit gate
    Argin:       stQubitNumber   target qubit number
                 matrix        matrix of the gate
                 errorRate     the errorrate of the gate
    Argout:      vQuantumStat  the state after measurement
    return:      quantum error
    *************************************************************************************************************/
    QError unitarySingleQubitGate(size_t  stQubitNumber,
                                  QState& matrix, 
                                  double  errorRate);

    /*************************************************************************************************************
    Name:        NOT
    Description: NOT gate,invert the state.The matrix is
                 [0 1;1 0]
    Argin:       stQubitNumber      qubit number that the Hadamard gate operates on.
                 errorRate          the errorrate of the gate
                 vControlBit        control bit vector
                 stQuantumBitNumber quantum bit number
    Argout:      None
    return:      quantum error
    *************************************************************************************************************/
    QError NOT(size_t  stQubitNumber,
               double  errorRate,
               Qnum   &vControlBit,
               int     stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        toffoli
    Description: toffoli dagger gate,the same as toffoli gate
    Argin:       stControlBit1       first control qubit
                 stControlBit2       the second control qubit
                 stQuantumBit        target qubit
                 errorRate           the errorrate of the gate
                 stQuantumBitNumber  quantum bit number
    Argout:      None
    return:      quantum error
    *************************************************************************************************************/
    QError toffoli(size_t stControlBit1,
                   size_t stControlBit2,
                   size_t stQuantumBit,
                   double errorRate,
                   int    stQuantumBitNumber);
};

