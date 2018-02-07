/*****************************************************************************************************************
Copyright:
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
    stringstream sExit;
    sExit << "exit";

    if (!_G_pCommandVector->commandAction(sExit))
    {
        return false;
    }

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

    }
    else if (0 == strcmp(ssAction.str().c_str(), "exit"))
    {
        exitCommand();
    }
    return _G_pCommandVector->commandAction(ssAction);
}


                                                                   