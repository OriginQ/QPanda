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

Author:Xue Cheng
Date:2017-12-13
Description: Definition of Cuda function of gates
************************************************************************/
#include "GPUGatesDecl.h"
#include <vector>
#include <algorithm>
#include <cuda_device_runtime_api.h>
#include <device_launch_parameters.h>
#include <cuda_runtime.h>
using namespace std;
#define QSIZE   size_t

#define SQ2 0.707106781186548
#define PI 3.141592653589793
#define THREADDIM 1024

namespace GATEGPU
{
    //typedef quantumstate QState;

    typedef std::vector<STATE_T> vecdou;
    //typedef std::vector<probability> vecprob;
    __global__ void unitary(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, STATE_T *matr, QSIZE Block);
    __global__ void initState(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim);
    __global__ void Hadamard(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block);
    __global__ void Hadamardnew(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block);
    __global__ void Hadamarddagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block);
    __global__ void RX(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta);
    __global__ void RXdagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta);
    __global__ void RY(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta);
    __global__ void RYdagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta);
    __global__ void RZ(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta);
    __global__ void RZdagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta);
    __global__ void NOT(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block);
    __global__ void NOTdagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block);
    __global__ void CNOT(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block1, QSIZE Block2);
    __global__ void CNOTdagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block1, QSIZE Block2);
    __global__ void CR(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block1, QSIZE Block2, STATE_T costheta, STATE_T sintheta);
    __global__ void CRdagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block1, QSIZE Block2, STATE_T costheta, STATE_T sintheta);
    __global__ void iSWAP(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block1, QSIZE Block2);
    __global__ void iSWAPdagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block1, QSIZE Block2);
    __global__ void sqiSWAP(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block1, QSIZE Block2);
    __global__ void sqiSWAPdagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block1, QSIZE Block2);
    __global__ void qubitprob(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block, STATE_T *pr);
    __global__ void probsum(STATE_T * pr, STATE_T * prob);
    __global__ void qubitcollapse0(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block, STATE_T coef);
    __global__ void qubitcollapse1(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block, STATE_T coef);
    __global__ void controlHadamard(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m);
    __global__ void controlHadamarddagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m);
    __global__ void controlRX(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta);
    __global__ void controlRXdagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta);
    __global__ void controlRY(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta);
    __global__ void controlRYdagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta);
    __global__ void controlRZ(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta);
    __global__ void controlRZdagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta);
    __global__ void toffoli(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE  block0, QSIZE  block1, QSIZE block2);
    __global__ void toffolidagger(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE  block0, QSIZE  block1, QSIZE block2);
    __global__ void multiprob(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, STATE_T * pro, QSIZE * block, QSIZE m, QSIZE dec);
    __global__ void probsumnew1(STATE_T * psireal, STATE_T * psiimag, STATE_T *probtemp, size_t num1, size_t m, size_t Dim, size_t * block);

    //void Hadamard(QState& psi, size_t qn, double error_rate = 0);
    DLLAPI int devicecount();
    DLLAPI bool initstate(QState& psi, QState& psigpu, int);
    DLLAPI bool destroyState(QState& psi, QState& psigpu, size_t sQnum);
    DLLAPI bool clearState(QState& psi, QState& psigpu, size_t sQnum);
    DLLAPI bool Hadamard(QState& psi, size_t qn, double error_rate = 0);
    DLLAPI bool Hadamardnew(QState& psi, size_t qn, double error_rate = 0);
    DLLAPI bool Hadamarddagger(QState& psi, size_t qn, double error_rate = 0);
    DLLAPI bool RX(QState& psi, size_t, double, double error_rate = 0);
    DLLAPI bool RXdagger(QState& psi, size_t, double, double error_rate = 0);
    DLLAPI bool RY(QState& psi, size_t, double, double error_rate = 0);
    DLLAPI bool RYdagger(QState& psi, size_t, double, double error_rate = 0);
    DLLAPI bool RZ(QState& psi, size_t, double, double error_rate = 0);
    DLLAPI bool RZdagger(QState& psi, size_t, double, double error_rate = 0);
    DLLAPI bool NOT(QState& psi, size_t qn, double error_rate = 0);
    DLLAPI bool NOTdagger(QState& psi, size_t qn, double error_rate = 0);
    DLLAPI bool CNOT(QState& psi, size_t, size_t, double error_rate = 0);
    DLLAPI bool CNOTdagger(QState& psi, size_t, size_t, double error_rate = 0);
    DLLAPI bool CR(QState& psi, size_t, size_t, double, double error_rate = 0);
    DLLAPI bool CRdagger(QState& psi, size_t, size_t, double, double error_rate = 0);
    DLLAPI bool iSWAP(QState& psi, size_t, size_t, double error_rate = 0);
    DLLAPI bool iSWAPdagger(QState& psi, size_t, size_t, double error_rate = 0);
    DLLAPI bool sqiSWAP(QState& psi, size_t, size_t, double error_rate = 0);
    DLLAPI bool sqiSWAPdagger(QState& psi, size_t, size_t, double error_rate = 0);
    DLLAPI int qubitmeasure(QState& psi, QSIZE Block);
    DLLAPI bool controlHadamard(QState& psi, Qnum&, double error_rate = 0);
    DLLAPI bool controlHadamarddagger(QState& psi, Qnum&, double error_rate = 0);
    DLLAPI bool controlRX(QState& psi, Qnum&, double, double error_rate = 0);
    DLLAPI bool controlRXdagger(QState& psi, Qnum&, double, double error_rate = 0);
    DLLAPI bool controlRY(QState& psi, Qnum&, double, double error_rate = 0);
    DLLAPI bool controlRYdagger(QState& psi, Qnum&, double, double error_rate = 0);
    DLLAPI bool controlRZ(QState& psi, Qnum&, double, double error_rate = 0);
    DLLAPI bool controlRZdagger(QState& psi, Qnum&, double, double error_rate = 0);
    DLLAPI bool toffoli(QState& psi, size_t, size_t, size_t, double error_rate = 0);
    DLLAPI bool toffolidagger(QState& psi, size_t, size_t, size_t, double error_rate = 0);
    DLLAPI bool qbReset(QState& psi, size_t, double error_rate = 0);
    DLLAPI bool pMeasure(QState&, vecprob&, QSIZE *block, QSIZE m);
    DLLAPI bool pMeasurenew(QState&, vector<pair<size_t, double>>&, Qnum&);
	DLLAPI bool getState(QState &psi,QState &psigpu,int qnum);
    double randGenerator();
}

/***************************************************************************************
Probdis pMeasure(QState&, Qnum&);
********************************************************************************************/


__global__ void GATEGPU:: unitary(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, STATE_T *matr, QSIZE Block)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;

    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X1*matr[0] - Y1*matr[1] + X2*matr[2] - Y2*matr[3];
        psireal[corIdx] = X1*matr[4] - Y1*matr[5] + X2*matr[6] - Y2*matr[7];
        psiimag[realIdx] = X1*matr[1] + Y1*matr[0] + X2*matr[3] + Y2*matr[2];
        psiimag[corIdx] = X1*matr[5] + Y1*matr[4] + X2*matr[7] + Y2*matr[6];
    }

}//checked

__global__ void GATEGPU:: initState(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number

    if (idx < Dim / 2 && idx != 0)
    {
        psireal[idx] = 0;
        psiimag[idx] = 0;
        psireal[idx + Dim / 2] = 0;
        psiimag[idx + Dim / 2] = 0;
    }
    if (0 == idx)
    {
        psireal[0] = 1;
        psiimag[0] = 0;
        psireal[Dim / 2] = 0;
        psiimag[Dim / 2] = 0;
    }
}//checked

__global__ void GATEGPU:: Hadamardnew(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    //QSIZE BlockNum = idx / Block;
    //QSIZE BlockInt = idx% Block;
    //QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
   // QSIZE corIdx = realIdx + Block;
    QSIZE realIdx;
    QSIZE corIdx;
    STATE_T X1, X2, Y1, Y2;
     for (int i = idx; i < Dim; i += gridDim.x*blockDim.x)
    {
         realIdx = i / (Block<<1) * 2 * Block + i%Block ;
         corIdx = realIdx + Block;
          X1 = psireal[realIdx];
          X2 = psireal[corIdx];
          Y1 = psiimag[realIdx];
          Y2 = psiimag[corIdx];
         psireal[realIdx] = (X1 + X2)*SQ2;
         psireal[corIdx] = (X1 - X2)*SQ2;
         psiimag[realIdx] = (Y1 + Y2)*SQ2;
         psiimag[corIdx] = (Y1 - Y2)*SQ2;

     }
     /*
    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = (X1 + X2)*SQ2;
        psireal[corIdx] = (X1 - X2)*SQ2;
        psiimag[realIdx] = (Y1 + Y2)*SQ2;
        psiimag[corIdx] = (Y1 - Y2)*SQ2;
    }
    */
}//checked
__global__ void GATEGPU::Hadamard(STATE_T * psireal, STATE_T * psiimag, QSIZE Dim, QSIZE Block)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;

    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = (X1 + X2)*SQ2;
        psireal[corIdx] = (X1 - X2)*SQ2;
        psiimag[realIdx] = (Y1 + Y2)*SQ2;
        psiimag[corIdx] = (Y1 - Y2)*SQ2;
    }
}//checked

