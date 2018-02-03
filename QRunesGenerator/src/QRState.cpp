
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
*******************************************************************************/

#include "QRState.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "QRException.h"
bool qubit::qInit = false;
size_t qubit::qNum = 0;
size_t qNumMax = 0;

using std::ofstream;
using std::endl;
using std::cout;
using std::stringstream;

qubit::qubit()
{
	extern size_t qNumMax;
    qID = qNum;
    qNum++;
    //cout << qNum;
    if (qNum > qNumMax)
        qNumMax = qNum;
    qInit = true;
}

qubit::~qubit()
{
    qNum--;
	/*
	extern size_t qNumMax;	
    if (qNum == 0)
    {
        extern ofstream out;
        extern stringstream code;
        extern size_t cRegCount;
		out << "%QRunes V2.0 - Powered by Origin Q" << endl;
        out << "QINIT " << qNumMax << endl; 
        out << "CREG " << cRegCount << endl;
        out << code.str();
        out << "END";
        out.close();        
    }
	*/
}

size_t qubit::getQID()
{
    return this->qID;
}

ancilla::ancilla()
{
    /* empty constructor */
}

ancilla::~ancilla()
{
    extern stringstream code;
    code << "RESET " << qNum-1 << endl;
	/*
	extern size_t qNumMax;
    if (qNum == 0)
    {
        extern ofstream out;
		out << "%QRunes V2.0 - Powered by Origin Q" << endl;
        out << "QINIT " << qNumMax << endl;
        out << code.str();
        out << "END";
        out.close();
    }
	*/
}