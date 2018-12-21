
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

#include <sstream>
#include <exception>
#include <iostream>
#include "QRException.h"
#include "QRGateController.h"

using std::stringstream;
using std::endl;
using std::cerr;

stringstream code;
size_t cRegCount = 0;

/********************************************************************
Name:           Hadamard
Description:    in ofstream output the cmd
Argin:          reference of qubit
Argout:         reference of qubit -> after gate
return:         n/a
********************************************************************/
void QRunes::Hadamard(qubit& q)
{
    try
    {
        code << "H " << q.getQID() << endl;
    }
    catch (exception E)
    {
        cerr << "1" << endl;
        GateOutputException rethrowException;
        throw(rethrowException);
    }
}

/********************************************************************
Name:           CNOT
Description:    in ofstream output the cmd
Argin:          reference of qubit1&2 ( 1 control 2 target )
Argout:         reference of qubit1&2 -> after gate
return:         n/a
********************************************************************/
void QRunes::CNOT(qubit& q1, qubit& q2)
{
    try
    {
        code << "CNOT " << q1.getQID() << "," << q2.getQID() << endl;
    }
    catch (exception E)
    {
        cerr << "2" << endl;
        GateOutputException rethrowException;
        throw(rethrowException);
    }
}

void QRunes::BEGIN_DAGGER()
{
    try
    {
        code << "DAGGER" << endl;
    }
    catch (exception E)
    {
        cerr << "1" << endl;
        GateOutputException rethrowException;
        throw(rethrowException);
    }
}

void QRunes::END_DAGGER()
{
    try
    {
        code << "ENDDAGGER" << endl;
    }
    catch (exception E)
    {
        cerr << "1" << endl;
        GateOutputException rethrowException;
        throw(rethrowException);
    }
}

/********************************************************************
Name:           RX
Description:    in ofstream output the cmd
Argin:          reference of qubit, rotation angle
Argout:         reference of qubit -> after gate
return:         n/a
********************************************************************/
void QRunes::RX(qubit& q,double angle)
{
    try
    {
        code << "RX " << q.getQID() << "," << '"' << angle << '"' << endl;
    }
    catch (exception E)
    {
        cerr << "1" << endl;
        GateOutputException rethrowException;
        throw(rethrowException);
    }
}

void QRunes::X(qubit& q)
{
	try
	{
		code << "NOT " << q.getQID() << endl;
	}
	catch (exception E)
	{
		cerr << "1" << endl;
		GateOutputException rethrowException;
		throw(rethrowException);
	}
}

/********************************************************************
Name:           RY
Description:    in ofstream output the cmd
Argin:          reference of qubit, rotation angle
Argout:         reference of qubit -> after gate
return:         n/a
********************************************************************/
void QRunes::RY(qubit& q, double angle)
{
    try
    {
        code << "RY " << q.getQID() << "," << '"' << angle << '"' << endl;
    }
    catch (exception E)
    {
        cerr << "1" << endl;
        GateOutputException rethrowException;
        throw(rethrowException);
    }
}

/********************************************************************
Name:           RZ
Description:    in ofstream output the cmd
Argin:          reference of qubit, rotation angle
Argout:         reference of qubit -> after gate
return:         n/a
********************************************************************/
void QRunes::RZ(qubit& q, double angle)
{
    try
    {
        code << "RZ " << q.getQID() << "," << '"' << angle << '"' << endl;
    }
    catch (exception E)
    {
        cerr << "1" << endl;
        GateOutputException rethrowException;
        throw(rethrowException);
    }
}

/********************************************************************
Name:           CR
Description:    in ofstream output the cmd
Argin:          reference of qubit1&2, rotation angle
Argout:         reference of qubit1&2 -> after gate
return:         n/a
********************************************************************/
void QRunes::CR(qubit& q1,qubit& q2, double angle)
{
    try
    {
        code << "CR " << q1.getQID() << "," << q2.getQID() << "," << '"' << angle << '"' << endl;
    }
    catch (exception E)
    {
        cerr << "1" << endl;
        GateOutputException rethrowException;
        throw(rethrowException);
    }
}

/********************************************************************
Name:           Toffoli
Description:    in ofstream output the cmd
Argin:          reference of qubit1&2&3
Argout:         reference of qubit1&2&3 -> after gate
return:         n/a
********************************************************************/
void QRunes::Toffoli(qubit& q1, qubit& q2, qubit& q3)
{
	try
	{
		code << "TOFFOLI " << q1.getQID() << "," << q2.getQID() << "," << q3.getQID() << endl;
	}
	catch (exception E)
	{
		cerr << "1" << endl;
		GateOutputException rethrowException;
		throw(rethrowException);
	}
}

/********************************************************************
Name:           CZ
Description:    in ofstream output the cmd
Argin:          reference of qubit1&2, rotation angle
Argout:         reference of qubit1&2 -> after gate
return:         n/a
********************************************************************/
void QRunes::Measure(qubit& q)
{
    try
    {        
        code << "MEASURE " << q.getQID() << ",$" << cRegCount << endl; 
        cRegCount++;
    }
    catch (exception E)
    {
        cerr << "1" << endl;
        GateOutputException rethrowException;
        throw(rethrowException);
    }
}

void QRunes::BEGIN_CONTROL(qubit& q)
{
    code << "CONTROL " << q.getQID() << endl;
}

void QRunes::END_CONTROL(qubit& q)
{
    code << "ENDCONTROL " << q.getQID() << endl;
}
