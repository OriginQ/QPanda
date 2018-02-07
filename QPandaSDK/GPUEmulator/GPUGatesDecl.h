/***********************************************************************
Copyright:
Author:Xue Cheng
Date:2017-12-13
Description: Cuda function of quantum gates, defined in GPUGates.cu
************************************************************************/

#pragma once
#include "GPUStruct.h"
#include <string>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;
#define DLLAPI extern "C" _declspec(dllexport)

//#define QNum 24
//#define BLOCKDIM ((1<<(QNum-1))/THREADDIM)
//#define Dim  (1<<QNum)

namespace GATEGPU
{
    //#define STATE_T double
    typedef pair<size_t, double> PAIR;
    typedef vector<PAIR> vecprob;                          //pmeasure ∑µªÿ¿‡–Õ
    typedef vector<size_t> Qnum;
    //void unitarySingleQubitGate(QState psi, size_t Block, double *matr);
    typedef vector< size_t> vecuint;



    typedef int (*pDevicecount)();
    typedef bool (*pInitstate)(QState& psi, QState& psigpu, int);
    typedef bool (*pDestroyState)(QState& psi, QState& psigpu, size_t sQnum);
    typedef bool (*pClearState)(QState& psi, QState& psigpu, size_t sQnum);
    typedef bool (*pHadamard)(QState& psi, size_t qn, double error_rate);
    typedef bool (*pHadamardnew)(QState& psi, size_t qn, double error_rate);
    typedef bool (*pHadamarddagger)(QState& psi, size_t qn, double error_rate);
    typedef bool (*pRX)(QState& psi, size_t, double, double error_rate);
    typedef bool (*pRXdagger)(QState& psi, size_t, double, double error_rate);
    typedef bool (*pRY)(QState& psi, size_t, double, double error_rate);
    typedef bool (*pRYdagger)(QState& psi, size_t, double, double error_rate);
    typedef bool (*pRZ)(QState& psi, size_t, double, double error_rate);
    typedef bool (*pRZdagger)(QState& psi, size_t, double, double error_rate);
    typedef bool (*pNOT)(QState& psi, size_t qn, double error_rate);
    typedef bool (*pNOTdagger)(QState& psi, size_t qn, double error_rate);
    typedef bool (*pCNOT)(QState& psi, size_t, size_t, double error_rate);
    typedef bool (*pCNOTdagger)(QState& psi, size_t, size_t, double error_rate);
    typedef bool (*pCR)(QState& psi, size_t, size_t, double, double error_rate);
    typedef bool (*pCRdagger)(QState& psi, size_t, size_t, double, double error_rate);
    typedef bool (*piSWAP)(QState& psi, size_t, size_t, double error_rate);
    typedef bool (*pISWAPdagger)(QState& psi, size_t, size_t, double error_rate);
    typedef bool (*pSqiSWAP)(QState& psi, size_t, size_t, double error_rate);
    typedef bool (*SqiSWAPdagger)(QState& psi, size_t, size_t, double error_rate);
    typedef int (*pQubitmeasure)(QState& psi, size_t Block);
    typedef bool (*pControlHadamard)(QState& psi, Qnum&, double error_rate);
    typedef bool (*pControlHadamarddagger)(QState& psi, Qnum&, double error_rate);
    typedef bool (*pControlRX)(QState& psi, Qnum&, double, double error_rate);
    typedef bool (*pControlRXdagger)(QState& psi, Qnum&, double, double error_rate);
    typedef bool (*pControlRY)(QState& psi, Qnum&, double, double error_rate);
    typedef bool (*pControlRYdagger)(QState& psi, Qnum&, double, double error_rate);
    typedef bool (*pControlRZ)(QState& psi, Qnum&, double, double error_rate);
    typedef bool (*pControlRZdagger)(QState& psi, Qnum&, double, double error_rate);
    typedef bool (*pToffoli)(QState& psi, size_t, size_t, size_t, double error_rate);
    typedef bool (*pToffolidagger)(QState& psi, size_t, size_t, size_t, double error_rate);
    typedef bool (*pQbReset)(QState& psi, size_t, double error_rate);
    typedef bool (*pPMeasure)(QState&, vecprob&, size_t *block, size_t m);
    typedef bool (*pPMeasurenew)(QState&, vector<pair<size_t, double>>&, Qnum&);
    typedef bool(*pGetState)(QState &psi,QState &psigpu,int qnum);
}



/*

void controlSwap(QState&, size_t, size_t, size_t, double error_rate = 0);
void unitarySingleQubitGate(QState&, size_t, QState&, double error_rate = 0);                //unitary single qubit gate
string::iterator fgetw(string::iterator);
void qbReset(QState&, size_t qn);
mprob pMeasure(QState&, Qnum&);
*/
//vecuint qnumtostate(vecuint& qn);

