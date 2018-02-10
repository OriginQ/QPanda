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
************************************************************************/
#include "QRunesParserAPI.h"

extern int qNum;

/*****************************************************************************************************************
Name:        QRunesParser
Description: quantum run parser 
Argin:       sFilePath        quantum program file path
             QInstructionList quantum instruction list
Argout:      QInstructionList quantum instruction list
return:      number of quantum bit 
*****************************************************************************************************************/
int QRunesParser(string &sFilePath, QList &QInstructionList)
{
    int bResult = -1;
    if (sFilePath.empty())
    {
        return bResult;
    }
    QList qlist;
    int status = parser(sFilePath.c_str(), qlist);

    if (0 == status)
    {
        QInstructionList = qlist;
        bResult = qNum;
    }
    
    return bResult;
}
