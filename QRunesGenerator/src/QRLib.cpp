#include "QR.h"
#include<iostream>
#include "QRFileController.h"
#include <numeric>
using namespace QRunes;

using namespace std;

void runQKernel(void(*kernel)())
{
    kernel();
    extern ofstream out;
    extern stringstream code;
    extern size_t cRegCount;
    extern size_t qNumMax;
    out << "%QRunes V2.0 - Powered by Origin Q" << endl;
    out << "QINIT " << qNumMax << endl;
    out << "CREG " << cRegCount << endl;
    out << code.str();
    out.close();
}

void qft(qRefList q)
{
    if (q.size() == 0)  // if q has no qubit, do nothing
    {
        return;
    }
    if (q.size() == 1)    // if q only has 1, just hadamard it
    {
        Hadamard(*q[0]);
    }
    else
    {
        qubit* lastQ = q.back();
        q.pop_back();
        qft(q);
        for (int i = 0; i < q.size(); i++)
        {
            CR(*lastQ, *(q[i]), PI / pow(2, q.size() - i));
        }
        Hadamard(*lastQ);
    }
}

void qftreverse(qRefList q)
{
    if (q.size() == 0)  // if q has no qubit, do nothing
    {
        return;
    }
    if (q.size() == 1)    // if q only has 1, just hadamard it
    {
        Hadamard(*q[0]);
    }
    else
    {
        qubit* lastQ = q.back();
        q.pop_back();
        Hadamard(*lastQ);
        for (int i = q.size()-1; i >=0 ; i--)
        {
            CR(*lastQ, *(q[i]), -PI / pow(2, q.size() - i));
        }
       
        qftreverse(q);
        
       
    }
}


void simple_qft(qRefList q,size_t setLevel)
{
	if (q.size() == 0)  // if q has no qubit, do nothing
	{
		return;
	}
	if (q.size() == 1)    // if q only has 1, just hadamard it
	{
		Hadamard(*q[0]);
	}
	else
	{
		qubit* lastQ = q.back();
		q.pop_back();
		simple_qft(q,setLevel);
		for (int i = 0; i < q.size(); i++)
		{
			if (q.size() - i - 1 >= setLevel)
			{
				continue;
			}
			CR(*lastQ, *(q[i]), PI / pow(2, q.size() - i));
		}
		Hadamard(*lastQ);
	}
}

void qAdder(qRefList a, qRefList b, qubit& z)
{
	size_t qNum = a.size();
	
#define a *a
#define b *b
	ancilla c;
	for (int i = 0; i < qNum; i++)
	{
		CNOT(a[i], b[i]);
	}
	CNOT(a[0], c);
	CNOT(a[1], a[0]);
	Toffoli(c, b[0], a[0]);
	CNOT(a[2], a[1]);
	for (int i = 0; i < qNum - 3; i++)
	{
		Toffoli(a[i], b[i + 1], a[i + 1]);
		CNOT(a[i + 3], a[i + 2]);
	}
	Toffoli(a[qNum - 3], b[qNum - 2], a[qNum - 2]);
	CNOT(a[qNum - 1], z);
	Toffoli(a[qNum - 2], b[qNum - 1], z);
	RX(b[qNum - 1]);

	for (int i = 0; i < qNum - 1; i++)
	{
		RX(b[i + 1]);
		CNOT(a[i], b[i + 1]);
	}
	RX(b[0]);
	CNOT(c, b[0]);
	Toffoli(a[qNum - 3], b[qNum - 2], a[qNum - 2]);
	for (int i = qNum - 1; i > 2; i--)
	{
		CNOT(a[i], a[i - 1]);
		RX(b[i - 1]);
		Toffoli(a[i - 3], b[i - 2], a[i - 2]);
	}
	Toffoli(c, b[0], a[0]);
	RX(b[1]);
	CNOT(a[2], a[1]);
	RX(b[0]);
	CNOT(a[1], a[0]);
	CNOT(a[0], c);
	for (int i = 0; i < qNum; i++)
	{
		CNOT(a[i], b[i]);
	}
#undef a *a
#undef b *b
}

void classical2quantum(qRefList& qList, int c)
{
	qRefList empty;
	while (c>=1)
	{
		bool digit = c % 2;
		ancilla* q=new ancilla();
		if (digit)
		{
			RX(*q);
		}
		empty.push_back(q);
		c = (c - digit) / 2;
	}	
	for (qRefList::reverse_iterator iter = empty.rbegin(); iter != empty.rend(); iter++)
	{
		qList.push_back(*iter);
	}
}


