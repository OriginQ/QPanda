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
Description:x86 quantum logic gates class
*****************************************************************************************************************/
#include "CPUQuantumGates.h"
#include <algorithm>
#include <thread>
#include <map>
#include <iostream>
#include <sstream>
//#include <omp.h>

using namespace std;

#define SQ2 0.707106781186548
//#define LONG long long
typedef vector<complex<double>> QStat;


#define POW2(N) (1ull<<(N))
typedef size_t  LONG;
CPUQuantumGates::CPUQuantumGates()
{
}

CPUQuantumGates::~CPUQuantumGates()
{
    mvQuantumStat.clear();
}

size_t CPUQuantumGates::getQStateSize()
{
    return mvQuantumStat.size();
}

/*****************************************************************************************************************
Name:        getQState
Description: get quantum state
Argin:       pQuantumProParam       quantum program prarm pointer
Argout:      sState                 string state
return:      quantum error
*****************************************************************************************************************/
bool CPUQuantumGates::getQState(string & sState, QuantumGateParam *pQuantumProParam)
{
    stringstream ssTemp;
    int i = 0;

    if (mvQuantumStat.size() <= 0)
        return false;
    for (auto aiter : mvQuantumStat)
    {
        ssTemp << "state[" << i << "].real = "
            << aiter.real() << " "
            << "state[" << i << "].imag = "
            << aiter.imag() << "\n";
        i++;
    }

    sState.append(ssTemp.str());
    return true;
}

