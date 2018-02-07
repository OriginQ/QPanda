/*********************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-10
Description:ring memory management and memory management
*********************************************************************************************************/
#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <mutex>
#include <Windows.h>
using namespace std;
using std::list;

/*****************************************************************************************************************
Memory:memory management
*****************************************************************************************************************/
class Memory
{
private:
    HANDLE mMuxtex;                                                     /* memory mutex                         */
    char  *mpMemory;                                                    /* memory pointer                       */
    bool   bIsRead;                                                     /* memory is read                       */

public:
    /*************************************************************************************************************
    Name:        Memory
    Description: initialize memory class
    Argin:       memorySize   memory size
    Argout:      None
    return:      None
    *************************************************************************************************************/
    Memory(size_t memorySize);
    /*************************************************************************************************************
    Name:        ~Memory
    Description: destruct memory class
    Argin:       memorySize   memory size
    Argout:      None
    return:      None
    *************************************************************************************************************/
    ~Memory();

    /*************************************************************************************************************
    Name:        setMemory
    Description: set memory
    Argin:       pIn      external memory space pointer
                 stSize   external memory space size
                 vControl control qbit vector
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool setMemory(char *pIn, size_t stSize, vector<size_t> &vControl);
    /*************************************************************************************************************
    Name:        getMemory
    Description: get memory value
    Argin:       pOut         external memory space pointer
                 stMemorySize memory size
    Argout:      pOut         external memory space pointer
    return:      true or false
    *************************************************************************************************************/
    bool getMemory(void *pOut, size_t stMemorySize);
};

/*****************************************************************************************************************
RingMemory:ring memory management
*****************************************************************************************************************/
class RingMemory
{
    typedef list<Memory * > LISTMEMORY;
private:
    list<Memory * >      mMemoryList;
    size_t               mListSize;
    LISTMEMORY::iterator mListWrite;
    LISTMEMORY::iterator mListRead;

public:
    size_t               mMemorySize;

public:
    /*************************************************************************************************************
    Name:        RingMemory
    Description: initialize ring memory class
    Argin:       listSize     ring list size
                 stmemorySize   memory size
    Argout:      None
    return:      None
    *************************************************************************************************************/
    RingMemory(size_t listSize, size_t stmemorySize);
    /*************************************************************************************************************
    Name:        ~RingMemory
    Description: destruct ring memory class
    Argin:       None
    Argout:      None
    return:      None
    *************************************************************************************************************/
    ~RingMemory();
    /*************************************************************************************************************
    Name:        getMemory
    Description: get memory value
    Argin:       pOut    external memory space pointer
    Argout:      pOut    external memory space pointer
    return:      true or false
    *************************************************************************************************************/
    bool getMemory(void *pOut);
    /*************************************************************************************************************
    Name:        setMemory
    Description: set value to memory
    Argin:       pIn      external memory space pointer
                 stSize   external memory space size
                 vControl control qbit vector
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool setMemory(char *pIn, size_t stSize, vector<size_t> &vControl);

private:
    RingMemory();




};