void cAdder(qRefList a, qubit& z, int c)
{
	
}

void modConstantAddition(qRefList qstate, int Module, int constant)
{
    size_t stQnum = qstate.size();
    ancilla antemp;
    size_t stN = pow(2, stQnum);


}
/*
*2018/1/11
*
*
*/
void MAJ(qubit& a, qubit& b, qubit&c)
{
    CNOT(c, b);
    CNOT(c, a);
    Toffoli(a, b, c);
}
void MAJ(qRefList a, qRefList b, qubit& in)
{
    if (a.size() != b.size())
    {
        cerr << "MAJ ERROR";
        exit(-1);
    }
    int digit = a.size();
#define a *a
#define b *b
    MAJ(in, a[0], b[0]);
    for (int i = 1; i < digit; i++)
    {
        MAJ(b[i - 1], a[i], b[i]);
    }
#undef a *a
#undef b *b
}
void UMA(qubit& a, qubit& b, qubit&c)
{
    Toffoli(a, b, c);
    CNOT(c, a);
    CNOT(a, b);
}
/*
void UMA(qRefList a, qRefList b, qubit& in)
{
if (a.size() != b.size())
{
cerr << "MAJ ERROR";
exit(-1);
}
int digit = a.size();
#define a *a
#define b *b
MAJ(in, a[0], b[0]);
for (int i = 1; i < digit; i++)
{
MAJ(b[i - 1], a[i], b[i]);
}
#undef a *a
#undef b *b
}
*/
void MAJreverse(qRefList a, qRefList b, qubit& in)
{
    if (a.size() != b.size())
    {
        cerr << "MAJ ERROR";
        exit(-1);
    }
    int digit = a.size();
#define a *a
#define b *b
    for (size_t i = digit - 1; i > 0; i--)
    {
        MAJ(b[i - 1], a[i], b[i]);
    }
    MAJ(in, a[0], b[0]);
#undef a *a
#undef b *b
}
void isCarry(qRefList a, qRefList b, qubit& q)         //是否有进位项
{
    ancilla in;
    MAJ(a, b, in);
    CNOT(*b.back(), q);
    BEGIN_DAGGER();
    MAJ(a, b, in);
    END_DAGGER();
}

void classtoQu(qRefList a, int C)
{
#define a *a
    size_t i(0);
    while (C >= 1)
    {
        if (C % 2 == 1)
        {
            RX(a[i]);
        }
        C >>= 1;
        i++;
    }
#undef a *a
}
void stateswap(qRefList a, qRefList b)
{
    size_t qnum = a.size();
    if (a.size() != b.size())
    {
        cout << "size not matched" << endl;
        return;
    }
#define a *a
#define b *b
    for (size_t i = 0; i < qnum; i++)
    {
        CNOT(a[i], b[i]);
        CNOT(b[i], a[i]);
        CNOT(a[i], b[i]);
    }
#undef a *a
#undef b *b
}
int modreverse(int c, int m)
{
    vector<int> quotient;
    int quo, remainder;
    //c = c%m;
    int m1 = m;
    quo = m / c;
    remainder = m%c;
    quotient.push_back(quo);
    if (c == 1)
    {
        return 1;
    }
    while (remainder != 1)
    {
        m = c;
        c = remainder;
        quo = m / c;
        quotient.push_back(quo);
        remainder = m%c;
    }
    if (quotient.size() == 1)
    {
        return m-quo;
    }
    if (quotient.size() == 2)
    {
        return 1 + quotient[0] * quotient[1];
    }
    int rev1(1), rev2 = quotient.back(), temp;
    for (int i = quotient.size() - 2; i > -1; i--)
    {
        rev1 = rev1 + rev2*quotient[i];
        temp = rev1;
        rev1 = rev2;
        rev2 = temp;
    }
    if (quotient.size() % 2 == 0)
    {
        return rev2;
    }
    else
    {
        return m1 - rev2;
    }

}
void constantModAdd(qRefList a, int C, int M)
{
    size_t qnum = a.size();

    ancillaVec b(qnum);
    ancilla temp;
    qRefList bf;
    for (size_t i = 0; i < qnum; i++)
    {
        bf.push_back(&b[i]);
    }
    int  x = pow(2, qnum) - 1 - M + C;
    classtoQu(bf, x);         //set b to x
    isCarry(a, bf, temp);
    BEGIN_DAGGER();
    classtoQu(bf, x);
    END_DAGGER();            //b reset to 0
    BEGIN_CONTROL(temp);         //temp =1
    classtoQu(bf, x + 1);
    qAdder(a, bf, temp);       //没有进位项
    END_CONTROL(temp);
    RX(temp);
    BEGIN_CONTROL(temp);         //temp =1
    classtoQu(bf, C);
    qAdder(a, bf, temp);       //没有进位项
    END_CONTROL(temp);         //丢弃temp
}


