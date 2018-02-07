#include "LinkedListController.h"
#include <algorithm>
#include <iostream>
#include "parser.h"

/**************************************************
 * constructor
 **************************************************/
QList::QList()
{    
    /* empty */
}

/*************************************************
* class     QList
* clear all contents in linkedlist
***************************************************/
void QList::listClear()
{
    this->qList.subListClear();
}

/**************************************************
 * class:       QList
 * name:        nodeInsert
 * visible:     no
 * arg:         QNode* (newly created note)
 * return:      n/a
 **************************************************/
void QList::nodeInsert(QNode* newGateNode)
{   
    // if it is not a measure node, assign the controlList to it
    if (newGateNode->gateSpecifier != MEASURE_GATE)
    {
        ((GateNode*)newGateNode)->controlList.assign(this->controlList.begin(), this->controlList.end());
    }
    // if true, that means handling the root list
    if (daggerStack.empty())
    {
        this->qList.cursor->next = newGateNode;
        this->qList.cursor = newGateNode;
    }
    else
    {
        if (newGateNode->gateSpecifier != MEASURE_GATE
			&&
			newGateNode->gateSpecifier != PMEASURE_GATE
			)
		{
			((GateNode*)newGateNode)->isDagger =
				daggerStack.top()->daggerLevel%2 == 0 ? true : false;
		}
        daggerStack.top()->cursor->next = newGateNode;
        daggerStack.top()->cursor = newGateNode;        
    }   
}

/*************************************************
 * class:    QList
 * name      gateInsert
 * overload  1/3
 * visible   yes
 * arg       int gateSpecifier, int operand
 * return   
 **************************************************/
bool QList::gateInsert(int gateSpecifier, int operand)
{
    SingleGateNode *newGateNode = new SingleGateNode();
    if (newGateNode == NULL)
    {
        return false;
    }
    // init the parameters
    newGateNode->gateSpecifier = gateSpecifier;
    newGateNode->next = NULL;
    newGateNode->opQubit = operand;
    nodeInsert(newGateNode);
    return true;
}

/*************************************************
* class:    QList
* name      gateInsert
* overload  2/3
* visible   yes
* arg       int gateSpecifier, int operand1, int operand2
* return
***************************************************/
bool QList::gateInsert(int gateSpecifier, int operand1, int operand2)
{
    DoubleGateNode *newGateNode = new DoubleGateNode();
    if (newGateNode == NULL)
    {
        return false;
    }

    // init the parameters
    newGateNode->gateSpecifier = gateSpecifier;
    newGateNode->next = NULL;
    newGateNode->opQubit1 = operand1;
    newGateNode->opQubit2 = operand2;
    nodeInsert(newGateNode);
    return true;
}

/*************************************************
* class:    QList
* name      gateInsert
* overload  3/3
* visible   yes
* arg       int gateSpecifier, int operand1, int operand2, int operand3
* return
***************************************************/
bool QList::gateInsert(int gateSpecifier, int operand1, int operand2, int operand3)
{
    TripleGateNode *newGateNode = new TripleGateNode();
    if (newGateNode == NULL)
    {
        return false;
    }

    // init the parameters
    newGateNode->gateSpecifier = gateSpecifier;
    newGateNode->next = NULL;
    newGateNode->opQubit1 = operand1;
    newGateNode->opQubit2 = operand2;
    newGateNode->opQubit3 = operand3;
    nodeInsert(newGateNode);
    return true;
}

/*************************************************
* class:    QList
* name      angleGateInsert
* overload  1/2
* visible   yes
* arg       int gateSpecifier, int operand, double angle
* return
***************************************************/
bool QList::angleGateInsert(int gateSpecifier, int operand, double angle)
{
    SingleAngleGateNode *newGateNode = new SingleAngleGateNode();
    if (newGateNode == NULL)
    {
        return false;
    }

    // init the parameters
    newGateNode->gateSpecifier = gateSpecifier;
    newGateNode->next = NULL;
    newGateNode->opQubit = operand;
    newGateNode->angle = angle;
    nodeInsert(newGateNode);
    return true;
}

