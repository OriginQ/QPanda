#ifndef _QPARAM_H
#define _QPARAM_H

#include <vector>
using std::vector;

using std::size_t;
enum QGATE
{
    HADAMARD_GATE = 1,
    RX_GATE,
    RY_GATE,
    RZ_GATE,
    NOT_GATE,
    TOFFOLI_GATE,
    RESET_GATE,
    CR_GATE,
    ISWAP_GATE,
    SQISWAP_GATE,
    CNOT_GATE,
    MEASURE_GATE,
    PMEASURE_GATE,
    END

};

/*************************************************
* struct
* name      QNode
* note      Base Struct
* attributes
*
* 1. int gateSpecifier. as defined in parser.h
*  HADAMARD_GATE           1
*  RX_GATE                 2
*  RY_GATE                 3
*  RZ_GATE                 4
*  NOT_GATE                5
*  TOFFOLI_GATE            6
*  CR_GATE                 7
*  ISWAP_GATE              8
*  SQISWAP_GATE            9
*  CNOT_GATE               10
*  MEASURE_GATE            11
*  END                     12
* by the way
* #define START                   -1
* this represents the first node of linked lists
*
* 2. QNode* next. as it's a linked list
*
***************************************************/
struct QNode
{
    int gateSpecifier;
    QNode *next;
};

/*************************************************
* struct
* name      GateNode
* note      Base Struct for all gate node
* attributes
*
* 1. bool isDagger.
*    if true, call dagger version of the simulation api
*
* 2. vector<size_t> controlList.
*    save the controller qubit
*
***************************************************/
struct GateNode : public QNode
{
    bool isDagger;
    vector<size_t> controlList;
};

/*************************************************
* struct
* name      SingleGateNode
* note
*       Name        gateSpecifier
*       Hadamard    HADAMARD_GATE(1)
*       NOT         NOT_GATE(5)
*
* attributes
* 1.  int gateSpecifier
* 2.  QNode* next
* 3.  bool isDagger
* 4.  vector<size_t> controlList
* 5.  int opQubit
*
***************************************************/
struct SingleGateNode : public GateNode
{
    int opQubit;
};

/*************************************************
* struct
* name      SingleAngleGateNode
* note
*       Name        gateSpecifier
*       RX          RX_GATE(2)
*       RY          RY_GATE(3)
*       RZ          RZ_GATE(4)
*
* attributes
*
* 1.  int gateSpecifier
* 2.  QNode* next
* 3.  bool isDagger
* 4.  vector<size_t> controlList
* 5.  int opQubit
* 6.  double angle
*
***************************************************/
struct SingleAngleGateNode : public GateNode
{
    int opQubit;
    double angle;
};

/*************************************************
* struct
* name      DoubleGateNode
* note
*       Name        gateSpecifier
*       CNOT        CNOT_GATE(10)
*       SQISWAP     SQISWAP_GATE(9)
*
* attributes
*
* 1.  int gateSpecifier
* 2.  QNode* next
* 3.  bool isDagger
* 4.  vector<size_t> controlList
* 5.  int opQubit1
* 6.  int opQubit2
*
***************************************************/
struct DoubleGateNode : public GateNode
{
    int opQubit1;
    int opQubit2;
};

/*************************************************
* struct
* name      DoubleAngleGateNode
* note
*       Name        gateSpecifier
*       ISWAP       ISWAP_GATE(7)
*
* attributes
*
* 1.  int gateSpecifier
* 2.  QNode* next
* 3.  bool isDagger
* 4.  vector<size_t> controlList
* 5.  int opQubit1
* 6.  int opQubit2
* 7.  double angle
*
***************************************************/
struct DoubleAngleGateNode : public GateNode
{
    int opQubit1;
    int opQubit2;
    double angle;
};

/*************************************************
* struct
* name      TripleGateNode
* note
*       Name        gateSpecifier
*       TOFFLOLI    TOFFOLI_GATE(7)
*
* attributes
*
* 1.  int gateSpecifier
* 2.  QNode* next
* 3.  bool isDagger
* 4.  vector<size_t> controlList
* 5.  int opQubit1
* 6.  int opQubit2
* 7.  int opQubit3
*
***************************************************/
struct TripleGateNode : public GateNode
{
    int opQubit1;
    int opQubit2;
    int opQubit3;
};

/*************************************************
* struct
* name      MeasureNode
* note
*       Name        gateSpecifier
*       MEASURE     MEASURE_GATE(13)
*
* attributes
*
* 1.  int gateSpecifier
* 2.  QNode* next
* 3.  int opQubit
* 4.  int creg
*
***************************************************/
struct MeasureNode :public QNode
{
    int opQubit;
    int creg;
};
/*************************************************
* struct
* name      pMeasureNode
* note
*       Name        gateSpecifier
*       MEASURE     pMEASURE_GATE(16)
*
* attributes
*
* 1.  int gateSpecifier
* 2.  QNode* next
* 3.  vector<int> vecint_pmeasure_list;
*
***************************************************/
struct pMeasureNode :public QNode
{
    vector<size_t> vecint_pmeasure_list;
};
#endif // !QPARAMSTRUCT
