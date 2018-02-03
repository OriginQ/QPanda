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