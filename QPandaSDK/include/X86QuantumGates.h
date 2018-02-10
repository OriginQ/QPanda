/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-10
Description:x86 quantum logic gates class
*****************************************************************************************************************/
#pragma once
#include "QuantumGates.h"
#include <stdio.h>
#include <iostream>    

using std::string;
using std::vector;
class X86QuantumGates :public QuantumGates
{
public:
     X86QuantumGates();
    ~X86QuantumGates();

    /*************************************************************************************************************
    Name:        Hadamard
    Description: Hadamard gate,the matrix is:[1/sqrt(2),1/sqrt(2);1/sqrt(2),-1/sqrt(2)]
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn           qubit number that the Hadamard gate operates on.
                 error_rate   the errorrate of the gate
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError Hadamard(QState& psi, size_t qn, double error_rate);

    /*************************************************************************************************************
    Name:        Hadamard
    Description: controled-Hadamard gate
    Argin:       psi                reference of vector<complex<double>> which contains quantum state information.
                 qn                 qubit number that the Hadamard gate operates on.
                 error_rate         the errorrate of the gate
                 vControlBit        control bit vector
                 stQuantumBitNumber quantum bit number
    Argout:      psi                quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError Hadamard(QState& psi, size_t qn, double error_rate, Qnum &vControlBit, size_t stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        RX
    Description: RX gate,quantum state rotates ¦È by x axis.The matric is:
                 [cos(¦È/2),-i*sin(¦È/2);i*sin(¦È/2),cos(¦È/2)]
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn          qubit number that the Hadamard gate operates on.
                 theta       rotation angle
                 error_rate  the errorrate of the gate
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError RX(QState& psi, size_t qn, double theta, double error_rate = 0);

    /*************************************************************************************************************
    Name:        RX
    Description: RX dagger gate,quantum state rotates ¦È by x axis.The matric is:
                 [cos(¦È/2),-i*sin(¦È/2);i*sin(¦È/2),cos(¦È/2)]
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn          qubit number that the Hadamard gate operates on.
                 theta       rotation angle
                 error_rate  the errorrate of the gate
                 iDagger     is dagger
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError RX(QState& psi, size_t qn, double theta, double error_rate, int iDagger);

    /*************************************************************************************************************
    Name:        RX
    Description: controled-RX gate
    Argin:       psi                reference of vector<complex<double>> which contains quantum state information.
                 qn                 qubit number that the Hadamard gate operates on.
                 theta              rotation angle
                 error_rate         the errorrate of the gate
                 vControlBitNumber  control bit number
                 stQuantumBitNumber quantum bit number
    Argout:      psi                quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError RX(QState &psi, 
              size_t  qn, 
              double  theta, 
              double  error_rate,
              Qnum   &vControlBitNumber,
              size_t  stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        RX
    Description: controled-RX dagger gate
    Argin:       psi                reference of vector<complex<double>> which contains quantum state information.
                 qn                 qubit number that the Hadamard gate operates on.
                 theta              rotation angle
                 error_rate         the errorrate of the gate
                 vControlBitNumber  control bit number
                 stQuantumBitNumber quantum bit number
                 iDagger            is dagger
    Argout:      psi                quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError RX(QState &psi,
              size_t  qn,
              double  theta,
              double  error_rate,
              Qnum   &vControlBitNumber,
              size_t  stQuantumBitNumber,
              int     iDagger);

    /*************************************************************************************************************
    Name:        RY
    Description: RY gate,quantum state rotates ¦È by y axis.The matric is
                 [cos(¦È/2),-sin(¦È/2);sin(¦È/2),cos(¦È/2)]
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn          qubit number that the Hadamard gate operates on.
                 theta       rotation angle
                 error_rate  the errorrate of the gate
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError RY(QState& psi, size_t qn, double theta, double error_rate = 0);

    /*************************************************************************************************************
    Name:        RY
    Description: RY control gate
    Argin:       psi                reference of vector<complex<double>> which contains quantum state information.
                 qn                 qubit number that the Hadamard gate operates on.
                 theta              rotation angle
                 error_rate         the errorrate of the gate
                 vControlBit        control bit vector
                 stQuantumBitNumber quantum bit number
    Argout:      psi                quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError RY(QState  &psi,
              size_t   qn,
              double   theta,
              double   error_rate,
              Qnum    &vControlBit,
              size_t   stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        RZ
    Description: RZ gate,quantum state rotates ¦È by z axis.The matric is
                 [1 0;0 exp(i*¦È)]
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn          qubit number that the Hadamard gate operates on.
                 theta       rotation angle
                 error_rate  the errorrate of the gate
                 iDagger     is dagger
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError RZ(QState& psi, size_t qn, double theta, double error_rate,int iDagger);

    /*************************************************************************************************************
    Name:        RZ
    Description: RZ gate
    Argin:       psi                reference of vector<complex<double>> which contains quantum state information.
                 qn                 qubit number that the Hadamard gate operates on.
                 theta              rotation angle
                 error_rate         the errorrate of the gate
                 vControlBitNumber  control bit number
                 stQuantumBitNumber quantum bit number
                 iDagger            is dagger
    Argout:      psi                quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError RZ(QState  &psi,
              size_t   qn,
              double   heta,
              double   error_rate,
              Qnum    &vControlBitNumber,
              size_t   stQuantumBitNumber,
              int      iDagger);

    /*************************************************************************************************************
    Name:        CNOT
    Description: CNOT gate,when control qubit is |0>,goal qubit does flip,
                 when control qubit is |1>,goal qubit flips.the matric is:
                 [1 0 0 0;0 1 0 0;0 0 0 1;0 0 1 0]
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn_1        control qubit number
                 qn_2        goal qubit number
                 error_rate  the errorrate of the gate
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError CNOT(QState& psi, size_t qn_1, size_t qn_2, double error_rate = 0);

    /*************************************************************************************************************
    Name:        CNOT
    Description: CNOT control gate
    Argin:       psi                reference of vector<complex<double>> which contains quantum state information.
                 qn_1               control qubit number
                 qn_2               goal qubit number
                 error_rate         the errorrate of the gate
                 vControlBitNumber  control bit number
                 stQuantumBitNumber quantum bit number
    Argout:      psi                quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError CNOT(QState &psi,
                size_t  qn_1,
                size_t  qn_2,
                double  error_rate,
                Qnum   &vControlBitNumber,
                int     stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        CR
    Description: CR gate,when control qubit is |0>,goal qubit does not rotate,
                 when control qubit is |1>,goal qubit rotate ¦È by z axis.the matric is:
                 [1 0 0 0;0 1 0 0;0 0 1 0;0 0 0 exp(i*¦È)]
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn_1        control qubit number
                 qn_2        goal qubit number
                 theta       roration angle
                 error_rate  the errorrate of the gate
                 iDagger     is dagger
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError CR(QState &psi,
              size_t  qn_1,
              size_t  qn_2,
              double  theta,
              double  error_rate,
              int     iDagger);

    /*************************************************************************************************************
    Name:        iSWAP
    Description: iSWAP gate,both qubits swap and rotate ¦Ð by z-axis,the matric is:
    [1 0 0 0;0 0 -i 0;0 -i 0 0;0 0 0 1]
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn_1        first qubit number
                 qn_2        second qubit number
                 error_rate  the errorrate of the gate
                 iDagger     is dagger
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError iSWAP(QState &psi,
                 size_t  qn_1,
                 size_t  qn_2,
                 double  error_rate,
                 int     iDagger);

    /*************************************************************************************************************
    Name:        iSWAP
    Description: iSWAP gate,both qubits swap and rotate ¦Ð by z-axis,the matric is:
    [1 0 0 0;0 0 -i 0;0 -i 0 0;0 0 0 1]
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn_1        first qubit number
                 qn_2        second qubit number
                 error_rate  the errorrate of the gate
                 vControlBitNumber  control bit number
                 stQuantumBitNumber quantum bit number
                 iDagger     is dagger
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError iSWAP(QState &psi,
                 size_t  qn_1,
                 size_t  qn_2,
                 double  error_rate,
                 Qnum   &vControlBitNumber,
                 int     stQuantumBitNumber,
                 int     iDagger);

    /*************************************************************************************************************
    Name:        sqiSWAP
    Description: sqiSWAP gate,both qubits swap and rotate ¦Ð by z-axis,the matrix is:
                 [1 0 0 0;0 1/sqrt(2) -i/sqrt(2) 0;0 -i/sqrt(2) 1/sqrt(2) 0;0 0 0 1]
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn_1        first qubit number
                 qn_2        second qubit number
                 error_rate  the errorrate of the gate
                 iDagger     is dagger
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError sqiSWAP(QState &psi,
                   size_t  qn_1,
                   size_t  qn_2,
                   double  error_rate,
                   int     iDagger);

    /*************************************************************************************************************
    Name:        sqiSWAP
    Description: sqiSWAP gate,both qubits swap and rotate ¦Ð by z-axis,the matrix is:
                 [1 0 0 0;0 1/sqrt(2) -i/sqrt(2) 0;0 -i/sqrt(2) 1/sqrt(2) 0;0 0 0 1]
    Argin:       psi                reference of vector<complex<double>> which contains quantum state information.
                 qn_1               first qubit number
                 qn_2               second qubit number
                 error_rate         the errorrate of the gate
                 vControlBitNumber  control bit number
                 stQuantumBitNumber quantum bit number
                 iDagger            is dagger
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError sqiSWAP(QState &psi,
                   size_t  qn_1,
                   size_t  qn_2,
                   double  error_rate,
                   Qnum   &vControlBitNumber,
                   int     stQuantumBitNumber,
                   int     iDagger);

    /*************************************************************************************************************
    Name:        controlSwap
    Description: c-swap gate
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn_1        control qubit number
                 qn_2        1st swap qubit number
                 qn_3        2nd swap qubit number
                 error_rate  the errorrate of the gate
    Argout:      psi         quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError controlSwap(QState& psi, size_t qn_1, size_t qn_2, size_t qn_3, double error_rate = 0);



    /*************************************************************************************************************
    Name:        qubitMeasure
    Description: measure qubit and the state collapsed
    Argin:       psi   reference of vector<complex<double>> which contains quantum state information.
                 qn    qubit number of the measurement
    Argout:      psi   the state after measurement
    return:      quantum error
    *************************************************************************************************************/
    int qubitMeasure(QState& psi, size_t qn);

