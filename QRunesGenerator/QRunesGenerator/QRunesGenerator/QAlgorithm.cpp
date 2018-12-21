#include"QAlgorithm.h"
#include"QR.h"
#include <iostream>
#include "QRFileController.h"

using namespace std;
//#define N 20
#define randnum randGenerator()

int shor15q()
{
    qVec qbit(12);
    qRefList qref;
    for (size_t i = 4; i < 12; i++)
    {
        qref.push_back(&qbit[i]);
    }
    X(qbit[0]);
    for (size_t i = 4; i < 12; i++)
    {
        Hadamard(qbit[i]);
    }
    BEGIN_CONTROL(qbit[4]);
    X(qbit[3]);
    X(qbit[2]);
    X(qbit[1]);
    X(qbit[0]);
    swap(qbit[1], qbit[2]);
    swap(qbit[2], qbit[3]);
    swap(qbit[0], qbit[3]);
    END_CONTROL(qbit[4]);
    BEGIN_CONTROL(qbit[5]);
    swap(qbit[0], qbit[2]);
    swap(qbit[1], qbit[3]);
    END_CONTROL(qbit[5]);
    qftreverse(qref);
    for (size_t i = 4; i < 12; i++)
    {
        Measure(qbit[i]);
    }
    return 0;
}
int shortest2(int base, size_t M)
{
    int M_length = 0;
    int j = 0;
    while (M >> (j) != 0)
    {
        j++;
    }
    M_length = j;
    qVec qbit(3 * M_length);
    qRefList target, control, anc;
    for (size_t i = 0; i < M_length; i++)
    {
        target.push_back(&qbit[i]);
    }
    for (size_t i = M_length; i < 3 * M_length; i++)
    {
        control.push_back(&qbit[i]);
    }
    Hadamardgate(control);
    size_t cqnum = control.size();
    size_t tqnum = target.size();       //a控制,b目标
#define control *control
    size_t temp = base;
    size_t temp1 = 1;
    for (size_t i = 0; i < cqnum; i++)      //C-7^(2^i)x mod M circuit
    {
        BEGIN_CONTROL(control[i]);
        temp = temp*temp1;;
        temp = temp % M;
        temp1 = temp;
        constantModMul(target, temp, M);
        END_CONTROL(control[i]);
        cout << i << endl;
    }//modexp is expressed by a series of modmult
#undef control *control
    qftreverse(control);
    measurement(control);
    return 0;
}
void modmul_913_7(qRefList a, qRefList b, int m)
{
    //c2+2+2+1+1h2+2h2h2h2h2+2+2+2+2
    copy(a, b);
    modadd(b, a, m);
    modadd(b, a, m);
    modadd(a, b, m);
    modadd(a, b, m);
    modhalf(b, m);
    modadd(b, a, m);
    modhalf(b, m);
    modhalf(b, m);
    modhalf(b, m);
    modhalf(b, m);
    modadd(b, a, m);
    modadd(b, a, m);
    modadd(b, a, m);
    modadd(b, a, m);
}
void modmul_913_49(qRefList a, qRefList b, int m)
{
    //c2+1+2+1+2+2+1+2+1h2+2h2+2+2+2+2
    copy(a, b);
    modadd(a, b, m);
    modadd(b, a, m);
    modadd(a, b, m);
    modadd(b, a, m);
    modadd(b, a, m);
    modadd(a, b, m);
    modadd(b, a, m);
    modadd(a, b, m);
    modhalf(b, m);
    modadd(b, a, m);
    modhalf(b, m);
    modadd(b, a, m);
    modadd(b, a, m);
    modadd(b, a, m);
    modadd(b, a, m);

}
void discretequantumwalkstep(qRefList a)
{
    size_t qnum = a.size();
#define a *a
    X(a.back());        //最高位为coin
    BEGIN_CONTROL(a.back());
    for (size_t j = 0; j <qnum - 2; j++)
    {
        BEGIN_CONTROL(a[j]);
    }
    for (size_t i = 0; i < qnum - 1; i++)
    {
        X(a[qnum - 2 - i]);
        if (qnum - 2 - i > 0)
        {
            END_CONTROL(a[qnum - 3 - i]);
        }
    }
    END_CONTROL(a.back());
    X(a.back());
    BEGIN_CONTROL(a.back());
    BEGIN_DAGGER();
    for (size_t j = 0; j <qnum - 2; j++)
    {
        BEGIN_CONTROL(a[j]);
    }
    for (size_t i = 0; i < qnum - 1; i++)
    {
        X(a[qnum - 2 - i]);
        if (qnum - 2 - i > 0)
        {
            END_CONTROL(a[qnum - 3 - i]);
        }
    }
    END_DAGGER();
    END_CONTROL(a.back());
#undef a *a
}
void disquantumwalk(qRefList a)
{
    size_t qnum = a.size();

    X(*a[qnum - 2]);         //初始化
    X(*a.back());
    for (size_t i = 0; i < 1 << (qnum - 1) - 1; i++)
    {
        Hadamard(*a.back());
        discretequantumwalkstep(a);
    }
}

void measurement(qRefList qref)
{
    size_t qnum = qref.size();
#define qref *qref
    for (size_t i = 0; i < qnum; i++)
    {
        Measure(qref[i]);
    }
#undef qref *qref
}
void Hadamardgate(qRefList qref)
{
    size_t qnum = qref.size();
#define qref *qref
    for (size_t i = 0; i < qnum; i++)
    {
        Hadamard(qref[i]);
    }
#undef qref *qref
}

//exp(-i*theta*sigma1sigma2....sigmaN)
void pauliZ(qRefList qref, double theta)
{
    for (auto iter = qref.begin(); iter != qref.end()-1; iter++)
    {
        CNOT(*(*iter), *(*(qref.end() - 1)));
    }
    RZ(*(*(qref.end() - 1)), 2 * theta);
    for (auto iter = qref.begin(); iter != qref.end() - 1; iter++)
    {
        CNOT(*(*iter), *(*(qref.end() - 1)));
    }
}


