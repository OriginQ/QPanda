#ifndef  _LINKEDLIST_H
#define  _LINKEDLIST_H



#include "QParamStruct.h"
#include <stack>

#define START -1

#ifdef _WIN32
#define API _declspec(dllexport)
#elif __linux__
#define API 
#endif
using std::stack;

class subQList
{
private:

    /*************************************************
    * class     subQList
    * name      ReverseNode
    * visible   no
    * arg       QNode* (first node after head)
    * return    QNode* (first node of new list)
    ***************************************************/
    QNode* ReverseNode(QNode*);

public:

    /* First node of the linked list*/
    QNode* head;

    /* QNode* cursor represents the final node*/
    QNode* cursor;

    /* level of dagger nested*/
    size_t daggerLevel;

    /*************************************************
    * class     subQList
    * default constructor
    * overload  1/2
    ***************************************************/
    subQList();

    /*************************************************
    * class     subQList
    * constructor
    * arg       size_t oldDaggerLevel
    * overload  2/2
    * note      only call when creating a new stack
    ***************************************************/
    subQList(size_t);

    /*************************************************
    * class     subQList
    * clear all contents in linkedlist
    ***************************************************/
    void subListClear();

    /*************************************************
    * class     subQList
    * name      Reverse
    * visible   yes
    * arg       n/a
    * return    n/a
    * note      Rerverse the linked list
    ***************************************************/
    void Reverse();   

    /*************************************************
    * class     subQList
    * name      Merge
    * visible   yes
    * arg       subQList* (another subQList)
    * return    n/a
    * note      Merge with another subQList
    ***************************************************/
    void Merge(subQList*);

    /*************************************************
    * class     subQList
    * name      getSize
    * visible   yes
    * arg       n/a
    * return    int (element number of this list)
    * note      Only for test
    ***************************************************/
    int getSize();
};

class QList
{

private:

    /*************************************************
    * attributes
    *
    * name      daggerStack
    * visible   no
    * note      intermidiate result for dagger and enddagger
    ***************************************************/
    stack<subQList*> daggerStack;

    /*************************************************
    * attributes
    *
    * name      controlList
    * visible   no
    * note      intermidiate result for control and endcontrol
    ***************************************************/
    vector<size_t> controlList;

    /**************************************************
    * class:       QList
    * name:        nodeInsert
    * visible:     no
    * arg:         QNode* (newly created note)
    * return:      n/a
    **************************************************/
    void nodeInsert(QNode*);

public:

    /*************************************************
    * attributes
    *
    * name      qList
    * visible   yes
    * note      the final linked list saved in it
    ***************************************************/
    subQList qList;

    /**************************************************
    * constructor
    **************************************************/
    API QList();

    /*************************************************
    * class     QList
    * clear all contents in linkedlist
    ***************************************************/
    API void listClear();

    /*************************************************
    * class:    QList
    * name      gateInsert
    * overload  1/3
    * visible   yes
    * arg       int gateSpecifier, int operand
    * return
    **************************************************/
    bool gateInsert(int, int);

    /*************************************************
    * class:    QList
    * name      gateInsert
    * overload  2/3
    * visible   yes
    * arg       int gateSpecifier, int operand1, int operand2
    * return
    ***************************************************/
    bool gateInsert(int, int, int);

    /*************************************************
    * class:    QList
    * name      gateInsert
    * overload  3/3
    * visible   yes
    * arg       int gateSpecifier, int operand1, int operand2, int operand3
    * return
    ***************************************************/
    bool gateInsert(int, int, int, int);

    /*************************************************
    * class:    QList
    * name      angleGateInsert
    * overload  1/2
    * visible   yes
    * arg       int gateSpecifier, int operand, double angle
    * return
    ***************************************************/
    bool angleGateInsert(int, int, double);

    /*************************************************
    * class:    QList
    * name      angleGateInsert
    * overload  2/2
    * visible   yes
    * arg       int gateSpecifier, int operand1, int operand2, double angle
    * return
    ***************************************************/
    bool angleGateInsert(int, int, int, double);

    /*************************************************
    * class     QList
    * name      measureInsert
    * visible   yes
    * arg       int gateSpecifier, int operand, int creg
    * return    errmsg
    ***************************************************/
    bool measureInsert(int, int, int);
    /*************************************************
    * class     QList
    * name      pmeasureInsert 
    * visible   yes
    * arg       vector<int> vecint_pmeasure_list
    * return    errmsg
    ***************************************************/
    bool pmeasureInsert(vector<int> vecint_pmeasure_list);


    /*************************************************
    * class     QList
    * name      daggerInsert
    * visible   yes
    * arg       n/a
    * return    n/a
    ***************************************************/
    void daggerInsert();

    /*************************************************
    * class     QList
    * name      daggerDelete
    * visible   yes
    * arg       n/a
    * return    errmsg
    ***************************************************/
    bool daggerDelete();

    /*************************************************
    * class     QList
    * name      ControlInsert
    * visible   yes
    * arg       int
    * return    errmsg
    ***************************************************/
    bool ControlInsert(int);

    /*************************************************
    * class     QList
    * name      ControlDelete
    * visible   yes
    * arg       int
    * return    errmsg
    ***************************************************/
    bool ControlDelete(int);    

    /*************************************************
    * class     QList
    * name      TraverseAll
    * visible   yes
    * arg       int
    * return    n/a
    * note      only for test. do a traverse and output opQubit
    ***************************************************/
    API void TraverseAll();
    
};

#endif // ! LINKEDLIST_H