__global__ void GATEGPU:: Hadamarddagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;

    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = (X1 + X2)*SQ2;
        psireal[corIdx] = (X1 - X2)*SQ2;
        psiimag[realIdx] = (Y1 + Y2)*SQ2;
        psiimag[corIdx] = (Y1 - Y2)*SQ2;
    }
}//checked

__global__ void GATEGPU:: RX(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;
    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X1*costheta + Y2*sintheta;
        psireal[corIdx] = Y1*sintheta + X2*costheta;
        psiimag[realIdx] = Y1*costheta - X2*sintheta;
        psiimag[corIdx] = Y2*costheta - X1*sintheta;
    }
}//checked

__global__ void GATEGPU:: RXdagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;
    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X1*costheta - Y2*sintheta;
        psireal[corIdx] = -Y1*sintheta + X2*costheta;
        psiimag[realIdx] = Y1*costheta + X2*sintheta;
        psiimag[corIdx] = Y2*costheta + X1*sintheta;
    }
}//checked

__global__ void GATEGPU:: RY(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;
    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X1*costheta - X2*sintheta;
        psireal[corIdx] = X1*sintheta + X2*costheta;
        psiimag[realIdx] = Y1*costheta - Y2*sintheta;
        psiimag[corIdx] = Y2*costheta + Y1*sintheta;
    }
} //checked

__global__ void GATEGPU:: RYdagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;
    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X1*costheta + X2*sintheta;
        psireal[corIdx] = -X1*sintheta + X2*costheta;
        psiimag[realIdx] = Y1*costheta + Y2*sintheta;
        psiimag[corIdx] = Y2*costheta - Y1*sintheta;
    }
} //checked

__global__ void GATEGPU:: RZ(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;

    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE corIdx = BlockNum * 2 * Block + BlockInt + Block;
    if (corIdx < Dim)
    {
        STATE_T X2 = psireal[corIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[corIdx] = X2*costheta - Y2*sintheta;
        psiimag[corIdx] = X2*sintheta + Y2*costheta;
    }
}

__global__ void GATEGPU:: RZdagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;

    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE corIdx = BlockNum * 2 * Block + BlockInt + Block;
    if (corIdx < Dim)
    {
        STATE_T X2 = psireal[corIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[corIdx] = X2*costheta + Y2*sintheta;
        psiimag[corIdx] = -X2*sintheta + Y2*costheta;
    }
}

__global__ void GATEGPU:: NOT(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;
    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X2;
        psireal[corIdx] = X1;
        psiimag[realIdx] = Y2;
        psiimag[corIdx] = Y1;
    }
}

__global__ void GATEGPU:: NOTdagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;
    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X2;
        psireal[corIdx] = X1;
        psiimag[realIdx] = Y2;
        psiimag[corIdx] = Y1;
    }
}

__global__ void GATEGPU:: CNOT(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block1, QSIZE Block2)    //2^(qnum)           q9q8q7...q0 
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;
    QSIZE corIdx, realIdx;
    if (Block1 >  Block2)
    {
        corIdx = (idx / (Block1 / 2)) * 2 * Block1 + Block1 + (idx % (Block1 / 2) / Block2) * 2 * Block2 + idx%  Block2;
    }
    else
    {
        corIdx = (idx / (Block2 / 2)) * 2 * Block2 + (idx % (Block2 / 2) / Block1) * 2 * Block1 + Block1 + idx%  Block1;
    }
    realIdx = corIdx + Block2;
    if (realIdx < Dim)
    {
        STATE_T X1 = psireal[corIdx];                                   //10
        STATE_T Y1 = psiimag[corIdx];
        STATE_T X2 = psireal[realIdx];                                  //11
        STATE_T Y2 = psiimag[realIdx];
        psireal[corIdx] = X2;
        psiimag[corIdx] = Y2;
        psireal[realIdx] = X1;
        psiimag[realIdx] = Y1;
    }
}

__global__ void GATEGPU:: CNOTdagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block1, QSIZE Block2)    //2^(qnum)           q9q8q7...q0 
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;
    QSIZE corIdx, realIdx;
    if (Block1 >  Block2)
    {
        corIdx = (idx / (Block1 / 2)) * 2 * Block1 + Block1 + (idx % (Block1 / 2) / Block2) * 2 * Block2 + idx%  Block2;
    }
    else
    {
        corIdx = (idx / (Block2 / 2)) * 2 * Block2 + (idx % (Block2 / 2) / Block1) * 2 * Block1 + Block1 + idx%  Block1;
    }
    realIdx = corIdx + Block2;
    if (realIdx < Dim)
    {
        STATE_T X1 = psireal[corIdx];                                   //10
        STATE_T Y1 = psiimag[corIdx];
        STATE_T X2 = psireal[realIdx];                                  //11
        STATE_T Y2 = psiimag[realIdx];
        psireal[corIdx] = X2;
        psiimag[corIdx] = Y2;
        psireal[realIdx] = X1;
        psiimag[realIdx] = Y1;
    }
}

__global__ void GATEGPU:: CR(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block1, QSIZE Block2, STATE_T costheta, STATE_T sintheta)    //2^(qnum)           q9q8q7...q0 
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;
    QSIZE realIdx;
    if (Block1 >  Block2)
    {
        realIdx = (idx / (Block1 / 2)) * 2 * Block1 + Block1 + (idx % (Block1 / 2) / Block2) * 2 * Block2 + Block2 + idx%  Block2;
    }
    else
    {
        realIdx = (idx / (Block2 / 2)) * 2 * Block2 + Block2 + (idx % (Block2 / 2) / Block1) * 2 * Block1 + Block1 + idx%  Block1;
    }
    if (realIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T Y1 = psiimag[realIdx];
        psireal[realIdx] = X1*costheta - Y1*sintheta;
        psiimag[realIdx] = X1*sintheta + Y1*costheta;
    }
}

__global__ void GATEGPU:: CRdagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block1, QSIZE Block2, STATE_T costheta, STATE_T sintheta)    //2^(qnum)           q9q8q7...q0 
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;
    QSIZE realIdx;
    if (Block1 >  Block2)
    {
        realIdx = (idx / (Block1 / 2)) * 2 * Block1 + Block1 + (idx % (Block1 / 2) / Block2) * 2 * Block2 + Block2 + idx%  Block2;
    }
    else
    {
        realIdx = (idx / (Block2 / 2)) * 2 * Block2 + Block2 + (idx % (Block2 / 2) / Block1) * 2 * Block1 + Block1 + idx%  Block1;
    }
    if (realIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T Y1 = psiimag[realIdx];
        psireal[realIdx] = X1*costheta + Y1*sintheta;
        psiimag[realIdx] = -X1*sintheta + Y1*costheta;
    }
}

__global__ void GATEGPU:: iSWAP(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block1, QSIZE Block2)    //2^(qnum)           q9q8q7...q0 
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;
    QSIZE corIdx, realIdx, temp;
    if (Block1 <  Block2)
    {
        temp = Block1;
        Block1 = Block2;
        Block2 = temp;
    }
    corIdx = (idx / (Block1 / 2)) * 2 * Block1 + Block1 + (idx % (Block1 / 2) / Block2) * 2 * Block2 + idx%  Block2;
    realIdx = corIdx - Block1 + Block2;
    if (realIdx < Dim)
    {
        STATE_T X1 = psireal[corIdx];                                   //10
        STATE_T Y1 = psiimag[corIdx];
        STATE_T X2 = psireal[realIdx];                                  //11
        STATE_T Y2 = psiimag[realIdx];
        psireal[corIdx] = Y2;
        psiimag[corIdx] = -X2;
        psireal[realIdx] = Y1;
        psiimag[realIdx] = -X1;
    }
}

__global__ void GATEGPU:: iSWAPdagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block1, QSIZE Block2)    //2^(qnum)           q9q8q7...q0 
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;
    QSIZE corIdx, realIdx, temp;
    if (Block1 <  Block2)
    {
        temp = Block1;
        Block1 = Block2;
        Block2 = temp;
    }
    corIdx = (idx / (Block1 / 2)) * 2 * Block1 + Block1 + (idx % (Block1 / 2) / Block2) * 2 * Block2 + idx%  Block2;
    realIdx = corIdx - Block1 + Block2;
    if (realIdx < Dim)
    {
        STATE_T X1 = psireal[corIdx];                                   //10
        STATE_T Y1 = psiimag[corIdx];
        STATE_T X2 = psireal[realIdx];                                  //11
        STATE_T Y2 = psiimag[realIdx];
        psireal[corIdx] = -Y2;
        psiimag[corIdx] = X2;
        psireal[realIdx] = -Y1;
        psiimag[realIdx] = X1;
    }
}

