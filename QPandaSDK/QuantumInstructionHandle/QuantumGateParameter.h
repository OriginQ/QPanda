/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-12-20
Description:QuantumGateParam class
*****************************************************************************************************************/
#ifndef _QUANTUM_GATE_PARAM_H
#define _QUANTUM_GATE_PARAM_H
#include <mutex>
#include <iostream>
#include <map>
#include <complex>
#include <algorithm>
#include <vector>
#include "../GPUEmulator/GPUStruct.h"

/*****************************************************************************************************************
QuantumGateParam:quantum gate param 
*****************************************************************************************************************/
class QuantumGateParam
{
    typedef std::vector <std::complex<double>> QStat;
 public:
    int                           mPMeasureSize;                        /* PMeasure bit size                    */
    int                           mQuantumBitNumber;                    /* quantum bit number                   */

    std::map<size_t, int>              mReturnValue;                    /* MonteCarlo result                    */
    std::vector<std::pair<size_t, double>>  mPMeasure;                  /* Pmeasure result                      */

    QuantumGateParam() : mPMeasureSize(0),mQuantumBitNumber(0){};
    ~QuantumGateParam()
    {
        mReturnValue.clear();
        mPMeasure.clear();
    };

    /*************************************************************************************************************
    Name:        setQBitNum
    Description: set quantum number
    Argin:       iQuantumBitNum      quantum bit number
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    inline bool setQBitNum(int iQuantumBitNum)
    {
        mQuantumBitNumber =iQuantumBitNum;
        return true;
    }
};

#endif
