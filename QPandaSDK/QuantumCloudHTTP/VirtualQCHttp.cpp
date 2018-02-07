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

Author: Dou Menghan
Date:2018-1-28
Description: virtual quantum cloud http
************************************************************************/
#include "VirtualQCHttp.h"
#include "QuantumCloudHTTP.h"


VirtualQCHttp::VirtualQCHttp()
{
}


VirtualQCHttp::~VirtualQCHttp()
{
}

/*****************************************************************************************************************
Name:        createQCHttp
Description: create quantum http class
Argin:       sKeyFilePath   key file path
Argout:      None  
return:      true or false
*****************************************************************************************************************/
VirtualQCHttp * createQCHttp(std::string &sKeyFilePath)
{
    return (VirtualQCHttp *)new QuantumCloudHTTP(sKeyFilePath);
}

/*****************************************************************************************************************
Name:        destroyQCHttp
Description: destroy quantum http class
Argin:       pVQCHttp   virtual quantum http class pointer
Argout:      None  
return:      true or false
*****************************************************************************************************************/
bool destroyQCHttp(VirtualQCHttp * pVQCHttp)
{
    delete(pVQCHttp);
    return true;
}