__global__ void GATEGPU:: sqiSWAP(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block1, QSIZE Block2)    //2^(qnum)           q9q8q7...q0 
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;
    QSIZE corIdx, realIdx, temp;
    if (Block1 <  Block2)
    {
        temp = Block1;
        Block1 = Block2;
        Block2 = temp;
    }
    corIdx = (idx / (Block1 / 2)) * 2 * Block1 + Block1 + (idx % (Block1 / 2) / Block2) * 2 * Block2 + idx%  Block2;
    realIdx = corIdx - Block1 + Block2;
    if (realIdx < Dim)
    {
        STATE_T X1 = psireal[corIdx];                                   //10
        STATE_T Y1 = psiimag[corIdx];
        STATE_T X2 = psireal[realIdx];                                  //11
        STATE_T Y2 = psiimag[realIdx];
        psireal[corIdx] = (X1 + Y2)*SQ2;
        psiimag[corIdx] = (Y1 - X2)*SQ2;
        psireal[realIdx] = (X2 + Y1)*SQ2;
        psiimag[realIdx] = (Y2 - X1)*SQ2;
    }
}

__global__ void GATEGPU:: sqiSWAPdagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block1, QSIZE Block2)    //2^(qnum)           q9q8q7...q0 
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;
    QSIZE corIdx, realIdx, temp;
    if (Block1 <  Block2)
    {
        temp = Block1;
        Block1 = Block2;
        Block2 = temp;
    }
    corIdx = (idx / (Block1 / 2)) * 2 * Block1 + Block1 + (idx % (Block1 / 2) / Block2) * 2 * Block2 + idx%  Block2;
    realIdx = corIdx - Block1 + Block2;
    if (realIdx < Dim)
    {
        STATE_T X1 = psireal[corIdx];                                   //10
        STATE_T Y1 = psiimag[corIdx];
        STATE_T X2 = psireal[realIdx];                                  //11
        STATE_T Y2 = psiimag[realIdx];
        psireal[corIdx] = (X1 - Y2)*SQ2;
        psiimag[corIdx] = (Y1 + X2)*SQ2;
        psireal[realIdx] = (X2 - Y1)*SQ2;
        psiimag[realIdx] = (Y2 + X1)*SQ2;
    }
}

__global__ void GATEGPU:: qubitprob(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block, STATE_T *pr)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE bid = blockIdx.x, tid = threadIdx.x;
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;
    extern __shared__ STATE_T  dprob[];
    dprob[tid] = 0;
    int i;
    /*
    for (i = bid * blockDim.x + tid; i < Dim / 2; i += gridDim.x * THREADDIM)
    {
        //        QSIZE idx = bid*(psigpu.qnum-1))/THREADDIM.x + tid;
        //        QSIZE corIdx = idx / Block * 2 * Block + idx%Block;
        dprob[tid] += psireal[realIdx] * psireal[realIdx] + psiimag[realIdx] * psiimag[realIdx];
    }
    */
    //dprob[tid] = psireal[realIdx] * psireal[realIdx] + psiimag[realIdx] * psiimag[realIdx];

    //同步 保证每个 thread 都已经把结果写到 shared[tid] 里面
    if (corIdx < Dim)
    {
        dprob[tid] = psireal[realIdx] * psireal[realIdx] + psiimag[realIdx] * psiimag[realIdx];   //可省略?
        __syncthreads();//树状加法
        int offset = 1, mask = 1;
        while (offset < THREADDIM)
        {
            if ((tid & mask) == 0)
            {
                dprob[tid] += dprob[tid + offset];
            }
            offset += offset;
            mask = offset + mask;
            __syncthreads();
        }
        //计算时间,记录结果,只在 thread 0（即 threadIdx.x =
        //dprob[0]求和即得到最后的概率
        if (tid == 0)
        {
            pr[bid] = dprob[0];
        }
    }
}//checked
__global__ void GATEGPU::probsumnew1(STATE_T * psireal, STATE_T * psiimag, STATE_T *probtemp, size_t num1, size_t m, size_t Dim, size_t * block)
{
    size_t idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    size_t bid = blockIdx.x, tid = threadIdx.x;
    size_t index1, index = 0, index2, k, s;
    double temp = 0;
    index1 = num1 + idx;                              //index1表示idx对应的不加权的态序号
    if (index1 < (1u << m))
    {
        for (size_t j = 0; j < m; j++)
        {
            index += block[j] * ((index1 >> j) % 2);
        }//index 表示idx对应的态的序号
        for (size_t i = 0; i < Dim / (1u << m); i++)
        {
            index2 = i;
            for (size_t j = 0; j < m; j++)
            {
                s = index2 / block[j];
                k = index2 % block[j];
                index2 = s * 2 * block[j] + k;
            }
            index2 += index;
            temp += psireal[index2] * psireal[index2] + psiimag[index2] * psiimag[index2];
        }
        probtemp[idx] = temp;
    }
}
__global__ void GATEGPU:: probsum(STATE_T * pr, STATE_T * prob)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    if (0 == idx)
    {
        STATE_T dprob = 0;
        for (int i = 0; i < gridDim.x; i++)
        {
            dprob += pr[i];
        }
        *prob = dprob;
    }
}//checked and can be optimized

__global__ void GATEGPU:: qubitcollapse0(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block, STATE_T coef)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;
    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T Y1 = psiimag[realIdx];
        psireal[realIdx] = X1*coef;
        psireal[corIdx] = 0;
        psiimag[realIdx] = Y1*coef;
        psiimag[corIdx] = 0;
    }
}//checked

__global__ void GATEGPU:: qubitcollapse1(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block, STATE_T coef)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;
    if (corIdx < Dim)
    {
        STATE_T X2 = psireal[corIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = 0;
        psireal[corIdx] = X2*coef;
        psiimag[realIdx] = 0;
        psiimag[corIdx] = Y2*coef;
    }
}//checked

__global__ void GATEGPU:: controlHadamard(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number

                                                                      //QSIZE BlockNum = idx / Block;
                                                                      //QSIZE BlockInt = idx% Block;    
    QSIZE i, j, k;
    if (idx < Dim / (1 << m))
    {
        QSIZE index = idx;
        for (i = 0; i < m; i++)
        {
            j = index / block1[i];
            k = index % block1[i];
            index = j * 2 * block1[i] + block1[i] + k;

        }
        QSIZE corIdx = index;                                   //1111
        QSIZE realIdx = corIdx - block2;                    //1110
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = (X1 + X2)*SQ2;
        psireal[corIdx] = (X1 - X2)*SQ2;
        psiimag[realIdx] = (Y1 + Y2)*SQ2;
        psiimag[corIdx] = (Y1 - Y2)*SQ2;
    }
}//checked

__global__ void GATEGPU:: controlHadamarddagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number

                                                                      //QSIZE BlockNum = idx / Block;
                                                                      //QSIZE BlockInt = idx% Block;    
    QSIZE i, j, k;
    if (idx < Dim / (1 << m))
    {
        QSIZE index = idx;
        for (i = 0; i < m; i++)
        {
            j = index / block1[i];
            k = index % block1[i];
            index = j * 2 * block1[i] + block1[i] + k;

        }
        QSIZE corIdx = index;                                   //1111
        QSIZE realIdx = corIdx - block2;                    //1110
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = (X1 + X2)*SQ2;
        psireal[corIdx] = (X1 - X2)*SQ2;
        psiimag[realIdx] = (Y1 + Y2)*SQ2;
        psiimag[corIdx] = (Y1 - Y2)*SQ2;
    }
}//checked

__global__ void GATEGPU:: controlRX(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number

                                                                      //QSIZE BlockNum = idx / Block;
                                                                      //QSIZE BlockInt = idx% Block;    
    QSIZE i, j, k;
    if (idx < Dim / (1 << m))
    {
        QSIZE index = idx;
        for (i = 0; i < m; i++)
        {
            j = index / block1[i];
            k = index % block1[i];
            index = j * 2 * block1[i] + block1[i] + k;

        }
        QSIZE corIdx = index;                                   //1111
        QSIZE realIdx = corIdx - block2;                    //1110
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X1*costheta + Y2*sintheta;
        psireal[corIdx] = Y1*sintheta + X2*costheta;
        psiimag[realIdx] = Y1*costheta - X2*sintheta;
        psiimag[corIdx] = Y2*costheta - X1*sintheta;
    }
}       //checked

