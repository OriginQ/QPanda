#pragma once
#include <vector>
using std::vector;

#ifndef PI
#define PI 3.14159
#endif

class qubit
{
private:
    static bool qInit;    
    size_t qID;
protected:
    static size_t qNum;
    static size_t qNumMax;
public:
    qubit();
    virtual ~qubit();
    size_t getQID();

    // To be done
    /*
    qubit& operator+(qubit&);
    void operator++();
    void operator--();
    qubit operator+=(qubit&);
    */
};

class ancilla :public qubit
{
public:
    ancilla();
    ~ancilla();
};

typedef vector<qubit> qVec;
typedef vector<ancilla> ancillaVec;

#define QREF_OLD_SCHEME 1

#ifdef QREF_OLD_SCHEME

typedef vector<qubit*> qRefList;

#else
class qRefList
{
private:
	vector<qubit*> ptList;
	
public:
	size_t size();
	qubit& operator[](size_t);
	qRefList(size_t);
	qRefList();
};
#endif