    /*************************************************************************************************************
    Name:        unitarySingleQubitGate
    Description: unitary single qubit gate
    Argin:       psi         reference of vector<complex<double>> which contains quantum state information.
                 qn          target qubit number
                 matrix      matrix of the gate
                 error_rate  the errorrate of the gate
    Argout:      psi         the state after measurement
    return:      quantum error
    *************************************************************************************************************/
    QError unitarySingleQubitGate(QState& psi, size_t qn, QState& matrix, double error_rate = 0);

    /*****************************************************************************************************************
    Name:        initState
    Description: initialize the quantum state
    Argin:       psi       reference of vector<complex<double>> which contains quantum state information.
    stNumber  Quantum number
    Argout:      psi       the state after measurement
    return:      quantum error
    *****************************************************************************************************************/
    QError initState(QState& psi, size_t stNumber);

    /*************************************************************************************************************
    Name:        matReverse
    Description: change the position of the qubits in 2-qubit gate
    Argin:       (*mat)[4]       pointer of the origin 2D array
                 (*mat_rev)[4]   pointer of the changed 2D array
    Argout:      2D array
    return:      quantum error
    *************************************************************************************************************/
    QError matReverse(COMPLEX(*)[4], COMPLEX(*)[4]);

    /*************************************************************************************************************
    Name:        compareCalculationUnitType
    Description: compare calculation unit type
    Argin:       sCalculationUnitType   external calculation unit type
    Argout:      None
    return:      comparison results
    *************************************************************************************************************/
    bool compareCalculationUnitType(string& sCalculationUnitType);