__global__ void GATEGPU:: controlRXdagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number

                                                                      //QSIZE BlockNum = idx / Block;
                                                                      //QSIZE BlockInt = idx% Block;    
    QSIZE i, j, k;
    if (idx < Dim / (1 << m))
    {
        QSIZE index = idx;
        for (i = 0; i < m; i++)
        {
            j = index / block1[i];
            k = index % block1[i];
            index = j * 2 * block1[i] + block1[i] + k;

        }
        QSIZE corIdx = index;                                   //1111
        QSIZE realIdx = corIdx - block2;                    //1110
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X1*costheta - Y2*sintheta;
        psireal[corIdx] = -Y1*sintheta + X2*costheta;
        psiimag[realIdx] = Y1*costheta + X2*sintheta;
        psiimag[corIdx] = Y2*costheta + X1*sintheta;
    }
}       //checked

__global__ void GATEGPU:: controlRY(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number

                                                                      //QSIZE BlockNum = idx / Block;
                                                                      //QSIZE BlockInt = idx% Block;    
    QSIZE i, j, k;
    if (idx < Dim / (1 << m))
    {
        QSIZE index = idx;
        for (i = 0; i < m; i++)
        {
            j = index / block1[i];
            k = index % block1[i];
            index = j * 2 * block1[i] + block1[i] + k;

        }
        QSIZE corIdx = index;                                   //1111
        QSIZE realIdx = corIdx - block2;                    //1110
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X1*costheta - X2*sintheta;
        psireal[corIdx] = X1*sintheta + X2*costheta;
        psiimag[realIdx] = Y1*costheta - Y2*sintheta;
        psiimag[corIdx] = Y2*costheta + Y1*sintheta;
    }
}       //checked

__global__ void GATEGPU:: controlRYdagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number

                                                                      //QSIZE BlockNum = idx / Block;
                                                                      //QSIZE BlockInt = idx% Block;    
    QSIZE i, j, k;
    if (idx < Dim / (1 << m))
    {
        QSIZE index = idx;
        for (i = 0; i < m; i++)
        {
            j = index / block1[i];
            k = index % block1[i];
            index = j * 2 * block1[i] + block1[i] + k;

        }
        QSIZE corIdx = index;                                   //1111
        QSIZE realIdx = corIdx - block2;                    //1110
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X1*costheta + X2*sintheta;
        psireal[corIdx] = -X1*sintheta + X2*costheta;
        psiimag[realIdx] = Y1*costheta + Y2*sintheta;
        psiimag[corIdx] = Y2*costheta - Y1*sintheta;
    }
}       //checked

__global__ void GATEGPU:: controlRZ(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE i, j, k;
    if (idx < Dim / (1 << m))
    {
        QSIZE index = idx;
        for (i = 0; i < m; i++)
        {
            j = index / block1[i];
            k = index % block1[i];
            index = j * 2 * block1[i] + block1[i] + k;

        }
        QSIZE corIdx = index;                                   //1111        
        STATE_T X2 = psireal[corIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[corIdx] = X2*costheta - Y2*sintheta;
        psiimag[corIdx] = X2*sintheta + Y2*costheta;
    }
}       //checked

__global__ void GATEGPU:: controlRZdagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE * block1, QSIZE  block2, QSIZE m, STATE_T costheta, STATE_T sintheta)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE i, j, k;
    if (idx < Dim / (1 << m))
    {
        QSIZE index = idx;
        for (i = 0; i < m; i++)
        {
            j = index / block1[i];
            k = index % block1[i];
            index = j * 2 * block1[i] + block1[i] + k;

        }
        QSIZE corIdx = index;                                   //1111        
        STATE_T X2 = psireal[corIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[corIdx] = X2*costheta + Y2*sintheta;
        psiimag[corIdx] = -X2*sintheta + Y2*costheta;
    }
}       //checked

__global__ void GATEGPU:: toffoli(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE  block0, QSIZE  block1, QSIZE block2)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE block = block2, temp;
    if (block0 > block1)
    {
        temp = block1;
        block1 = block0;
        block0 = temp;
    }
    if (block0 > block2)
    {
        temp = block2;
        block2 = block0;
        block0 = temp;
    }
    if (block1 > block2)
    {
        temp = block2;
        block2 = block1;
        block1 = temp;
    }                           //small to large sequence
    if (idx < Dim / (1 << 3))
    {
        QSIZE corIdx = idx / block0 * 2 * block0 + block0 + idx%block0, realIdx;
        corIdx = corIdx / block1 * 2 * block1 + block1 + corIdx%block1;
        corIdx = corIdx / block2 * 2 * block2 + block2 + corIdx%block2;
        realIdx = corIdx - block;
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X2;
        psireal[corIdx] = X1;
        psiimag[realIdx] = Y2;
        psiimag[corIdx] = Y1;
    }
}     //checked

__global__ void GATEGPU:: toffolidagger(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE  block0, QSIZE  block1, QSIZE block2)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE block = block2, temp;
    if (block0 > block1)
    {
        temp = block1;
        block1 = block0;
        block0 = temp;
    }
    if (block0 > block2)
    {
        temp = block2;
        block2 = block0;
        block0 = temp;
    }
    if (block1 > block2)
    {
        temp = block2;
        block2 = block1;
        block1 = temp;
    }                           //small to large sequence
    if (idx < Dim / (1 << 3))
    {
        QSIZE corIdx = idx / block0 * 2 * block0 + block0 + idx%block0, realIdx;
        corIdx = corIdx / block1 * 2 * block1 + block1 + corIdx%block1;
        corIdx = corIdx / block2 * 2 * block2 + block2 + corIdx%block2;
        realIdx = corIdx - block;
        STATE_T X1 = psireal[realIdx];
        STATE_T X2 = psireal[corIdx];
        STATE_T Y1 = psiimag[realIdx];
        STATE_T Y2 = psiimag[corIdx];
        psireal[realIdx] = X2;
        psireal[corIdx] = X1;
        psiimag[realIdx] = Y2;
        psiimag[corIdx] = Y1;
    }
}     //checked
/*
__global__ void GATEGPU:: qbReset(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, QSIZE Block)      //reset to |0>, this operator is NOT UNITARY
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE BlockNum = idx / Block;
    QSIZE BlockInt = idx% Block;
    QSIZE realIdx = BlockNum * 2 * Block + BlockInt;
    QSIZE corIdx = realIdx + Block;

    if (corIdx < Dim)
    {
        STATE_T X1 = psireal[realIdx];
        STATE_T Y1 = psiimag[realIdx];
        psireal[realIdx] = X1;
        psireal[corIdx] = 0;
        psiimag[realIdx] = Y1;
        psiimag[corIdx] = 0;
    }
}
*/


/**************************************************************************************
psireal:
psiimag:
pro:      save probability
block:    qubit number
m:        target qubit number
dec:      target qubit state





****************************************************************************************/
__global__ void GATEGPU:: multiprob(STATE_T * psireal, STATE_T * psiimag,QSIZE Dim, STATE_T * pro, QSIZE * block, QSIZE m, QSIZE dec)
{
    QSIZE idx = blockDim.x*blockIdx.x + threadIdx.x;           //thread number
    QSIZE bid = blockIdx.x, tid = threadIdx.x;
    //QSIZE BlockNum = idx / Block;
    //QSIZE BlockInt = idx% Block;    
    extern __shared__ STATE_T dprob[];
    dprob[tid] = 0;
    QSIZE i, j, k;
    if (idx < Dim / (1 << m))
    {
        QSIZE index = idx;
        for (i = 0; i < m; i++)
        {
            j = index / block[i];
            k = index % block[i];
            index = j * 2 * block[i] + k;
        }                                                              //index 目标比特全为0
        QSIZE realIdx = index + dec;                                   //需要加的态的概率
        dprob[tid] = psireal[realIdx] * psireal[realIdx] + psiimag[realIdx] * psiimag[realIdx];
        __syncthreads();//树状加法
        int offset = 1, mask = 1;
        while (offset < THREADDIM)
        {
            if ((tid & mask) == 0)
            {
                dprob[tid] += dprob[tid + offset];
            }
            offset += offset;
            mask = offset + mask;
            __syncthreads();
        }
        //计算时间,记录结果,只在 thread 0（即 threadIdx.x =
        //dprob[0]求和即得到最后的概率
        if (tid == 0)
        {
            pro[bid] = dprob[0];                       //再计算pro的和就得到最后的概率
        }
    }
}


/***********************************************************************
Copyright:
Author:Xue Cheng
Date:2017-12-13
Description: Definition of Encapsulation of GPU gates
************************************************************************/

#define SET_BLOCKDIM  BLOCKDIM = (1 << (psigpu.qnum - 1)) / THREADDIM;

int GATEGPU:: devicecount()
{
    int count;
    cudaGetDeviceCount(&count);
    return count;
}


