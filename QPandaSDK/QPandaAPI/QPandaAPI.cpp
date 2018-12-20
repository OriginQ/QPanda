/*****************************************************************************************************************
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
Date:2018-01-19
Description: QParserSDK
*****************************************************************************************************************/
#include "QPandaAPI.h"
#include <algorithm>
using namespace  QPanda;

QPandaSDK::QPandaSDK()
{
    mbIsRead = false;
    miComputeType = -1;
    miMeasureType = -1;
    mbIsRun = false;
    mQGatesParam = nullptr;
}


QPandaSDK::~QPandaSDK()
{
    mQList.listClear();

    mQHandle.destroyState(mQGatesParam);

    if (nullptr != mQGatesParam)
    {
        delete(mQGatesParam);
    }
}

/*****************************************************************************************************************
Name:        loadQProgram
Description: load quantum program
Argin:       sFilePath  quantum program file path
Argout:      Qnum       quantum bit num
return:      qerror
*****************************************************************************************************************/
int QPandaSDK::loadFile(const string &sFilePath)
{
    /*
     *  judgment of conditions
     */

    if(0 ==sFilePath.size())
    {
        return qParameterError;
    }

    mbIsRead = false;
    miComputeType = -1;
    miMeasureType = -1;
    mbIsRun = false;
    if (nullptr != mQGatesParam)
    {
        delete(mQGatesParam);
    }
    mQGatesParam = new QuantumGateParam();
    msFileName.clear();
    msFileName.append(sFilePath);
    mQList.listClear();
    /*
     *  analyse quantum program file
     */
    int iResult = QRunesParser(msFileName,mQList);

    if ((iResult <= 0)||(iResult > 30))
    {
        return qbitError;
    }

    mQGatesParam->mQuantumBitNumber = iResult;
    mbIsRead = true;

    return qErrorNone;
}