void constantModMul(qRefList a, int C, int M) {
    size_t qnum = a.size();
    ancillaVec b(qnum);
    qRefList bf;
    for (size_t i = 0; i < qnum; i++)
    {
        bf.push_back(&b[i]);
    }
#define a *a
    for (size_t i = 0; i < qnum; i++)
    {
        BEGIN_CONTROL(a[i]);
        int temp = C*pow(2, i);
        temp = temp%M;
        constantModAdd(bf, temp, M);
        END_CONTROL(a[i]);
    }                                         //|a>|bf>      |a>|bf+C*2^i*ai>
#undef a *a
    stateswap(a, bf);
#define a *a
    int Crev = modreverse(C, M);
    BEGIN_DAGGER();
    for (size_t i = 0; i < qnum; i++)
    {
        BEGIN_CONTROL(a[i]);
        int temp = Crev*pow(2, i);
        temp = temp%M;
        constantModAdd(bf, temp, M);
        END_CONTROL(a[i]);
    }                                         //|a>|bf>      |a>|bf+C*2^i*ai>

#undef a *a
}
void constModExp(qRefList a, qRefList b, int c, int m)
{
    size_t cqnum = a.size();
    size_t tqnum = b.size();       //a控制,b目标
#define a *a
    for (size_t i = 0; i < cqnum; i++)
    {
        BEGIN_CONTROL(a[i]);
        int temp = c*pow(2, i);
        temp = temp%m;
        constantModMul(b, temp, m);
        END_CONTROL(a[i]);
    }
#undef a *a
}
/*
*another way
*contains x0--xx,xy--(x+y mod m)y,xy--(x-y mod m)y,x--(-x)mod m,x--2x mod m,x--x/2 mod m
*
*/
void copy(qRefList a, qRefList b)        //|a>|0>   ->   |a>|a>
{
    size_t dim = a.size();
#define a *a
#define b *b
    for (size_t i = 0; i < dim; i++)
    {
        CNOT(a[i], b[i]);
    }
#undef a *a
#undef b *b
}
/*
*加法，和保存在a，不考虑进位项
*
*/
void adder(qRefList a, qRefList b)
{
    size_t dim = a.size();
    ancilla temp;
#define a *a
#define b *b
    MAJ(temp, a[0], b[0]);
    for (size_t i = 0; i < dim - 1; i++)
    {
        MAJ(b[i], a[i + 1], b[i + 1]);
    }
    for (size_t i = dim - 2; i > 0; i--)
    {
        UMA(b[i], a[i + 1], b[i + 1]);
    }
    UMA(b[0], a[1], b[1]);
    UMA(temp, a[0], b[0]);
#undef a *a
#undef b *b
}//checked
/*
*加法，考虑进位项
*
*/
void adder(qRefList a, qRefList b, qubit& c)
{
    size_t dim = a.size();
    ancilla temp;
#define a *a
#define b *b
    MAJ(temp, a[0], b[0]);
    for (size_t i = 0; i < dim - 1; i++)
    {
        MAJ(b[i], a[i + 1], b[i + 1]);
    }
    CNOT(b[dim - 1], c);
    for (size_t i = dim - 2; i > 0; i--)
    {
        UMA(b[i], a[i + 1], b[i + 1]);
    }
    UMA(b[0], a[1], b[1]);
    UMA(temp, a[0], b[0]);
#undef a *a
#undef b *b
}
void constadder(qRefList a, int c)
{
    size_t qnum = a.size();
    ancillaVec b(qnum);
    qRefList bf;
    for (size_t i = 0; i < qnum; i++)
    {
        bf.push_back(&b[i]);
    }
    classtoQu(bf, c);
    adder(a, bf);
    classtoQu(bf, c);
}
void constadder(qRefList a, qubit& s, int c)  //考虑进位
{
    size_t qnum = a.size();
    ancillaVec b(qnum);
    qRefList bf;
    for (size_t i = 0; i < qnum; i++)
    {
        bf.push_back(&b[i]);
    }
    classtoQu(bf, c);
    adder(a, bf,s);
}
/*
*先将c赋值到b
*
*/
void constadder(qRefList a, qRefList b, int c)
{
    size_t qnum = a.size();
    classtoQu(b, c);
    adder(a, b);
    classtoQu(b, c);
}
void constadder(qRefList a, qRefList b, qubit& s, int c)
{
    size_t qnum = a.size();
    classtoQu(b, c);
    adder(a, b,s);
    classtoQu(b, c);
}
/*
*  |x> --> |-x mod m>
*
*/
void modnot(qRefList a, int m)
{
    size_t dim = a.size();
#define a *a
    for (size_t i = 0; i < dim; i++)
    {
        RX(a[i]);         //取反
    }
#undef a *a
    constadder(a, m + 1);
}
void modadd(qRefList a, qRefList b, int m)       //|a>|b>   ->   |a+b>|b mod m>
{
    size_t qnum = a.size();
    ancilla temp;
    ancillaVec c(qnum);
    qRefList cf;
    for (size_t i = 0; i < qnum; i++)
    {
        cf.push_back(&c[i]);
    }
    //classtoQu(cf, (1<<qnum)-m);
   // isCarry(a, b, temp);
    adder(a, b, temp);
    BEGIN_CONTROL(temp);
    constadder(a, cf,(1 << qnum) - m);
    END_CONTROL(temp);
    
    classtoQu(cf, (1 << qnum) - m);
    isCarry(a, cf, temp);
    BEGIN_CONTROL(temp);
    adder(a, cf);
    END_CONTROL(temp);
    classtoQu(cf, (1 << qnum) - m);
    
}
void constcomparator(qRefList a, qRefList b,qubit& s, int c)  //a>c时，s为|1>
{
    size_t qnum = a.size();
    classtoQu(b, (1<<qnum)-c-1);
    isCarry(a, b, s);                   //s表示进位
    classtoQu(b, c);                    //b是辅助比特，置回原位
}
void modsub(qRefList a, qRefList b, int m)       //|a>|b>   ->   |a-b>|b mod m>
{
    size_t qnum = a.size();
    modnot(b, m);
    modadd(a, b, m);
}
void swap(qubit& a, qubit& b)
{
    CNOT(a, b);
    CNOT(b, a);
    CNOT(a, b);
}
void moddouble(qRefList a, int m)
{
    size_t qnum = a.size();
    ancilla temp;
    ancillaVec c(qnum);
    qRefList cf;
    for (size_t i = 0; i < qnum; i++)
    {
        cf.push_back(&c[i]);
    }
    constcomparator(a, cf, temp, m/2);

    BEGIN_CONTROL(temp);
    constadder(a, cf, (1 << qnum) - m / 2 - 1);
    END_CONTROL(temp);
#define a *a
#define cf *cf
    for (size_t i = qnum - 1; i > 0; i--)
    {
        swap(a[i], a[i - 1]);
    }
    CNOT(temp, a[0]);
    CNOT(a[0], temp);
#undef a *a
#undef cf *cf
}//待检查
void modhalf(qRefList a, int m)
{
    size_t qnum = a.size();
#define a *a
    for (size_t i = 0; i < qnum-1; i++)
    {
        swap(a[i], a[i + 1]);
    }
    ancilla temp;
    BEGIN_CONTROL(a[qnum - 1]);  //|a>为奇数
    RX(temp);
    END_CONTROL(a[qnum - 1]);
    BEGIN_CONTROL(temp);
    RX(a[qnum - 1]);
    //CNOT(temp, a[qnum - 1]);   //若最高位为|1>,则置为|0>
#undef a *a
    //BEGIN_CONTROL(temp);
    constadder(a, m / 2 + 1);
    END_CONTROL(temp);
}//checked