bool getSynchronizeResult(cudaError_t cudaStatue, char * pcGate)
{

    if (cudaSuccess != cudaStatue)
    {
        cout << "err " << pcGate << " = " << cudaGetErrorString(cudaStatue) << endl;
        return false;
    }
    return true;
}

#define GET_SYN_RES(x)      cudaError_t cudaStatue = cudaDeviceSynchronize();\
                            return getSynchronizeResult(cudaStatue,(x));

bool GATEGPU::destroyState(QState& psi, QState& psigpu,size_t stQnum)
{

    if ((nullptr == psi.real) ||
        (nullptr == psi.imag) ||
        (nullptr == psigpu.real) ||
        (nullptr == psigpu.imag))
    {
        return false;
    }

    if (stQnum<30)
    {
        cudaError_t cudaStates = cudaFree(psigpu.real);
        if (cudaSuccess != cudaStates)
        {
            cout << "psigpu.real free error" << endl;
            return false;
        }
        cudaStates =cudaFree(psigpu.imag);
        if (cudaSuccess != cudaStates)
        {
            cout << "psigpu.imag free error" << endl;
            return false;
        }
        free(psi.real);
        free(psi.imag);
    }
    else
    {
        cudaFreeHost(psigpu.real);
        cudaFreeHost(psigpu.imag);
    }


    return true;
}

bool GATEGPU::clearState(QState& psi, QState& psigpu,size_t stQnum)
{

    if ((nullptr == psi.real) ||
        (nullptr == psi.imag) ||
        (nullptr == psigpu.real) ||
        (nullptr == psigpu.imag))
    {
        return false;
    }

    if (stQnum<30)
    {
        QSIZE qsDim = (1ll << stQnum);
        memset(psi.real,0, qsDim *sizeof(STATE_T));
        memset(psi.imag, 0, qsDim * sizeof(STATE_T));
        psi.real[0] = 1;

        //cudaFree(psigpu.real);
        //cudaFree(psigpu.imag);
        cudaError_t cudaStatue = cudaMemcpy(psigpu.real, psi.real, sizeof(STATE_T)*qsDim, cudaMemcpyHostToDevice);
        if (cudaSuccess != cudaStatue)
        {
            cout << "psigpu real memcpy error" << endl;
        }
        cudaStatue = cudaMemcpy(psigpu.imag, psi.imag, sizeof(STATE_T)*qsDim, cudaMemcpyHostToDevice);
        if (cudaSuccess != cudaStatue)
        {
            cout << "psigpu imag memcpy error" << endl;
        }
    }
    else
    {
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        initState << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag, 1 << (psigpu.qnum));
    }

    return true;
}

bool GATEGPU::initstate(QState& psi, QState& psigpu, int qnum)
{
    //QState psigpu;
    if (qnum >= 30)
    {
        cudaError_t cudaStatus = cudaHostAlloc(&psi.real, sizeof(double)*(1ll << qnum), cudaHostAllocMapped);
        if (cudaStatus != cudaSuccess)
        {
            printf("host alloc fail!\n");
            return false;
        }
        cudaError_t cudaStatus1 = cudaHostAlloc(&psi.imag, sizeof(double)*(1ll << qnum), cudaHostAllocMapped);
        if (cudaStatus1 != cudaSuccess)
        {
            printf("host alloc fail!\n");
            return false;
        }
        cudaHostGetDevicePointer(&psigpu.real, psi.real, 0);
        cudaHostGetDevicePointer(&psigpu.imag, psi.imag, 0);
        psi.qnum = qnum;
        psigpu.qnum = qnum;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
            initState << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag, 1 << (psigpu.qnum));
        //std::cout << "err = " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    }
    else 
    {
        QSIZE Dim = 1 << qnum;
        cudaError_t cudaStatus;
        psi.real = (STATE_T*)malloc(Dim * sizeof(STATE_T));
        if (nullptr == psi.real)
        {
            printf("psi.real alloc memory error\n");
            return false;
        }
        psi.imag = (STATE_T*)malloc(Dim * sizeof(STATE_T));
        if (nullptr == psi.real)
        {
            printf("psi.imag alloc memory error\n");
            free(psi.imag);
            return false;
        }
        cudaStatus = cudaMalloc((void**)&psigpu.real, sizeof(STATE_T)*Dim);
        if (cudaSuccess != cudaStatus)
        {
            printf("psigpu.real alloc gpu memoery error!\n");
            free(psi.real);
            free(psi.imag);
            return false;
        }
        cudaStatus = cudaMalloc((void**)&psigpu.imag, sizeof(STATE_T)*Dim);
        if (cudaSuccess != cudaStatus)
        {
            printf("psigpu.imag alloc gpu memoery error!\n");
            free(psi.real);
            free(psi.imag);
            cudaFree(psigpu.real);
            return false;
        }
        
        memset(psi.real,0,Dim * sizeof(STATE_T));
        memset(psi.imag, 0, Dim * sizeof(STATE_T));
        psi.real[0] = 1;
        
        cudaStatus = cudaMemcpy(psigpu.real, psi.real, sizeof(STATE_T)*Dim, cudaMemcpyHostToDevice);
        if (cudaSuccess != cudaStatus)
        {
            printf("psigpu.imag alloc gpu memoery error!\n");
            free(psi.real);
            free(psi.imag);
            cudaFree(psigpu.real);
            cudaFree(psigpu.imag);
            return false;
        }

        cudaStatus = cudaMemcpy(psigpu.imag, psi.imag, sizeof(STATE_T)*Dim, cudaMemcpyHostToDevice);
        if (cudaSuccess != cudaStatus)
        {
            printf("psigpu.imag alloc gpu memoery error!\n");
            free(psi.real);
            free(psi.imag);
            cudaFree(psigpu.real);
            cudaFree(psigpu.imag);
            return false;
        }
        psigpu.qnum = qnum;
        psi.qnum = qnum;
    }

    return true;
}



bool GATEGPU:: Hadamard(QState& psigpu, size_t qn, double error_rate)

{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        //int BLOCKDIM = (1 << (psigpu.qnum - 1)) / THREADDIM;
        QSIZE BLOCKDIM = (1 << (psigpu.qnum - 1)) / THREADDIM;
        Hadamard << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag, 1 << (psigpu.qnum), 1 << qn);
    }
    //GET_SYN_RES("Hadamard");
    cudaError_t cudaStatue = cudaDeviceSynchronize(); 
    return getSynchronizeResult(cudaStatue, "Hadamard");
}
bool GATEGPU::Hadamardnew(QState& psigpu, size_t qn, double error_rate)

{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        //int BLOCKDIM = (1 << (psigpu.qnum - 1)) / THREADDIM;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        Hadamardnew << < 4096, THREADDIM >> > (psigpu.real, psigpu.imag, 1 << (psigpu.qnum), 1 << qn);
    }
    //std::cout << "err = " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    GET_SYN_RES("Hadamardnew")
}
bool GATEGPU:: Hadamarddagger(QState& psigpu, size_t qn, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        Hadamarddagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn);
        std::cout << "err Hadamarddagger= " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    }
   // std::cout << "err = " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    GET_SYN_RES("Hadamarddagger")

}

bool GATEGPU:: RX(QState& psigpu, size_t qn, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        double costheta = cos(theta / 2), sintheta = sin(theta / 2);
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        RX << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn, costheta, sintheta);
    }

    GET_SYN_RES("RX")
}
bool GATEGPU:: RXdagger(QState& psigpu, size_t qn, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        double costheta = cos(theta / 2), sintheta = sin(theta / 2);
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        RXdagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn, costheta, sintheta);
        //cudaDeviceSynchronize();
    }
    GET_SYN_RES("RXdagger")
}
bool GATEGPU::RY(QState& psigpu, size_t qn, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        double costheta = cos(theta / 2), sintheta = sin(theta / 2);
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        RY << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag, 1 << (psigpu.qnum), 1 << qn, costheta, sintheta);
        //cudaDeviceSynchronize();
        //std::cout << "errry = " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    }
    GET_SYN_RES("RY")
}
bool GATEGPU:: RYdagger(QState& psigpu, size_t qn, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        double costheta = cos(theta / 2), sintheta = sin(theta / 2);
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        RYdagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn, costheta, sintheta);
        //cudaDeviceSynchronize();
    }
    GET_SYN_RES("RYdagger")
}
bool GATEGPU:: RZ(QState& psigpu, size_t qn, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        double costheta = cos(theta), sintheta = sin(theta);
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        RZ << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn, costheta, sintheta);
        //std::cout << "err rz= " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
        //cudaDeviceSynchronize();
    }
    GET_SYN_RES("RZ")
}