        /*************************************************************************************************************
    Name:    NOT
    Description: NOT gate,invert the state.The matrix is
                 [0 1;1 0]
    Argin:       psi                reference of vector<complex<double>> which contains quantum state information.
                 qn                 qubit number that the Hadamard gate operates on.
                 error_rate         the errorrate of the gate
    Argout:      psi     quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError NOT(QState &psi,
               size_t  qn,
               double  error_rate);

    /*************************************************************************************************************
    Name:    NOT
    Description: NOT gate,invert the state.The matrix is
                 [0 1;1 0]
    Argin:       psi                reference of vector<complex<double>> which contains quantum state information.
                 qn                 qubit number that the Hadamard gate operates on.
                 error_rate         the errorrate of the gate
                 vControlBit        control bit vector
                 stQuantumBitNumber quantum bit number
    Argout:      psi     quantum state after the gate
    return:      quantum error
    *************************************************************************************************************/
    QError NOT(QState &psi,
               size_t  qn,
               double  error_rate,
               Qnum   &vControlBit,
               int     stQuantumBitNumber);

    /*************************************************************************************************************
    Name:        toffoli
    Description: toffoli dagger gate,the same as toffoli gate
    Argin:       psi                 reference of vector<complex<double>> which contains quantum state information.
                 stControlBit1       first control qubit
                 stControlBit2       the second control qubit
                 stQuantumBit        target qubit
                 errorRate           the errorrate of the gate
                 stQuantumBitNumber  quantum bit number
    Argout:      None
    return:      quantum error
    *************************************************************************************************************/
    QError toffoli(QState &psi,
                   size_t stControlBit1,
                   size_t stControlBit2,
                   size_t stQuantumBit,
                   double errorRate,
                   int    stQuantumBitNumber);

    protected:
        string sCalculationUnitType = "X86";
        
};

