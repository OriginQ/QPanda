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

using namespace  QPanda;

QPandaAPI::QPandaAPI()
{
    mbIsRead = false;
    miComputeType = -1;
    miMeasureType = -1;
    mbIsRun = false;
}


QPandaAPI::~QPandaAPI()
{
    mQList.listClear();

    mQHandle.destroyState(&mQGatesParam);
}

/*****************************************************************************************************************
Name:        loadQProgram
Description: load quantum program
Argin:       sFilePath  quantum program file path
Argout:      Qnum       quantum bit num
return:      qerror
*****************************************************************************************************************/
QError QPandaAPI::loadFile(const string &sFilePath,int &Qnum)
{
    /*
     *  judgment of conditions
     */
    if(0 ==sFilePath.size()||(mbIsRead))
    {
        return qParameterError;
    }
    msFileName.append(sFilePath);

    /*
     *  analyse quantum program file
     */
    int iResult = QRunesParser(msFileName,mQList);

    if ((iResult <= 0)||(iResult > 30))
    {
        return qbitError;
    }

    mQGatesParam.mQuantumBitNumber = iResult;
    mbIsRead = true;
    Qnum = iResult;

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
QError QPandaAPI::setComputeUnit(int iComputeUnit)
{
    /*
     *  judgment of conditions
     */
    if(iComputeUnit <= 0)
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
QError QPandaAPI::run(int iRepeat)
{
    if ((iRepeat <= 0)||(!mbIsRead))
    {
        return qParameterError;
    }
    
    /*
     *  initialize the operating environment 
     */
    mQGatesParam.mPMeasure.clear();
    mQGatesParam.mReturnValue.clear();
    mQResultMap.clear();
    msResult.clear();
    if (!mbIsRun)                                                       /* run the program for the first time   */
    {
        if (!mQHandle.initState(&mQGatesParam))
        {
            return initStateError;
        }
    }

    QError bResult =qErrorNone;

    /*
     * run the program first to determine the type of measurement
     */
    if(!mQHandle.transmit(mQList,&mQGatesParam))                        
    {
        bResult =runProgramError;
        mbIsRun = false;
    }

    if((0 == mQGatesParam.mPMeasureSize)&&(qErrorNone == bResult))      /* measure                              */
    {
        countState();
        miMeasureType = MEASURE;
        for (int i = 1; i < iRepeat; i++)
        {
            if(!mQHandle.transmit(mQList,&mQGatesParam))
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

        for (auto aiter : mQGatesParam.mPMeasure)
        {
            integerToBinary(aiter.first, ssResult, mQGatesParam.mPMeasureSize);
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
QError QPandaAPI::getResult()
{
    if ((!mbIsRun)||(0 != msResult.size())||(0 == mQResultMap.size()))
    {
        
        return qParameterError;

    }
    stringstream ssTemp;
    for (auto aiter : mQResultMap)
    {
        ssTemp << aiter.first << " " << aiter.second << "\n";
        msResult.append(ssTemp.str());
        ssTemp.str("");
    }
    return qErrorNone;
}

/*****************************************************************************************************************
Name:        getQState
Description: get quantum program qstate
Argin:       None
return:      qerror
*****************************************************************************************************************/
QError QPandaAPI::getQuantumState()
{
    if (!mbIsRun)
    {
        return qParameterError;
    }
    msState.clear();

    if (!mQHandle.getState(msState, &mQGatesParam))
    {
        return getQStateError;
    } 
    return qErrorNone;
}

/*****************************************************************************************************************
Name         countState
Description: statistical results
Argin:       None
Argout:      None
return:      None
*****************************************************************************************************************/
void QPandaAPI::countState()
{
    stringstream ssReuslt;

    for (auto aiter : mQGatesParam.mReturnValue)
    {
        ssReuslt<<aiter.second;
    }

    auto aiter = mQResultMap.find(ssReuslt.str());
    if (mQResultMap.end() !=  aiter)
    {
        aiter->second+=1; 
    }
    else
    {
        mQResultMap.insert(PAIR(ssReuslt.str(),1));
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
bool QPandaAPI::integerToBinary(int number, stringstream & ssRet, int ret_len)
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