bool GATEGPU:: RZdagger(QState& psigpu, size_t qn, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        double costheta = cos(theta), sintheta = sin(theta);
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        RZdagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn, costheta, sintheta);
        //cudaDeviceSynchronize();
    }
    GET_SYN_RES("RZdagger")
}
bool GATEGPU:: NOT(QState& psigpu, size_t qn, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        NOT << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn);
        //std::cout << "err NOT= " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    }
    GET_SYN_RES("NOT")
}
bool GATEGPU:: NOTdagger(QState& psigpu, size_t qn, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        NOTdagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn);
        //cudaDeviceSynchronize();
    }
    GET_SYN_RES("NOTdagger")
}

bool GATEGPU:: CNOT(QState& psigpu, size_t qn0, size_t qn1, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        CNOT << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn0, 1 << qn1);
        //std::cout << "err CNOT= " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    }
    GET_SYN_RES("CNOT")
}
bool GATEGPU::CNOTdagger(QState& psigpu, size_t qn0, size_t qn1, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        CNOTdagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag, 1 << (psigpu.qnum), 1 << qn0, 1 << qn1);
    }
    GET_SYN_RES("CNOTdagger")
}
bool GATEGPU:: CR(QState& psigpu, size_t qn0, size_t qn1, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        double costheta = cos(theta), sintheta = sin(theta);
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        CR << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn0, 1 << qn1, costheta, sintheta);
        //std::cout << "err CR= " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    }
    GET_SYN_RES("CR")
}
bool GATEGPU:: CRdagger(QState& psigpu, size_t qn0, size_t qn1, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        double costheta = cos(theta), sintheta = sin(theta);
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        CRdagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn0, 1 << qn1, costheta, sintheta);
    }
    GET_SYN_RES("CRdagger")
}
bool GATEGPU:: iSWAP(QState& psigpu, size_t qn0, size_t qn1, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        iSWAP << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn0, 1 << qn1);
        //std::cout << "err iSWAP= " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    }
    GET_SYN_RES("iSWAP")
}
bool GATEGPU:: iSWAPdagger(QState& psigpu, size_t qn0, size_t qn1, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        iSWAPdagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn0, 1 << qn1);
    }
    GET_SYN_RES("iSWAPdagger")
}
bool GATEGPU:: sqiSWAP(QState& psigpu, size_t qn0, size_t qn1, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        sqiSWAP << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn0, 1 << qn1);
        //std::cout << "err sqiSWAP= " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    }
    GET_SYN_RES("sqiSWAP")
}
bool GATEGPU:: sqiSWAPdagger(QState& psigpu, size_t qn0, size_t qn1, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        sqiSWAPdagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn0, 1 << qn1);
    }
    GET_SYN_RES("sqiSWAP")
}
bool GATEGPU:: controlHadamard(QState& psigpu, Qnum& qnum, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        QSIZE m = qnum.size();
        QSIZE target = qnum.back();
        sort(qnum.begin(), qnum.end());
        QSIZE *block, *blockgpu;
        cudaHostAlloc((void **)&block, sizeof(QSIZE)*m, cudaHostAllocMapped);
        cudaHostGetDevicePointer(&blockgpu, block, 0);
        for (QSIZE i = 0; i < m; i++)
        {
            block[i] = 1 << qnum[i];
        }
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        controlHadamard << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), blockgpu, 1 << target, m);
        cudaFreeHost(block);
        //std::cout << "err = " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    }
    GET_SYN_RES("controlHadamard")
}
bool GATEGPU:: controlHadamarddagger(QState& psigpu, Qnum& qnum, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        QSIZE m = qnum.size();
        QSIZE target = qnum.back();
        sort(qnum.begin(), qnum.end());
        QSIZE *block, *blockgpu;
        cudaHostAlloc((void **)&block, sizeof(QSIZE)*m, cudaHostAllocMapped);
        cudaHostGetDevicePointer(&blockgpu, block, 0);
        for (QSIZE i = 0; i < m; i++)
        {
            block[i] = 1 << qnum[i];
        }
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        controlHadamarddagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), blockgpu, 1 << target, m);
        cudaFreeHost(block);
    }
    GET_SYN_RES("controlHadamarddagger")
}
bool GATEGPU:: controlRX(QState& psigpu, Qnum& qnum, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        double costheta = cos(theta / 2), sintheta = sin(theta / 2);
        QSIZE m = qnum.size();
        QSIZE target = qnum.back();
        sort(qnum.begin(), qnum.end());
        QSIZE *block, *blockgpu;
        cudaHostAlloc((void **)&block, sizeof(QSIZE)*m, cudaHostAllocMapped);
        cudaHostGetDevicePointer(&blockgpu, block, 0);
        for (QSIZE i = 0; i < m; i++)
        {
            block[i] = 1 << qnum[i];
        }
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        controlRX << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), blockgpu, 1 << target, m, costheta, sintheta);
        cudaFreeHost(block);

    }
    GET_SYN_RES("controlRX")
}
bool GATEGPU:: controlRXdagger(QState& psigpu, Qnum& qnum, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        double costheta = cos(theta / 2), sintheta = sin(theta / 2);
        QSIZE m = qnum.size();
        QSIZE target = qnum.back();
        sort(qnum.begin(), qnum.end());
        QSIZE *block, *blockgpu;
        cudaHostAlloc((void **)&block, sizeof(QSIZE)*m, cudaHostAllocMapped);
        cudaHostGetDevicePointer(&blockgpu, block, 0);
        for (QSIZE i = 0; i < m; i++)
        {
            block[i] = 1 << qnum[i];
        }
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        controlRXdagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), blockgpu, 1 << target, m, costheta, sintheta);
        cudaFreeHost(block);
    }
    GET_SYN_RES("controlRX")
}
bool GATEGPU:: controlRY(QState& psigpu, Qnum& qnum, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        double costheta = cos(theta / 2), sintheta = sin(theta / 2);
        QSIZE m = qnum.size();
        QSIZE target = qnum.back();
        sort(qnum.begin(), qnum.end());
        QSIZE *block, *blockgpu;
        cudaHostAlloc((void **)&block, sizeof(QSIZE)*m, cudaHostAllocMapped);
        cudaHostGetDevicePointer(&blockgpu, block, 0);
        for (QSIZE i = 0; i < m; i++)
        {
            block[i] = 1 << qnum[i];
        }
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        controlRY << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), blockgpu, 1 << target, m, costheta, sintheta);
        cudaFreeHost(block);

    }
    GET_SYN_RES("controlRY")
}
bool GATEGPU:: controlRYdagger(QState& psigpu, Qnum& qnum, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        double costheta = cos(theta / 2), sintheta = sin(theta / 2);
        QSIZE m = qnum.size();
        QSIZE target = qnum.back();
        sort(qnum.begin(), qnum.end());
        QSIZE *block, *blockgpu;
        cudaHostAlloc((void **)&block, sizeof(QSIZE)*m, cudaHostAllocMapped);
        cudaHostGetDevicePointer(&blockgpu, block, 0);
        for (QSIZE i = 0; i < m; i++)
        {
            block[i] = 1 << qnum[i];
        }
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        controlRYdagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), blockgpu, 1 << target, m, costheta, sintheta);
        cudaFreeHost(block);
    }
    GET_SYN_RES("controlRYdagger")
}
bool GATEGPU:: controlRZ(QState& psigpu, Qnum& qnum, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        double costheta = cos(theta), sintheta = sin(theta);
        QSIZE m = qnum.size();
        QSIZE target = qnum.back();
        sort(qnum.begin(), qnum.end());
        QSIZE *block, *blockgpu;
        cudaHostAlloc((void **)&block, sizeof(QSIZE)*m, cudaHostAllocMapped);
        cudaHostGetDevicePointer(&blockgpu, block, 0);
        for (QSIZE i = 0; i < m; i++)
        {
            block[i] = 1 << qnum[i];
        }
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        controlRZ << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), blockgpu, 1 << target, m, costheta, sintheta);
        cudaFreeHost(block);

    }
    GET_SYN_RES("controlRZ")
}
bool GATEGPU:: controlRZdagger(QState& psigpu, Qnum& qnum, double theta, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        double costheta = cos(theta), sintheta = sin(theta);
        QSIZE m = qnum.size();
        QSIZE target = qnum.back();
        sort(qnum.begin(), qnum.end());
        QSIZE *block, *blockgpu;
        cudaHostAlloc((void **)&block, sizeof(QSIZE)*m, cudaHostAllocMapped);
        cudaHostGetDevicePointer(&blockgpu, block, 0);
        for (QSIZE i = 0; i < m; i++)
        {
            block[i] = 1 << qnum[i];
        }
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        controlRZdagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), blockgpu, 1 << target, m, costheta, sintheta);
        cudaFreeHost(block);
    }
    GET_SYN_RES("controlRZdagger")
}
bool GATEGPU:: toffoli(QState& psigpu, size_t qn0, size_t qn1, size_t qn2, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        toffoli << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn0, 1 << qn1, 1 << qn2);
    }
    GET_SYN_RES("toffoli")
}
bool GATEGPU:: toffolidagger(QState& psigpu, size_t qn0, size_t qn1, size_t qn2, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        //QState* QPsi = (QState*)psi;
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        toffolidagger << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn0, 1 << qn1, 1 << qn2);
    }
    GET_SYN_RES("toffolidagger")
}
bool GATEGPU:: qbReset(QState& psigpu, size_t qn, double error_rate)
{
    if (randGenerator() > error_rate)
    {
        double * resultgpu;
        // cudaHostAlloc((void **)&result, sizeof(STATE_T)*(psigpu.qnum-1))/THREADDIM, cudaHostAllocMapped);
        //cudaHostGetDevicePointer(&resultgpu, result, 0);
        cudaMalloc((void **)&resultgpu, sizeof(STATE_T)*(1 << (psigpu.qnum - 1)) / THREADDIM);
        double * probgpu, *prob;
        cudaHostAlloc((void **)&prob, sizeof(STATE_T), cudaHostAllocMapped);
        cudaHostGetDevicePointer(&probgpu, prob, 0);
        QSIZE BLOCKDIM;
        SET_BLOCKDIM
        qubitprob << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM, THREADDIM * sizeof(STATE_T) >> > (psigpu.real, psigpu.imag, 1 << (psigpu.qnum), 1 << qn, resultgpu);    //概率第一次归约
        probsum << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (resultgpu, probgpu);                   //要测量的态的概率存在prob中
        cudaDeviceSynchronize();           //等概率完全计算出来
        *prob = 1 / sqrt(*prob);
        qubitcollapse0 << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag, 1 << (psigpu.qnum), 1 << qn, *prob);
        cudaDeviceSynchronize();           
        cudaFree(resultgpu);
        cudaFreeHost(prob);
       // std::cout << "err = " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
    }
    GET_SYN_RES("qbReset")
    
}