/*****************************************************************************************************************
Name:        setComputeUnit
Description: set compute unit,you have two options:CPU or GPU.you can not choose again when you have 
             already selected a compute unit
Argin:       iComputeUnit  the type of compute unit
Argout:      None
return:      qerror
*****************************************************************************************************************/
int QPandaSDK::setComputeUnit(int iComputeUnit)
{
    /*
     *  judgment of conditions
     */
    if((iComputeUnit <= 0)||(iComputeUnit > 2))
    {
        return qParameterError;
    }

    if(!mQHandle.setComputeUnit(iComputeUnit))                          /* set compute unit fail                */
    {
        return setComputeUnitError;
    }
    
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        runQProgram
Description: run quantum program
Argin:       iRepeat    quantum program repeat
Argout:      None
return:      qerror
*****************************************************************************************************************/
int QPandaSDK::run(int iRepeat)
{
    if (iRepeat <= 0)
    {
        return qParameterError;
    }

    if (!mbIsRead)
    {
        return notReadFileError;
    }
    
    /*
     *  initialize the operating environment 
     */
    mQGatesParam->mPMeasure.clear();
    mQGatesParam->mReturnValue.clear();
    mQResultMap.clear();
    if (!mbIsRun)
    {
        if (!mQHandle.initState(mQGatesParam))
        {
            return initStateError;
        }
    }


    QError bResult =qErrorNone;

    /*
     * run the program first to determine the type of measurement
     */
    if(!mQHandle.transmit(mQList,mQGatesParam))                        
    {
        bResult =runProgramError;
        mbIsRun = false;
    }

    if((0 == mQGatesParam->mPMeasureSize)&&(qErrorNone == bResult))      /* measure                              */
    {
        countState();
        miMeasureType = MEASURE;
        for (int i = 1; i < iRepeat; i++)
        {
            if(!mQHandle.transmit(mQList,mQGatesParam))
            {
                bResult = runProgramError;
                mbIsRun = false;
                break;
            }
            countState();
        }

        for (auto aiter = mQResultMap.begin();
             aiter !=mQResultMap.end();
             aiter++)
        {
            aiter->second = (aiter->second / iRepeat);
        }
    }
    else                                                                /* pmeasure                             */
    {
        stringstream ssResult;

        miMeasureType = PMEASURE;

        for (auto aiter : mQGatesParam->mPMeasure)
        {
            integerToBinary(aiter.first, ssResult, mQGatesParam->mPMeasureSize);
            mQResultMap.insert(PAIR(ssResult.str(), aiter.second));
            ssResult.str("");
        }
    }

    if (qErrorNone == bResult)
    {
        mbIsRun = true;
    }

    return bResult;
}

/*****************************************************************************************************************
Name:        getQResult
Description: get quantum program result
Argin:       None
Argout:      sResult   result string
return:      qerror
*****************************************************************************************************************/
STRING QPandaSDK::getResult()
{
    STRING sResult;
    stringstream ssTemp;
    if ((!mbIsRun)||(0 == mQResultMap.size()))
    {
        
        return ssTemp.str();

    }
    for (auto aiter : mQResultMap)
    {
        ssTemp << aiter.first << " " << aiter.second << "\n";
        sResult.append(ssTemp.str());
        ssTemp.str("");
    }
    return sResult;
}

/*****************************************************************************************************************
Name:        getQState
Description: get quantum program qstate
Argin:       None
return:      qerror
*****************************************************************************************************************/
STRING QPandaSDK::getQuantumState()
{
    STRING sState;
    if (!mbIsRun)
    {
        return sState;
    }
    mQHandle.getState(sState, mQGatesParam);

    return sState;
}

/*****************************************************************************************************************
Name         countState
Description: statistical results
Argin:       None
Argout:      None
return:      None
*****************************************************************************************************************/
void QPandaSDK::countState()
{
    stringstream ssResult;

    for (auto aiter : mQGatesParam->mReturnValue)
    {
        ssResult <<aiter.second;
    }

    string sResult(ssResult.str());
    reverse(sResult.begin(), sResult.end());
    auto aiter = mQResultMap.find(sResult);
    if (mQResultMap.end() !=  aiter)
    {
        aiter->second+=1; 
    }
    else
    {
        mQResultMap.insert(PAIR(sResult,1));
    }

}

/*****************************************************************************************************************
Name:        integerToBinary
Description: integer to binary
Argin:       number     src number
             iRetLen    ssRet len
Argout:      ssRet      binary result
return:      true or false
*****************************************************************************************************************/
bool QPandaSDK::integerToBinary(size_t number, stringstream & ssRet, size_t ret_len)
{
    unsigned int index;

    index = 1 << (ret_len - 1);                        
    for (int i = 0; i<ret_len; ++i)
    {
        ssRet<< (((number&index) == 0) ? '0' : '1'); 
        index >>= 1;                          
    }
    return true;
}

int  loadFileAPI(char * pcFilePath)
{
    auto temp = QPandaSDK::getIntance();
    string sFilePaht(pcFilePath);
    return temp->loadFile(sFilePaht);

}

int  setComputeUnitAPI(int iComputeUnit)
{
    auto temp = QPandaSDK::getIntance();
    return temp->setComputeUnit(iComputeUnit);
}

int  runAPI(int iRepeat)
{
    auto temp = QPandaSDK::getIntance();
    return temp->run(iRepeat);
}

int  getFileNameAPI(char * buf, int * pLength)
{
    auto temp = QPandaSDK::getIntance();
    auto sFileName = temp->msFileName;
    auto iLength = sFileName.size();

    if (0 != (*pLength))
    {
        memcpy(buf, sFileName.c_str(), (*pLength));
    }

    (*pLength) = (int)iLength;

    return qErrorNone;
}

int  getResultAPI(char * buf, int * pLength)
{
    auto temp = QPandaSDK::getIntance();
    auto sResult = temp->getResult();
    auto iLength = sResult.size();

    if (0 != (*pLength))
    {
        memcpy(buf, sResult.c_str(), iLength);
    }

    (*pLength) = (int)iLength;
    return qErrorNone;
}

int  getQuantumStateAPI(char * buf, int * pLength)
{
    auto temp = QPandaSDK::getIntance();
    auto sStat = temp->getQuantumState();
    auto iLength = sStat.size();

    if (0 != (*pLength))
    {
        memcpy(buf, sStat.c_str(), iLength);
    }

    (*pLength) = (int)iLength;
    return qErrorNone;
}