/*************************************************
* class:    QList
* name      angleGateInsert
* overload  2/2
* visible   yes
* arg       int gateSpecifier, int operand1, int operand2, double angle
* return    errmsg
***************************************************/
bool QList::angleGateInsert(int gateSpecifier, int operand1, int operand2, double angle)
{
    DoubleAngleGateNode *newGateNode = new DoubleAngleGateNode();
    if (newGateNode == NULL)
    {
        return false;
    }

    // init the parameters
    newGateNode->gateSpecifier = gateSpecifier;
    newGateNode->next = NULL;
    newGateNode->opQubit1 = operand1;
    newGateNode->opQubit2 = operand2;
    newGateNode->angle = angle;
    nodeInsert(newGateNode);
    return true;
}

/*************************************************
* class     QList
* name      measureInsert
* visible   yes
* arg       int gateSpecifier, int operand, int creg
* return    errmsg
***************************************************/
bool QList::measureInsert(int gateSpecifier,int operand, int creg)
{
    MeasureNode *newGateNode = new MeasureNode();
    if (newGateNode == NULL)
    {
        return false;
    }

    newGateNode->gateSpecifier = gateSpecifier;
    newGateNode->next = NULL;
    newGateNode->opQubit = operand;
    newGateNode->creg = creg;

    if (this->daggerStack.size()!=0 || this->controlList.size()!=0)
    {
        return false;
    }
    else
    {
        if (this->qList.cursor->next == NULL)
        {
            this->qList.cursor->next = newGateNode;
            this->qList.cursor = newGateNode;
            return true;
        }
        else
        {
            return false;
        }
    }
}

/*************************************************
* class     QList
* name      pmeasureInsert
* visible   yes
* arg       vector<int> vecint_pmeasure_list
* return    errmsg
***************************************************/
bool QList::pmeasureInsert(vector<int> vecint_pmeasure_list)
{
    pMeasureNode *newGateNode = new pMeasureNode();
    if (newGateNode == NULL)
    {
        return false;
    }

    newGateNode->gateSpecifier = PMEASURE_GATE;
    newGateNode->next = NULL;
    newGateNode->vecint_pmeasure_list.assign(vecint_pmeasure_list.begin(),
        vecint_pmeasure_list.end());

    if (this->daggerStack.size() != 0 || this->controlList.size() != 0)
    {
        return false;
    }
    else
    {
        if (this->qList.cursor->next == NULL)
        {
            this->qList.cursor->next = newGateNode;
            this->qList.cursor = newGateNode;
            return true;
        }
        else
        {
            return false;
        }
    }
}

/*************************************************
* class     QList
* name      daggerInsert
* visible   yes
* arg       n/a
* return    n/a
***************************************************/
void QList::daggerInsert()
{
    //  if true, that means handling the root list
    if (this->daggerStack.empty())
    {
        subQList* newQList = new subQList(1);
        daggerStack.push(newQList);
    }
    else
    {
        subQList* newQList = new subQList(this->daggerStack.top()->daggerLevel);
        daggerStack.push(newQList);
    }
}

/*************************************************
* class     QList
* name      daggerDelete
* visible   yes
* arg       n/a
* return    errmsg
***************************************************/
bool QList::daggerDelete()
{
    using std::cout;

    // if true, that means handling the root list, so enddagger is illegal
    if (daggerStack.empty())
        return false;

    subQList* topQList = this->daggerStack.top();
    daggerStack.pop();

    // if true, that means handling the root list
    if (daggerStack.empty())
    {
        topQList->Reverse();
        this->qList.Merge(topQList);
    }
    else
    {
        // if true, dagger -> reverse
        // if not,  dagger dagger -> do nothing
        if (topQList->daggerLevel % 2 == 1)
        {
            topQList->Reverse();
        }        
        daggerStack.top()->Merge(topQList);
    }
    return true;
}