/*
void GATEGPU:: unitarySingleQubitGate(double * psireal, double * psiimag, QSIZE Block, double *matr)
{
    double * matrgpu;
    cudaMalloc((void GATEGPU:: **)(&matrgpu), sizeof(STATE_T) * 8);
    cudaMemcpy((void *)matrgpu, (void *)matr, sizeof(STATE_T) * 8, cudaMemcpyHostToDevice);
    unitary << < ((BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psireal, psiimag, matrgpu, Block);
    cudaFree(&matrgpu);
}//checked
*/
int GATEGPU:: qubitmeasure(QState& psigpu, QSIZE Block)
{
    
    // double * result;
    double * resultgpu;
    // cudaHostAlloc((void **)&result, sizeof(STATE_T)*(psigpu.qnum-1))/THREADDIM, cudaHostAllocMapped);
    //cudaHostGetDevicePointer(&resultgpu, result, 0);
    //QSIZE BLOCKDIM = (1 << (psigpu.qnum - 1)) / THREADDIM;
    QSIZE BLOCKDIM;
    SET_BLOCKDIM
    cudaError_t cudaState = cudaMalloc(&resultgpu, sizeof(STATE_T)* (BLOCKDIM == 0 ? 1 : BLOCKDIM));
    if (cudaSuccess != cudaState)
    {
        cout << "resultgpu  " << cudaGetErrorString(cudaState) << endl;
        return -1;
    }
    double * probgpu, prob;
    //cudaHostAlloc((void **)&prob, sizeof(STATE_T), cudaHostAllocMapped);
    //cudaHostGetDevicePointer(&probgpu, prob, 0);
    cudaState = cudaMalloc(&probgpu, sizeof(STATE_T));
    if (cudaSuccess != cudaState)
    {
        cout << "probgpu  " << cudaGetErrorString(cudaState) << endl;
        cudaFree(resultgpu);
        return -1;
    }
    qubitprob << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM, THREADDIM * sizeof(STATE_T) >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), Block, resultgpu);    //概率第一次归约
    cudaState = cudaDeviceSynchronize();           //等概率完全计算出来
    if (cudaSuccess != cudaState)
    {
        cout << cudaGetErrorString(cudaState) << endl;
        cudaFree(resultgpu);
        cudaFree(probgpu);
        return -1;
    }
    //double *prob;
    probsum << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (resultgpu, probgpu);                   //要测量的态的概率存在prob中
    cudaState = cudaDeviceSynchronize();           //等概率完全计算出来
    if (cudaSuccess != cudaState)
    {
        cout << cudaGetErrorString(cudaState) << endl;
        cudaFree(resultgpu);
        cudaFree(probgpu);
        return -1;
    }
    cudaMemcpy(&prob, probgpu, sizeof(STATE_T), cudaMemcpyDeviceToHost);
    cudaState = cudaDeviceSynchronize();           //等概率完全计算出来
    if (cudaSuccess != cudaState)
    {
        cout  << cudaGetErrorString(cudaState) << endl;
        cudaFree(resultgpu);
        cudaFree(probgpu);
        return -1;
    }
                                       //cudaMemcpy((void GATEGPU::*)&prob1, (void GATEGPU::*)prob, sizeof(STATE_T), cudaMemcpyDeviceToHost);
    //dprob.prob = prob[0];
    //cout << prob[0] << "\t" << *prob << endl;
    //cout << "prob\t" << dprob.prob << endl;
    //*prob = prob1;
    int outcome = 0;
    if (randGenerator() > prob)
    {
        outcome = 1;
    }
    if (0 == outcome)
    {
       
        prob = 1 / sqrt(prob);
        qubitcollapse0 << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), Block, prob);
        //GET_SYN_RES("qubitmeasure")
    }
    else
    {
        
        prob = 1 / sqrt(1 - prob);
        qubitcollapse1 << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), Block, prob);
    //    GET_SYN_RES("qubitmeasure")
    }
    cudaState = cudaFree(resultgpu);
    if (cudaSuccess!=cudaState)
    {
        cout << "resultgpu free error" << endl;
        return -1;
    }
    cudaState =cudaFree(probgpu);
    if (cudaSuccess != cudaState)
    {
        cout << "probgpu free error" << endl;
        return -1;
    }
    //cudaFreeHost(prob);
    return outcome;
}//checked
 /*
 void GATEGPU:: Hadamard(QState& psi, size_t qn, double error_rate = 0)
 {

 Hadamard << < ((BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), 1 << qn);
 }*/

 //vecuint qnumtostate(vecuint& qn)
 //{

 //vecuint state(qn.size(), 0);

 //}
#if 0