void quantumredpacketnew(qRefList a, vector<double> &b)
{
    size_t qnum = a.size();
    size_t stnum = b.size();
    if ((1 << qnum) != stnum)
    {
        cout << "not matched" << endl;
        return;
    }
    double sum = 0;
    for (auto iter = b.begin(); iter < b.end(); iter++)
    {
        sum += *iter;
    }
    if (abs(1 - sum) > 1e-6)
    {
        cout << "not uniformed" << endl;
        return;
    }
    double denominator, numerator, theta;
    denominator = 0;
#define a *a
    for (size_t i = qnum; i > 0; i--)       //作用在第i个比特
    {
        for (size_t k = 0; k < (1 << (qnum - i)); k++)       //第i个比特需要1<<(n-i)个受控RY门
        {

            denominator = 0;
            numerator = 0;
            theta = 0;
            for (size_t j = k << i; j < (k << i) + (1 << i); j++)
            {
                denominator += b[j];
            }
            for (size_t j = k << i; j < (k << i) + (1 << (i - 1)); j++)
            {
                numerator += b[j];
            }
            theta = 2 * acos(sqrt(numerator) / sqrt(denominator));
            for (size_t j = 0; j < qnum - i; j++)
            {
                if ((k >> j) % 2 == 0)
                {
                    RX(a[i + j]);
                }
            }
            for (size_t j = 0; j < qnum - i; j++)
            {
                BEGIN_CONTROL(a[i + j]);
            }
            RY(a[i - 1], theta);
            for (size_t j = 0; j <qnum-i;j++)
            {
                END_CONTROL(a[i+j]);
            }
            for (size_t j = 0; j < qnum - i; j++)
            {
                if ((k >> j) % 2 == 0)
                {
                    RX(a[i + j]);
                }
            }//复位
        }
    }
#undef a *a
}