/*************************************************
* class     QList
* name      ControlInsert
* visible   yes
* arg       int
* return    errmsg
***************************************************/
bool QList::ControlInsert(int operand)
{
    // if there is duplicate control operand, that's illegal
    if (std::count(controlList.begin(), controlList.end(), operand) >= 1)

    {
        return false;
    }
    else
    {
        controlList.push_back(operand);
        return true;
    }
}

/*************************************************
* class     QList
* name      ControlDelete
* visible   yes
* arg       int
* return    errmsg
***************************************************/
bool QList::ControlDelete(int operand)
{
    // if there not existed, that's illegal
    if (std::count(controlList.begin(), controlList.end(), operand) == 0)
    {
        return false;
    }
    else
    {
        // iterator traverse. when finded, delete and break the loop
        for (vector<size_t>::iterator iter = controlList.begin(); iter != controlList.end(); iter++)
        {
            if ((*iter) == operand)
            {
                controlList.erase(iter);
                break;
            }
        }
    }
    return true;
}

/*************************************************
* class     QList
* name      TraverseAll
* visible   yes
* arg       int
* return    n/a
* note      only for test. do a traverse and output opQubit
***************************************************/
void QList::TraverseAll()
{
    QNode *ptQNode = this->qList.head->next;
    while (ptQNode != NULL)
    {
        SingleGateNode* sptQNode=(SingleGateNode*)ptQNode;
        std::cout << sptQNode->opQubit << " "
            << (sptQNode->isDagger == true ? 1 : -1) << " " << std::endl;
       
        ptQNode = ptQNode->next;
        getchar();
    }
}

/*************************************************
* class     subQList
* default constructor
* overload  1/2
***************************************************/
subQList::subQList()
{
    QNode* headNode = new QNode();
    headNode->gateSpecifier = START;
    headNode->next = NULL;
    head = headNode;
    cursor = head;
    daggerLevel = 0;
}

/*************************************************
* class     subQList
* constructor
* arg       size_t oldDaggerLevel
* overload  2/2
* note      only call when creating a new stack
***************************************************/
subQList::subQList(size_t oldDaggerLevel)
{
    QNode* headNode = new QNode();
    headNode->gateSpecifier = START;
    headNode->next = NULL;
    head = headNode;
    cursor = head;
    daggerLevel = oldDaggerLevel + 1;
}

/*************************************************
* class     subQList
* clear all contents in linkedlist
***************************************************/
void subQList::subListClear()
{
    QNode* thisNode = this->head;
    QNode* nextNode = NULL;
    while (NULL != thisNode)
    {
        nextNode = thisNode->next;
        delete(thisNode);
        thisNode = nextNode;
    }
}

/*************************************************
* class     subQList
* name      Reverse
* visible   yes
* arg       n/a
* return    n/a
* note      Rerverse the linked list
***************************************************/
void subQList::Reverse()
{    
    this->head->next = ReverseNode(this->head->next);
}

/*************************************************
* class     subQList
* name      Reverse
* visible   no
* arg       QNode* (first node after head)
* return    QNode* (first node of new list)
***************************************************/
QNode* subQList::ReverseNode(QNode* firstNode)
{
    QNode* newh = NULL;
    for (QNode* p = firstNode; p; )
    {
        QNode* tmp = p->next;
        p->next = newh;
        newh = p;
        p = tmp;
    }
    return newh;
}

/*************************************************
* class     subQList
* name      Merge
* visible   yes
* arg       subQList* (another subQList)
* return    n/a
* note      Merge with another subQList
***************************************************/
void subQList::Merge(subQList* origin)
{
    cursor->next = origin->head->next;       

    while (cursor->next != NULL)
    {
        cursor = cursor->next;
    }
}

/*************************************************
* class     subQList
* name      getSize
* visible   yes
* arg       n/a
* return    element number of this list
* note      Only for test
***************************************************/
int subQList::getSize()
{
    QNode *temp = head->next;
    int i = 0;
    while (temp != NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}