/*****************************************************************************************************************
Name:        Hadamard
Description: Hadamard gate,the matrix is:[1/sqrt(2),1/sqrt(2);1/sqrt(2),-1/sqrt(2)]
Argin:       qn           qubit number that the Hadamard gate operates on.
error_rate   the errorrate of the gate
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError CPUQuantumGates::Hadamard(size_t qn, double error_rate)
{
    /*
    *  judge errorrate of the gate
    */
    if (randGenerator() > error_rate)
    {
        size_t ststep = POW2(qn);
        COMPLEX alpha, beta;

        LONG j;
#pragma omp parallel for private(j,alpha,beta)
        for (LONG i = 0; i < (LONG)mvQuantumStat.size(); i += ststep * 2)
        {
            for (j = i; j<(i + ststep); j++)
            {
                alpha = mvQuantumStat[j];
                beta = mvQuantumStat[j + ststep];
                mvQuantumStat[j] = (alpha + beta)*SQ2;         /* in j,the goal qubit is in |0>        */
                mvQuantumStat[j + ststep] = (alpha - beta)*SQ2;         /* in j+ststep,the goal qubit is in |1> */
            }
        }
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
QError CPUQuantumGates::Reset(size_t qn)
{

    //#pragma omp parallel for private(j,alpha,beta)
    bool bOutcome = qubitMeasure(qn);
    if (bOutcome)
    {
        NOT(qn, 0);
    }
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        probcompare
Description: prob compare
Argin:       a        pair
b        pair
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool probcompare(pair<size_t, double>& a, pair<size_t, double>& b)
{
    return a.second > b.second;
}

/*****************************************************************************************************************
Name:        pMeasure
Description: pMeasure gate
Argin:       qnum        qubit bit number vector
mResult     reuslt vector
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError CPUQuantumGates::pMeasure(Qnum& qnum, vector<pair<size_t, double>> &mResult)
{
    mResult.resize(POW2(qnum.size()));
    for (size_t i = 0; i < POW2(qnum.size()); i++)
    {
        mResult[i].first = i;
        mResult[i].second = 0;
    }

    for (LONG i = 0; i < mvQuantumStat.size(); i++)
    {
        LONG idx = 0;
        for (LONG j = 0; j < (LONG)qnum.size(); j++)
        {
            idx += (((i >> (qnum[j])) % 2) << j);
        }
        mResult[idx].second += abs(mvQuantumStat[i])*abs(mvQuantumStat[i]);
    }

    if (mResult.size() <= 10)
    {
        sort(mResult.begin(), mResult.end(), probcompare);
        return qErrorNone;
    }
    else
    {
        sort(mResult.begin(), mResult.end(), probcompare);
        mResult.erase(mResult.begin() + 10, mResult.end());
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
QError CPUQuantumGates::Hadamard(size_t  qn,
    double  error_rate,
    Qnum    vControlBit,
    size_t  stQuantumBitNumber)
{
    if (randGenerator() > error_rate)
    {
        LONG M = (LONG)(mvQuantumStat.size() / POW2(vControlBit.size()));
        LONG x;

        LONG n = stQuantumBitNumber;
        LONG ststep = POW2(qn);
        LONG index = 0;
        LONG block = 0;

        COMPLEX alpha, beta;

        sort(vControlBit.begin(), vControlBit.end());
        for (Qnum::iterator j = vControlBit.begin(); j != vControlBit.end(); j++)
        {
            block += POW2(*j);
        }

        Qnum::iterator qiter;

        LONG j;
#pragma omp parallel for private(j,alpha,beta,index,x,qiter)
        for (LONG i = 0; i < M; i++)
        {
            index = 0;
            x = i;
            qiter = vControlBit.begin();

            for (j = 0; j < n; j++)
            {
                while (qiter != vControlBit.end() && *qiter == j)
                {
                    qiter++;
                    j++;
                }
                index += ((x % 2)*POW2(j));
                x >>= 1;
            }

            /*
            * control qubits are 1,target qubit is 0
            */
            index = index + block - ststep;
            alpha = mvQuantumStat[index];
            beta = mvQuantumStat[index + ststep];
            mvQuantumStat[index] = (alpha + beta)*SQ2;
            mvQuantumStat[index + ststep] = (alpha - beta)*SQ2;
        }
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
QError CPUQuantumGates::RX(size_t qn, double theta, double error_rate, int iDagger)
{

    /*
    *  judge errorrate of the gate
    */
    if (randGenerator() > error_rate)
    {
        LONG ststep = POW2(qn);

        double dcostheta = cos(theta / 2);
        double dsintheta = sin(theta / 2);

        COMPLEX alpha, beta;
        COMPLEX compll(0, -1);
        if (iDagger)
        {
            compll = COMPLEX(0, 1);
        }

        /*
        *  traverse all the states
        */
        LONG j;
#pragma omp parallel for private(j,alpha,beta)
        for (LONG i = 0; i < (LONG)mvQuantumStat.size(); i += ststep * 2)
        {
            for (j = i; j != i + ststep; j++)
            {
                alpha = mvQuantumStat[j];
                beta = mvQuantumStat[j + ststep];
                mvQuantumStat[j] = alpha * dcostheta + compll * dsintheta*beta;
                mvQuantumStat[j + ststep] = beta * dcostheta + compll * dsintheta*alpha;
            }
        }
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
QError CPUQuantumGates::RX(size_t  qn,
    double  theta,
    double  error_rate,
    Qnum    vControlBitNumber,
    size_t  stQuantumBitNumber,
    int     iDagger)
{
    if (randGenerator() > error_rate)
    {

        LONG x;
        LONG M = (LONG)(mvQuantumStat.size() / POW2(vControlBitNumber.size()));

        LONG  n = stQuantumBitNumber;
        LONG  ststep = POW2(qn);
        LONG  index = 0;
        LONG block = 0;

        double  dcostheta = cos(theta / 2);
        double  dsintheta = sin(theta / 2);

        COMPLEX alpha, beta;
        COMPLEX compll(0, 1);
        if (iDagger)
        {
            compll = COMPLEX(0, -1);
        }
        sort(vControlBitNumber.begin(), vControlBitNumber.end());
        for (Qnum::iterator j = vControlBitNumber.begin(); j != vControlBitNumber.end(); j++)
        {
            block += POW2(*j);
        }

        Qnum::iterator qiter;

        LONG j;
#pragma omp parallel for private(j,alpha,beta,index,x,qiter)
        for (LONG i = 0; i < M; i++)
        {
            index = 0;
            x = i;
            qiter = vControlBitNumber.begin();
            for (j = 0; j < n; j++)
            {
                while (qiter != vControlBitNumber.end() && *qiter == j)
                {
                    qiter++;
                    j++;
                }
                index += ((x % 2)*POW2(j));
                x >>= 1;
            }
            index = index + block - ststep;
            alpha = mvQuantumStat[index];
            beta = mvQuantumStat[index + ststep];
            mvQuantumStat[index] = alpha * dcostheta - compll * dsintheta*beta;
            mvQuantumStat[index + ststep] = beta * dcostheta - compll * dsintheta*alpha;
        }
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
QError CPUQuantumGates::RY(size_t   qn,
    double   theta,
    double   error_rate,
    Qnum     vControlBit,
    size_t   stQuantumBitNumber, int iDagger)
{
    if (randGenerator() > error_rate)
    {
        LONG M = (mvQuantumStat.size() / POW2(vControlBit.size()));
        LONG x;

        LONG qn = vControlBit.back();
        LONG n = stQuantumBitNumber;
        LONG ststep = POW2(qn);
        LONG index = 0;
        LONG block = 0;

        double dcostheta = cos(theta / 2);
        double dsintheta = sin(theta / 2);

        COMPLEX alpha, beta;

        sort(vControlBit.begin(), vControlBit.end());
        for (Qnum::iterator j = vControlBit.begin(); j != vControlBit.end(); j++)
        {
            block += (size_t)pow(2, *j);
        }

        Qnum::iterator qiter;
        LONG j;
#pragma omp parallel for private(j,alpha,beta,index,x,qiter)
        for (LONG i = 0; i < M; i++)
        {
            index = 0;
            x = i;
            qiter = vControlBit.begin();
            for (j = 0; j < n; j++)
            {
                while (qiter != vControlBit.end() && *qiter == j)
                {
                    qiter++;
                    j++;
                }
                index += ((x % 2)*POW2(j));
                x >>= 1;
            }
            index = index + block - ststep;
            alpha = mvQuantumStat[index];
            beta = mvQuantumStat[index + ststep];
            if (iDagger)
            {
                mvQuantumStat[index] = alpha * dcostheta + dsintheta * beta;
                mvQuantumStat[index + ststep] = beta * dcostheta - dsintheta * alpha;
            }
            else
            {
                mvQuantumStat[index] = alpha * dcostheta - dsintheta * beta;
                mvQuantumStat[index + ststep] = beta * dcostheta + dsintheta * alpha;
            }

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
QError CPUQuantumGates::RY(size_t qn, double theta, double error_rate, int iDagger)
{
    /*
    *  judge errorrate of the gate
    */
    if (randGenerator() > error_rate)
    {
        double dcostheta = cos(theta / 2);
        double dsintheta = sin(theta / 2);

        LONG ststep = POW2(qn);

        COMPLEX alpha, beta;
        /*
        *  traverse all the states
        */
        LONG j;
#pragma omp parallel for private(j,alpha,beta)
        for (LONG i = 0; i < (LONG)mvQuantumStat.size(); i += ststep * 2)
        {
            for (j = i; j != i + ststep; j++)
            {
                alpha = mvQuantumStat[j];
                beta = mvQuantumStat[j + ststep];
                if (iDagger)
                {
                    mvQuantumStat[j] = alpha * dcostheta + dsintheta * beta;
                    mvQuantumStat[j + ststep] = beta * dcostheta - dsintheta * alpha;
                }
                else
                {
                    mvQuantumStat[j] = alpha * dcostheta - dsintheta * beta;
                    mvQuantumStat[j + ststep] = beta * dcostheta + dsintheta * alpha;
                }
            }
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
QError CPUQuantumGates::RZ(size_t qn, double theta, double error_rate, int iDagger)
{
    /*
    *  judge errorrate of the gate
    */
    if (randGenerator() > error_rate)
    {
        LONG ststep = POW2(qn);

        double dcostheta = cos(theta / 2);
        double dsintheta = sin(theta / 2);

        COMPLEX compll;
        COMPLEX compl2;

        if (!iDagger)
        {
            compll.real(dcostheta);
            compll.imag(dsintheta);
            compl2.real(dcostheta);
            compl2.imag(-dsintheta);
        }
        else
        {
            compll.real(dcostheta);
            compll.imag(-dsintheta);
            compl2.real(dcostheta);
            compl2.imag(dsintheta);
        }

        /*
        *  traverse all the states
        */
        LONG j;
#pragma omp parallel for private(j)
        for (LONG i = 0; i < (LONG)mvQuantumStat.size(); i += ststep * 2)
        {
            for (j = i; j != i + ststep; j++)
            {
                mvQuantumStat[j] = compl2 * mvQuantumStat[j];
                mvQuantumStat[j + ststep] = compll * mvQuantumStat[j + ststep];
            }
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
QError CPUQuantumGates::RZ(size_t   qn,
    double   theta,
    double   error_rate,
    Qnum     vControlBitNumber,
    size_t   stQuantumBitNumber,
    int      iDagger)
{
    if (randGenerator() > error_rate)
    {
        LONG M = (LONG)(mvQuantumStat.size() / POW2(vControlBitNumber.size()));
        LONG x;

        LONG n = stQuantumBitNumber;
        LONG index = 0;
        LONG block = 0;

        LONG ststep = POW2(qn);

        double dcostheta = cos(theta / 2);
        double dsintheta = sin(theta / 2);

        sort(vControlBitNumber.begin(), vControlBitNumber.end());
        COMPLEX compll;
        COMPLEX compl2;

        if (!iDagger)
        {
            compll.real(dcostheta);
            compll.imag(dsintheta);
            compl2.real(dcostheta);
            compl2.imag(-dsintheta);
        }
        else
        {
            compll.real(dcostheta);
            compll.imag(-dsintheta);
            compl2.real(dcostheta);
            compl2.imag(dsintheta);
        }

        for (Qnum::iterator j = vControlBitNumber.begin(); j != vControlBitNumber.end(); j++)
        {
            block += (size_t)pow(2, *j);
        }

        Qnum::iterator qiter;
        LONG j;
#pragma omp parallel for private(j,index,x,qiter)
        for (LONG i = 0; i < M; i++)
        {
            index = 0;
            x = i;
            qiter = vControlBitNumber.begin();
            for (j = 0; j < n; j++)
            {
                while (qiter != vControlBitNumber.end() && *qiter == j)
                {
                    qiter++;
                    j++;
                }
                index += (size_t)((x % 2)*POW2(j));
                x >>= 1;
            }
            index = index + block - ststep;
            mvQuantumStat[index] = compl2 * mvQuantumStat[index];
            mvQuantumStat[index + ststep] = compll * mvQuantumStat[index + ststep];
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
QError CPUQuantumGates::CNOT(size_t qn_1, size_t qn_2, double error_rate)
{
    /*
    *  judge errorrate of the gate
    */
    if (randGenerator() > error_rate)
    {
        LONG ststep1 = POW2(qn_1);
        LONG ststep2 = POW2(qn_2);

        bool bmark;

        COMPLEX alpha, beta;

        if (qn_1>qn_2)                                                  /* control qubit number is higher       */
        {
            /*
            *  traverse all the states
            */
            LONG j, k;
#pragma omp parallel for  private(j,k,alpha,beta) 
            for (LONG i = 0; i < (LONG)mvQuantumStat.size(); i = i + ststep1)
            {
                bmark = i / ststep1 % 2;
                for (j = i; j < i + ststep1; j = j + 2 * ststep2)
                {
                    for (k = j; k < j + ststep2; k++)
                    {
                        if (bmark)
                        {
                            alpha = mvQuantumStat[k];
                            beta = mvQuantumStat[k + ststep2];
                            mvQuantumStat[k] = beta;          /* k:control |1>,goal |0>               */
                            mvQuantumStat[k + ststep2] = alpha;         /* k+ststep:control |1>,goal |1>        */
                        }

                    }
                }
            }
        }
        else                                                            /* control qubit numer is lower         */
        {
            /*
            *  traverse all the states
            */
            LONG j, k;
#pragma omp parallel for private(j,k,alpha,beta)
            for (LONG i = 0; i < (LONG)mvQuantumStat.size(); i = i + 2 * ststep2)
            {

                for (j = i; j < i + ststep2; j = j + ststep1)
                {
                    bmark = j / ststep1 % 2;
                    for (k = j; k < j + ststep1; k++)
                    {
                        if (bmark)
                        {
                            alpha = mvQuantumStat[k];
                            beta = mvQuantumStat[k + ststep2];
                            mvQuantumStat[k] = beta;
                            mvQuantumStat[k + ststep2] = alpha;
                        }
                    }
                }
            }
        }
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
QError CPUQuantumGates::CNOT(size_t  qn_1,
    size_t  qn_2,
    double  error_rate,
    Qnum    vControlBitNumber,
    int     stQuantumBitNumber)
{
    return NOT(qn_2, error_rate, vControlBitNumber, stQuantumBitNumber);
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
QError CPUQuantumGates::CR(size_t  qn_1,
    size_t  qn_2,
    double  theta,
    double  error_rate,
    int     iDagger)
{
    /*
    *  judge errorrate of the gate
    */
    if (randGenerator() > error_rate)
    {
        LONG ststep1 = POW2(qn_1);
        LONG ststep2 = POW2(qn_2);

        double dcostheta = cos(theta);
        double dsintheta = sin(theta);

        COMPLEX alpha, beta;
        COMPLEX compll;

        if (!iDagger)
        {
            compll.real(dcostheta);
            compll.imag(dsintheta);
        }
        else
        {
            compll.real(dcostheta);
            compll.imag(-dsintheta);
        }
        size_t stTemp;
        if (ststep1 < ststep2)
        {
            stTemp = ststep1;
            ststep1 = ststep2;
            ststep2 = stTemp;
        }

        LONG j, k;
#pragma omp parallel for private(j,k)
        for (LONG i = ststep1; i < (LONG)mvQuantumStat.size(); i = i + 2 * ststep1)
        {
            for (j = i + ststep2; j < i + ststep1; j = j + 2 * ststep2)
            {
                for (k = j; k < j + ststep2; k++)
                {
                    mvQuantumStat[k] = mvQuantumStat[k] * compll;
                }
            }
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
QError CPUQuantumGates::iSWAP(size_t qn_1,
    size_t qn_2,
    double error_rate,
    int    iDagger)
{
    /*
    *  judge errorrate of the gate
    */
    if (randGenerator() > error_rate)
    {
        LONG sttemp = 0;
        LONG ststep1 = POW2(qn_1);
        LONG ststep2 = POW2(qn_2);

        /*
        * iSWAP(qn_1,qn_2) is agree with
        * iSWAP(qn_2,qn_1)
        */
        if (qn_1 < qn_2)
        {
            sttemp = ststep1;
            ststep1 = ststep2;
            ststep2 = sttemp;
        }
        sttemp = ststep1 - ststep2;
        COMPLEX compll;
        if (!iDagger)
        {
            compll.real(0);
            compll.imag(1.0);
        }
        else
        {
            compll.real(0);
            compll.imag(-1.0);
        }

        COMPLEX alpha, beta;

        /*
        *  traverse all the states
        */
        LONG j, k;
#pragma omp parallel for private(j,k,alpha,beta)
        for (LONG i = 0; i < (LONG)mvQuantumStat.size(); i = i + 2 * ststep1)
        {
            for (j = i + ststep2; j < i + ststep1; j = j + 2 * ststep2)
            {
                for (k = j; k < j + ststep2; k++)
                {
                    alpha = mvQuantumStat[k];
                    beta = mvQuantumStat[k + sttemp];

                    mvQuantumStat[k] = compll * beta;           /* k:|01>                               */
                    mvQuantumStat[k + sttemp] = compll * alpha;          /* k+sttemp:|10>                        */
                }
            }
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
vControlBitNumber  control bit number
stQuantumBitNumber quantum bit number
iDagger     is dagger
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError CPUQuantumGates::iSWAP(size_t  qn_1,
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
QError CPUQuantumGates::controlSwap(size_t qn_1, size_t qn_2, size_t qn_3, double error_rate)
{
    COMPLEX alpha, beta;
    /*
    *  judge errorrate of the gate
    */
    if (randGenerator() > error_rate)
    {
        LONG  ststep1 = POW2(qn_1);
        LONG  ststep2 = POW2(qn_2);
        LONG  ststep3 = POW2(qn_3);

        /*
        *  traverse all the states
        */
        for (LONG i = ststep1; i < mvQuantumStat.size(); i = i + 2 * ststep1)
        {
            for (LONG j = i; j < i + ststep1; ++j)
            {
                if (j % (2 * ststep2) >= ststep2 && j % (2 * ststep3) < ststep3)
                {
                    alpha = mvQuantumStat[j];
                    mvQuantumStat[j] = mvQuantumStat[j - ststep2 + ststep3];

                    mvQuantumStat[j - ststep2 + ststep3] = alpha;
                }
            }
        }
    }

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
QError CPUQuantumGates::sqiSWAP(size_t  qn_1,
    size_t  qn_2,
    double  error_rate,
    int     iDagger)
{
    /*
    *  judge errorrate of the gate
    */
    if (randGenerator() > error_rate)
    {
        LONG sttemp;
        LONG ststep1 = POW2(qn_1);
        LONG ststep2 = POW2(qn_2);
        /*
        * sqiSWAP(qn_1,qn_2) is agree with
        * sqiSWAP(qn_2,qn_1)
        */
        if (qn_1 < qn_2)
        {
            sttemp = ststep1;
            ststep1 = ststep2;
            ststep2 = sttemp;
        }
        sttemp = ststep1 - ststep2;

        COMPLEX compll;

        if (!iDagger)
        {
            compll.real(0);
            compll.imag(1.0);
        }
        else
        {
            compll.real(0);
            compll.imag(-1.0);
        }
        COMPLEX alpha, beta;

        /*
        *  traverse all the states
        */
        LONG j, k;
#pragma omp parallel for private(j,k,alpha,beta)
        for (LONG i = 0; i < (LONG)mvQuantumStat.size(); i = i + 2 * ststep1)
        {
            for (j = i + ststep2; j < i + ststep1; j = j + 2 * ststep2)
            {
                for (k = j; k < j + ststep2; k++)
                {
                    alpha = mvQuantumStat[k];
                    beta = mvQuantumStat[k + sttemp];

                    mvQuantumStat[k] = alpha * SQ2 + compll * beta *SQ2;
                    mvQuantumStat[k + sttemp] = compll * alpha *SQ2 + beta * SQ2;
                }
            }
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
QError CPUQuantumGates::sqiSWAP(size_t  qn_1,
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
int CPUQuantumGates::qubitMeasure(size_t qn)
{
    LONG ststep = POW2(qn);

    double dprob(0);

    for (LONG i = 0; i< mvQuantumStat.size(); i += ststep * 2)
    {
        for (LONG j = i; j<i + ststep; j++)
        {
            dprob += abs(mvQuantumStat[j])*abs(mvQuantumStat[j]);
        }
    }
    int ioutcome(0);

    float fi = (float)randGenerator();

    if (fi> dprob)
    {
        ioutcome = 1;
    }

    /*
    *  POVM measurement
    */
    if (ioutcome == 0)
    {
        dprob = 1 / sqrt(dprob);

        LONG j;
#pragma omp parallel for private(j)
        for (LONG i = 0; i < (LONG)mvQuantumStat.size(); i = i + 2 * ststep)
        {
            for (j = i; j < i + ststep; j++)
            {
                mvQuantumStat[j] *= dprob;
                mvQuantumStat[j + ststep] = 0;
            }
        }
    }
    else
    {
        dprob = 1 / sqrt(1 - dprob);

        LONG j;
#pragma omp parallel for private(j)
        for (LONG i = 0; i < (LONG)mvQuantumStat.size(); i = i + 2 * ststep)
        {
            for (j = i; j<i + ststep; j++) {
                mvQuantumStat[j] = 0;
                mvQuantumStat[j + ststep] *= dprob;
            }
        }
    }
    return ioutcome;
}


/*****************************************************************************************************************
Name:        initState
Description: initialize the quantum state
Argin:       stNumber  Quantum number
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError CPUQuantumGates::initState(QuantumGateParam *pQuantumProParam)
{
    if (nullptr == pQuantumProParam)
    {
        return undefineError;
    }

    LONG stQuantumStat = POW2(pQuantumProParam->mQuantumBitNumber);

    try
    {
        mvQuantumStat.resize(stQuantumStat,0);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return undefineError;
    }
    mvQuantumStat[0] = 1;

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
QError CPUQuantumGates::unitarySingleQubitGate(size_t qn, void* matrix, double error_rate)
{
    /*
    *  judge errorrate of the gate
    */
    QStat  Qmatrix = *(QStat*)matrix;
    if (randGenerator() > error_rate)
    {
        COMPLEX det = Qmatrix[0] * Qmatrix[3] - Qmatrix[1] * Qmatrix[2];

        /*
        *  judge if the matrix is unitary
        */
        if (abs(abs(det) - 1) > 0.000001)
        {
            return undefineError;
        }

        LONG ststep = POW2(qn - 1);

        COMPLEX alpha, beta;

        for (LONG i = 0; i< mvQuantumStat.size(); i += ststep * 2)
        {
            for (LONG j = i; j<i + ststep; j++)
            {
                alpha = mvQuantumStat[j];
                beta = mvQuantumStat[j + ststep];

                /*
                * in j,the goal qubit is in |0>
                */
                mvQuantumStat[j] = alpha * Qmatrix[0] + beta * Qmatrix[1];

                /*
                * in j+ststep,the goal qubit is in |1>
                */
                mvQuantumStat[j + ststep] = alpha * Qmatrix[2] + beta * Qmatrix[3];
            }
        }
    }
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
QError  CPUQuantumGates::matReverse(COMPLEX(*mat)[4], COMPLEX(*mat_rev)[4])
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
bool CPUQuantumGates::compareCalculationUnitType(string& sCalculationUnitType)
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
QError CPUQuantumGates::NOT(size_t qn, double error_rate)
{
    /*
    *  judge errorrate of the gate
    */
    if (randGenerator() > error_rate)
    {
        LONG ststep = POW2(qn);

        COMPLEX alpha, beta;

        LONG j;
#pragma omp parallel for private(j,alpha,beta)
        for (LONG i = 0; i < (LONG)mvQuantumStat.size(); i += ststep * 2)
        {
            for (j = i; j<i + ststep; j++)
            {
                alpha = mvQuantumStat[j];
                beta = mvQuantumStat[j + ststep];

                mvQuantumStat[j] = beta;
                mvQuantumStat[j + ststep] = alpha;
            }
        }
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
QError CPUQuantumGates::NOT(size_t  qn,
    double  error_rate,
    Qnum    vControlBit,
    int     stQuantumBitNumber)
{
    if (randGenerator() > error_rate)
    {

        size_t qn = vControlBit.back();                                        /*qn is target number                   */
        sort(vControlBit.begin(), vControlBit.end());
        LONG M = (LONG)(mvQuantumStat.size() / POW2(vControlBit.size()));
        LONG x;
        LONG n = stQuantumBitNumber;
        LONG ststep = POW2(qn);
        COMPLEX alpha, beta;
        LONG index = 0;
        LONG block = 0;
        for (Qnum::iterator j = vControlBit.begin(); j != vControlBit.end(); j++)
        {
            block += (1ll << *j);
        }

        Qnum::iterator qiter;

        LONG j;
#pragma omp parallel for private(j,alpha,beta,index,x,qiter)
        for (LONG i = 0; i < M; i++)
        {
            index = 0;
            x = i;
            qiter = vControlBit.begin();
            for (j = 0; j < n; j++)
            {
                while (qiter != vControlBit.end() && *qiter == j)
                {
                    qiter++;
                    j++;
                }
                index += ((x % 2)*(1ll << j));
                x >>= 1;
            }
            index = index + block - ststep;                             /*control qubits are 1,target qubit is 0 */
            alpha = mvQuantumStat[index];
            mvQuantumStat[index] = mvQuantumStat[index + ststep];
            mvQuantumStat[index + ststep] = alpha;
        }
    }
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
QError CPUQuantumGates::toffoli(size_t stControlBit1,
    size_t stControlBit2,
    size_t stQuantumBit,
    double errorRate,
    int    stQuantumBitNumber)
{
    if (randGenerator() > errorRate)
    {
        LONG ststep0 = POW2(stControlBit1);
        LONG ststep1 = POW2(stControlBit2);
        LONG ststep2 = POW2(stQuantumBit);
        LONG temp;

        COMPLEX dtemp2(0);

        if (ststep0 > ststep1)
        {
            temp = ststep1;
            ststep1 = ststep0;
            ststep0 = temp;
        }
        if (ststep0 > ststep2)
        {
            temp = ststep2;
            ststep2 = ststep0;
            ststep0 = temp;
        }
        if (ststep1 > ststep2)
        {
            temp = ststep2;
            ststep2 = ststep1;
            ststep1 = temp;
        }                                                               /* sort                                 */

        temp = POW2(stQuantumBit);
        LONG j, k, m;
#pragma omp parallel for private(j,k,m)
        for (LONG i = ststep2; i < (LONG)mvQuantumStat.size(); i += 2 * ststep2)
        {
            for (j = i + ststep1; j < i + ststep2; j += 2 * ststep1)
            {
                for (k = j + ststep0; k < j + ststep1; k += 2 * ststep0)
                {
                    for (m = k; m < k + ststep0; m++)
                    {
                        dtemp2 = mvQuantumStat[m];
                        mvQuantumStat[m] = mvQuantumStat[m - temp];

                        mvQuantumStat[m - temp] = dtemp2;
                    }
                }
            }
        }

    }
    return qErrorNone;

}

/*****************************************************************************************************************
Name:        endGate
Description: end gate
Argin:       pQuantumProParam       quantum program param pointer
pQGate                 quantum gate
Argout:      None
return:      quantum error
*****************************************************************************************************************/
QError CPUQuantumGates::endGate(QuantumGateParam * pQuantumProParam, QuantumGates * pQGate)
{
    for (size_t i = 0; i < mvQuantumStat.size(); i++)
    {
        mvQuantumStat[i] = 0;
    }
    mvQuantumStat[0] = 1;
    return qErrorNone;
}