void quantumredpacket(qRefList a, vector<double> &b)
{
    size_t qnum = a.size();
    double temp1, temp2,temp3;
    temp1 = b[0] + b[1] + b[2] + b[3];
    temp2 = b[0] + b[1] + b[4] + b[5];
    temp3 = b[0] + b[1] + b[2] + b[3];
    double theta = 2*acos(sqrt(temp1));
#define a *a
    theta = 2 * acos(sqrt(temp1));
    RY(a[2], theta);
    CNOT(a[2], a[1]);
    CNOT(a[2], a[0]);
    //sqrt(b0+b1+b2+b3)|000>+sqrt(b4+b5+b6+b7)|111>
    temp2 = b[0] + b[1];
    theta = 2 * acos(sqrt(temp2)/sqrt(temp1));
    RX(a[2]);
    BEGIN_CONTROL(a[2]);
    RY(a[1], theta);
    END_CONTROL(a[2]);
    RX(a[2]);
    //|000>    |000>+|010>
    temp1 = 1 - temp1;
    temp2 = b[4] + b[5];
    theta = 2 * asin(sqrt(temp2) / sqrt(temp1));
    BEGIN_CONTROL(a[2]);
    RY(a[1], -theta);
    END_CONTROL(a[2]);
    //|111>    |111>+|101>

    temp1 = b[0] + b[1];
    temp2 = b[0];
    RX(a[2]);
    RX(a[1]);
    theta= 2 * acos(sqrt(temp2)/sqrt(temp1));
    BEGIN_CONTROL(a[2]);
    BEGIN_CONTROL(a[1]);
    RY(a[0], theta);
    END_CONTROL(a[1]);
    END_CONTROL(a[2]);
    RX(a[2]);
    RX(a[1]);
    //|000>    |000>+|001>
    
    RX(a[2]);
    temp1 = b[2] + b[3];
    temp2 = b[2];
    theta = 2 * acos(sqrt(temp2) / sqrt(temp1));
    BEGIN_CONTROL(a[2]);
    BEGIN_CONTROL(a[1]);
    RY(a[0], theta);
    END_CONTROL(a[1]);
    END_CONTROL(a[2]);
    //|010>   |010>+|011>
    RX(a[2]);
    
    temp1 = b[6] + b[7];
    temp2 = b[6];
    theta = 2 * asin(sqrt(temp2) / sqrt(temp1));
    BEGIN_CONTROL(a[2]);
    BEGIN_CONTROL(a[1]);
    RY(a[0], -theta);
    //RY(a[0], theta);
    END_CONTROL(a[1]);
    END_CONTROL(a[2]);
    
    //|111>    |111>+|110>
    
    RX(a[1]);
    temp1 = b[4] + b[5];
    temp2 = b[4];
    theta = 2 * asin(sqrt(temp2) / sqrt(temp1));
    BEGIN_CONTROL(a[2]);
    BEGIN_CONTROL(a[1]);
    RY(a[0], -theta);
    END_CONTROL(a[1]);
    END_CONTROL(a[2]);
    //|101>    |101>+|100>
    RX(a[1]);
    
#undef a *a

}
