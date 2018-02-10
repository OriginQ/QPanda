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
Description: quantum system command vector base
*****************************************************************************************************************/
#ifndef _Q_COMMNAD_VECTOR_BASE_H
#define _Q_COMMNAD_VECTOR_BASE_H

#include <sstream>
#include <iostream>

class QCommandVectorBase
{
public:
    
    QCommandVectorBase() {};
    virtual ~QCommandVectorBase() {};

    /*************************************************************************************************************
    Name:        commandAction
    Description: command  action
    Argin:       ssAction  command name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    virtual bool commandAction(std::stringstream & ssAction) = 0;

    /*************************************************************************************************************
    Name:        commandDescription
    Description: command  Description
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    virtual void commandDescription() = 0;
private:

};


#endif // !_Q_COMMNAD_VECTOR_BASE_H

