#pragma once

#include "QRState.h"

void runQKernel(void(*)());

void qft(qRefList);
void qftreverse(qRefList q);

void simple_qft(qRefList q, size_t setLevel=3);

void classical2quantum(qRefList& qList, int c);

void qAdder(qRefList a, qRefList b, qubit& z);

void cAdder(qRefList a, qubit& z, int c);
/*
*
*  2018/1/11
*/
void MAJ(qubit& a, qubit& b, qubit&c);
void MAJ(qRefList a, qRefList b, qubit& in);
void UMA(qubit& a, qubit& b, qubit&c);
void MAJreverse(qRefList a, qRefList b, qubit& in);
void isCarry(qRefList a, qRefList b, qubit& q);
void classtoQu(qRefList a, int C);
void stateswap(qRefList a, qRefList b);
int modreverse(int c, int m);
void constantModAdd(qRefList a, int C, int M);
void constantModMul(qRefList a, int C, int M);
void constModExp(qRefList a, qRefList b, int c, int m);
void copy(qRefList a, qRefList b);
void adder(qRefList a, qRefList b);
void adder(qRefList a, qRefList b, qubit& c);
void constadder(qRefList a, int c);//不考虑进位
void constadder(qRefList a, qRefList b, int c);//不考虑进位
void constadder(qRefList a, qubit& b, int c);//考虑进位
void constadder(qRefList a, qRefList b, qubit& s, int c);
void modnot(qRefList a, int m);
void modadd(qRefList a, qRefList b, int m);
void modsub(qRefList a, qRefList b, int m);
void moddouble(qRefList a, int m);
void modhalf(qRefList a, int m);
void swap(qubit& a, qubit& b);
void quantumredpacket(qRefList a, vector<double> &b);
void quantumredpacketnew(qRefList a, vector<double> &b);