bool GATEGPU:: pMeasure(QState& psigpu, vecprob& vprob,QSIZE * block, QSIZE m)
{
    QSIZE temp;
    for (int i = 0; i < m - 1; i++)
    {
        for (int j = 0; j < m - i - 1; j++)
        {
            if (block[j] > block[j + 1])
            {
                temp = block[j];
                block[j] = block[j + 1];
                block[j + 1] = temp;
            }
        }
    }//排序
    double *probgpu;
    double * probc, *result;
    cudaError_t cudaStatus=cudaHostAlloc(&probc, sizeof(STATE_T)*(1 << m), cudaHostAllocMapped);
    if (cudaStatus != cudaSuccess)
    {
        printf("host alloc fail!\n");
        return true;
    }
    cudaHostGetDevicePointer(&probgpu, probc, 0);
    //probc=(STATE_T*)malloc(sizeof(STATE_T)*(1<<m));          //各个态的概率
    QSIZE *blockgpu1;                       //block
    QSIZE BLOCKDIM = (1 << (psigpu.qnum - 1)) / THREADDIM;
    cudaMalloc((&blockgpu1), sizeof(QSIZE)*m);
    cudaMalloc((&result), sizeof(STATE_T)*BLOCKDIM);          //求概率的中间变量
                                                                           //cudaMalloc((void **)(&probgpu), sizeof(STATE_T)*(1<<m));
    cudaMemcpy(blockgpu1, block, sizeof(QSIZE)*m, cudaMemcpyHostToDevice);//blockgpu1 contains target qubit
    for (int i = 0; i < 1 << m; i++)
    {

        int index = 0;
        for (int j = 0; j < m; j++)
        {
            index += block[j] * ((i >> j) % 2);
        }
        //cout << "index\t" << index << endl;
        multiprob << < ((BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM, THREADDIM * sizeof(STATE_T) >> > (psigpu.real, psigpu.imag,1<<(psigpu.qnum), result, blockgpu1, m, index);
        //std::cout << "err1 = " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
        probsum << < ((BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (result, &probgpu[i]);
        //std::cout << "err2 = " << cudaGetErrorString(cudaDeviceSynchronize()) << endl;
        //cudaMemcpy((void GATEGPU::*)probc, (void GATEGPU::*)probgpu, sizeof(STATE_T)*(1<<m), cudaMemcpyDeviceToHost);
        cudaDeviceSynchronize();
        //vprob[i].first = i;
        //vprob[i].second = probc[i];
        vprob.push_back(PAIR(i, probc[i]));

    }
    //std::cout << *probc << endl;
    cudaFree(result);
    cudaFree(blockgpu1);
    cudaFreeHost(probc);
    return ;
}
#endif // 0
#if 1

bool probcompare(pair<size_t, double>& a, pair<size_t, double>& b)
{
    return a.second> b.second;
}

bool GATEGPU::pMeasurenew(QState& psigpu, vector<pair<size_t, double>>& vprob, Qnum& qnum)
{
    cudaDeviceSynchronize();
    QSIZE m = qnum.size();
    sort(qnum.begin(),qnum.end());
    if (m <= psigpu.qnum / 2)
    {
        QSIZE *block, *blockgpu;
        cudaHostAlloc(&block, sizeof(QSIZE)*m, cudaHostAllocMapped);
        cudaHostGetDevicePointer(&blockgpu, block, 0);
        QSIZE temp;
        for (size_t i = 0; i < m; i++)
        {
            block[i] = 1 << qnum[i];
        }//排序
        double *probgpu;
        double * probc, *result;
        cudaError_t cudaStatus = cudaHostAlloc(&probc, sizeof(STATE_T)*(1 << m), cudaHostAllocMapped);
        if (cudaStatus != cudaSuccess)
        {
            printf("host alloc fail!\n");
            return false;
        }
        cudaHostGetDevicePointer(&probgpu, probc, 0);
        //probc=(STATE_T*)malloc(sizeof(STATE_T)*(1<<m));          //各个态的概率
        QSIZE *blockgpu1;                       //block
        QSIZE BLOCKDIM = (1u << (psigpu.qnum - 1)) / THREADDIM;
        cudaMalloc((&blockgpu1), sizeof(QSIZE)*m);
        cudaMalloc((&result), sizeof(double)*(BLOCKDIM == 0 ? 1 : BLOCKDIM));          //求概率的中间变量
                                                                                       //cudaMalloc((void **)(&probgpu), sizeof(STATE_T)*(1<<m));
        cudaMemcpy(blockgpu1, block, sizeof(QSIZE)*m, cudaMemcpyHostToDevice);
        for (size_t i = 0; i < 1u << m; i++)
        {
            size_t index = 0;
            for (size_t j = 0; j < m; j++)
            {
                index += block[j] * ((i >> j) % 2);
            }
            // cout << "index\t" << index << endl;
            multiprob << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM, THREADDIM * sizeof(STATE_T) >> > (psigpu.real, psigpu.imag, 1 << (psigpu.qnum), result, blockgpu1, m, index);
            probsum << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (result, probgpu + i);
            //cudaMemcpy((void GATEGPU::*)probc, (void GATEGPU::*)probgpu, sizeof(STATE_T)*(1<<m), cudaMemcpyDeviceToHost);
            cudaDeviceSynchronize();
            //vprob[i].first = i;
            //vprob[i].second = probc[i];
            vprob.push_back(PAIR(i, probc[i]));

        }
        if (vprob.size() <= 10)
        {
            sort(vprob.begin(), vprob.end(), probcompare);
        }
        else
        {
            sort(vprob.begin(), vprob.end(), probcompare);
            vprob.erase(vprob.begin() + 10, vprob.end());
        }
        //std::cout << *probc << endl;
        cudaFree(result);
        cudaFree(blockgpu1);
        cudaFreeHost(probc);
        cudaFreeHost(block);
        return true;
    }
    else
    {
        size_t Dim = 1u << psigpu.qnum;
        size_t blocknum = 1u << (m - psigpu.qnum / 4);         //blocknum表示block数
        STATE_T *probtemp, *probtempgpu;
        cudaError_t cudastate;
        cudastate = cudaHostAlloc(&probtemp, sizeof(double) * blocknum, cudaHostAllocMapped);
        if (cudastate != cudaSuccess)
        {
            cudaFreeHost(probtemp);
            return false;
        }
        cudastate = cudaHostGetDevicePointer(&probtempgpu, probtemp, 0);
        if (cudastate != cudaSuccess)
        {
            cudaFreeHost(probtemp);
            return false;
        }
        size_t *block, *blockgpu;
        cudastate = cudaHostAlloc(&block, sizeof(size_t)*m, cudaHostAllocMapped);
        if (cudastate != cudaSuccess)
        {
            cudaFreeHost(probtemp);
            cudaFreeHost(block);
            return false;
        }
        cudastate = cudaHostGetDevicePointer(&blockgpu, block, 0);
        if (cudastate != cudaSuccess)
        {
            cudaFreeHost(probtemp);
            cudaFreeHost(block);
            return false;
        }
        for (size_t i = 0; i < m; i++)
        {
            block[i] = 1u << qnum[i];
        }//排序
        for (size_t i = 0; i < blocknum; i++)
        {
            probtemp[i] = 0;
        }
        for (size_t i = 0; i < 10; i++)
        {
            vprob.push_back(PAIR(0, 0));
        }
        size_t BLOCKDIM = blocknum / THREADDIM;
        for (size_t i = 0; i < (1u << m); i += blocknum)
        {
            //(STATE_T * psireal, STATE_T * psiimag, STATE_T *probtemp, size_t num1, size_t m, size_t Dim, size_t * block)
            
            probsumnew1 << < (BLOCKDIM == 0 ? 1 : BLOCKDIM), THREADDIM >> > (psigpu.real, psigpu.imag, probtempgpu, i, m, Dim, blockgpu);
            
            cudastate =  cudaDeviceSynchronize();
            if (cudaSuccess!=cudastate)
            {
                cout << "error" << endl;
            }
            for (size_t j = 0; j < blocknum; j++)
            {
                if (probtemp[j] > vprob[9].second)
                {
                    vprob[9] = PAIR(i + j, probtemp[j]);
                    sort(vprob.begin(), vprob.end(), probcompare);
                }
            }
        }
        cudaFreeHost(probtemp);
        cudaFreeHost(block);
        return true;
    }

}

#endif // 0


#if 0
bool GATEGPU::pMeasurenew(QState& psigpu, vector<pair<int, double>>& vprob, Qnum& qnum)
{
    QSIZE dim = (1 << psigpu.qnum);

    double* psiHostReal = (double*)malloc(dim * sizeof(double));

    double* psiHostImag = (double*)malloc(dim * sizeof(double));

    cudaMemcpy(psiHostReal, psigpu.real, dim * sizeof(double), cudaMemcpyDeviceToHost);

    cudaMemcpy(psiHostImag, psigpu.imag, dim * sizeof(double), cudaMemcpyDeviceToHost);

    vprob.resize((1 << qnum.size()));

    for (int i = 0; i < (1 << qnum.size()); i++)
    {
        vprob[i].first = i;
        vprob[i].second = 0;
    }

    for (int i = 0; i <dim; i++)
    {
        volatile int idx = 0;
        for (int j = 0; j < qnum.size(); j++)
        {
            idx += (((i >> (qnum[j])) & 1) << (qnum.size() - 1 - j));
        }
        vprob[idx].second +=
            (
                abs(psiHostReal[i])*abs(psiHostReal[i])
                +
                abs(psiHostImag[i])*abs(psiHostImag[i])
                );
    }

    if (vprob.size() <= 10)
    {
        sort(vprob.begin(), vprob.end(), probcompare);
    }
    else
    {
        sort(vprob.begin(), vprob.end(), probcompare);
        vprob.erase(vprob.begin() + 10, vprob.end());
    }

    free(psiHostReal);
    free(psiHostImag);
    return true;
}
#endif  //0
bool GATEGPU::getState(QState &psi,QState &psigpu,int qnum)
{
	if (qnum < 30)
    {
        QSIZE Dim = 1 << qnum;
        cudaMemcpy(psi.real, psigpu.real, sizeof(STATE_T)*Dim, cudaMemcpyDeviceToHost);
        cudaMemcpy(psi.imag, psigpu.imag, sizeof(STATE_T)*Dim, cudaMemcpyDeviceToHost);
    }
    return true;
}

double GATEGPU:: randGenerator()
{
    int  ia = 16807, im = 2147483647, iq = 127773, ir = 2836;           /*difine constant number in 16807 generator.*/
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    static int irandseed = timeinfo->tm_year + 70 *
        (timeinfo->tm_mon + 1 + 12 *
        (timeinfo->tm_mday + 31 *
            (timeinfo->tm_hour + 23 *
            (timeinfo->tm_min + 59 * timeinfo->tm_sec))));
    static int irandnewseed;
    if (ia*(irandseed%iq) - ir*(irandseed / iq) >= 0)
        irandnewseed = ia*(irandseed%iq) - ir*(irandseed / iq);
    else
        irandnewseed = ia*(irandseed%iq) - ir*(irandseed / iq) + im;
    irandseed = irandnewseed;
    return (double)irandnewseed / im;

}
