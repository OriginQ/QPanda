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
Date:2017-11-23
Description: quantum system command control API
*****************************************************************************************************************/
#include "QCommandVectorBase.h"
#include "QuantumCommandCtrAPI.h"
#include "QSimulateCommandVector.h"
#include "QCloudCommandVector.h"

static QCommandVectorBase *_G_pCommandVector;                               /* globe command vector                 */

/*****************************************************************************************************************
Name:        initCommandVector
Description: init command vector
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool initCommandVector(int iMode)
{
    if (iMode == 0)
    {
        return false;
    }
    if (1 == iMode)
    {
        _G_pCommandVector = new QSimulateCommandVector;
    }
    else if (2 == iMode)
    {
        _G_pCommandVector = new QCloudCommandVector;
    }
    else
    {

    }

    return true;
}

/*****************************************************************************************************************
Name:        deleteCommandVector
Description: delete command vector
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool deleteCommandVector()
{
    bool bResult = true;

    if (NULL != _G_pCommandVector)
    {
        delete(_G_pCommandVector);
    }
    else
    {
        bResult = false;
    }

    return bResult;
} 
/*****************************************************************************************************************
Name:        exitCommand
Description: exit command
Argin:       None
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool exitCommand()
{
    deleteCommandVector(); 
    exit(0);
}

/*****************************************************************************************************************
Name:        commandAction
Description: command action
Argin:       ssAction  command from upper layer
Argout:      None
return:      true or false
*****************************************************************************************************************/
bool commandAction(stringstream & ssAction)
{
    if (ssAction.str().empty())
    {
        return false;
    }

    if (0 == strcmp(ssAction.str().c_str(), "help"))
    {
        _G_pCommandVector->commandDescription();
        return true;
    }
    else if (0 == strcmp(ssAction.str().c_str(), "exit"))
    {
        exitCommand();
    }
    return _G_pCommandVector->commandAction(ssAction);
}


                                                                   
