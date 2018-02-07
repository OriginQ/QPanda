/*********************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-23
Description: quantum system command
*********************************************************************************************************/
#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <functional>
#include <complex>
#include "../QRunesParser/QParamStruct.h"
#include "../QPandaAPI/QPandaAPI.h"
#include "../QuantumCloudHTTP/VirtualQCHttp.h"

using namespace std;
using std::function;
using std::map;

typedef vector< complex<double> > QState;
typedef  pair < string, function<void()>> FPAIR;

#define QPROGCLASS   QPanda::QPandaAPI
/*****************************************************************************************************************
  QCommand:the parent of Command class
*****************************************************************************************************************/
class QCommand
{
public:
     ~QCommand(){}
     inline QCommand()
     {
     }
     /*************************************************************************************************************
     Name:        action
     Description: Comannd action
     Argin:       ssAction  action name
     Argout:      None
     return:      true or false
     *************************************************************************************************************/
     virtual bool action(stringstream & ssAction, QPROGCLASS * pParserProg) { return true; };

    /*************************************************************************************************************
     Name:        action
     Description: Comannd action
     Argin:       ssAction  action name
     Argout:      None
     return:      true or false
     *************************************************************************************************************/
     virtual bool action(stringstream & ssAction, VirtualQCHttp * pQCHttp) {return true;};

    /*************************************************************************************************************
    Name:        description
    Description: description Command
    Argin:       None
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    virtual void description() = 0;

public:

    string  mComand;                                                    /* Command name                         */
};

/*****************************************************************************************************************
  QCommandSelectMode:select command
*****************************************************************************************************************/
class QCommandSelectMode :public QCommand
{
public:
    inline QCommandSelectMode()
    {
        mComand = "mode";                                               /* set command name                     */
        mFunction.insert(FPAIR("-help", [this]() {this->description(); }));
    }
    /*************************************************************************************************************
    Name:        action
    Description: Comannd action
    Argin:       ssAction  action name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool action(stringstream & ssAction,QPROGCLASS * pParserProg);
    /*************************************************************************************************************
    Name:        description
    Description: description Command
    Argin:       None
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    void description();
private:
    map<string, function<void()> > mFunction;
};

/*****************************************************************************************************************
  QCommandLoadFile:load file
*****************************************************************************************************************/
class QCommandLoadFile :public QCommand
{
public:
    inline QCommandLoadFile()
    {
        mComand = "load";                                               /* set command name                     */
        mFunction.insert(FPAIR("-help", [this]() {this->description(); }));
    }
    /*************************************************************************************************************
    Name:        action
    Description: Comannd action
    Argin:       ssAction  action name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool action(stringstream & ssAction,QPROGCLASS * pParserProg);
    /*************************************************************************************************************
    Name:        description
    Description: description Command
    Argin:       None
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    void description();
private:
    map<string, function<void()> > mFunction;
};

/*****************************************************************************************************************
  QCommandRun:run quantum program
*****************************************************************************************************************/
class  QCommandRun :public QCommand
{
    #define CPU 1
    #define GPU 2
    typedef  pair < string, function<void(int)>> RUNFPAIR;
public:
    inline QCommandRun()
    {
        mComand = "run";                                                /* set command name                     */
        miCalculationUnit = CPU;
        mFunction.insert(RUNFPAIR("-o", [this](int) {this->mbIsO = true; }));
        mFunction.insert(RUNFPAIR("-f", [this](int){this->mbIsF = true; }));
        mFunction.insert(RUNFPAIR("-fb", [this](int){this->mbIsFB = true; }));
        mFunction.insert(RUNFPAIR("-gpu", [this](int){this->miCalculationUnit = GPU; }));
        mFunction.insert(RUNFPAIR("-n", [this](int i){this-> miRepeat= i; }));
        mFunction.insert(RUNFPAIR("-help", [this](int) {this->description(); this->mbIsHelp = true; }));
    }
    /*************************************************************************************************************
    Name:        action
    Description: Comannd action
    Argin:       ssAction  action name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool action(stringstream & ssAction,QPROGCLASS * pParserProg);
    /*************************************************************************************************************
    Name:        description
    Description: description Command
    Argin:       None
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    void description();

private:
    map<string, function<void(int)> > mFunction;
    bool mbIsO  = true;
    bool mbIsF  = false;
    bool mbIsFB = false;
    bool mbIsHelp = false;
    bool mbIsSetCompute = false;

    int  miRepeat = 0;
    int  miCalculationUnit;

    /*************************************************************************************************************
    Name:        saveMeasure
    Description: save Measure
    Argin:       sResult measure result 
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool saveMeasure(string &sResult,string sFilePath);

    /*************************************************************************************************************
    Name:        saveQstate
    Description: save QState
    Argin:       qsResult quantum state  result
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool saveQstate(string & qsResult,string sFilePath);

    /*************************************************************************************************************
    Name:        saveQstateBinary
    Description: save QState
    Argin:       qsResult quantum state  result
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool saveQstateBinary(string & qsResult,string sFilePath);

    bool getStringResult(string & sResult, QuantumGateParam *pQuantumGateParam);
    
};

/*****************************************************************************************************************
  QCommandExit:exit
*****************************************************************************************************************/
class  QCommandExit :public QCommand
{
public:
    inline QCommandExit()
    {
        mComand = "exit";                                               /* set command name                     */
        mFunction.insert(FPAIR("-help", [this]() {this->description(); }));
    }
    /*************************************************************************************************************
    Name:        action
    Description: Comannd action
    Argin:       ssAction  action name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool action(stringstream & ssAction,QPROGCLASS * pParserProg);
    /*************************************************************************************************************
    Name:        description
    Description: description Command
    Argin:       None
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    void description();

private:
    map<string, function<void()> > mFunction;
};

/*****************************************************************************************************************
QCommandMemory:Memory
*****************************************************************************************************************/
class  QCommandMemory :public QCommand
{
public:
    inline QCommandMemory()
    {
        mComand = "memory";                                             /* set command name                     */
        mFunction.insert(FPAIR("-help", [this]() {this->description(); }));
    }

    /*************************************************************************************************************
    Name:        action
    Description: Comannd action
    Argin:       ssAction  action name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool action(stringstream & ssAction,QPROGCLASS * pParserProg);

    /*************************************************************************************************************
    Name:        description
    Description: description Command
    Argin:       None
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    void description();
private:
    map<string, function<void()> > mFunction;
};

/*****************************************************************************************************************
QCommandCheckCUDA:checkCUDA
*****************************************************************************************************************/
class  QCommandCheckCUDA :public QCommand
{
public:
    inline QCommandCheckCUDA()
    {
        mComand = "checkCUDA";                                          /* set command name                     */
        mFunction.insert(FPAIR("-help", [this]() {this->description(); }));
    }

    /*************************************************************************************************************
    Name:        action
    Description: Comannd action
    Argin:       ssAction  action name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool action(stringstream & ssAction,QPROGCLASS * pParserProg);

    /*************************************************************************************************************
    Name:        description
    Description: description Command
    Argin:       None
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    void description();
private:
    map<string, function<void()> > mFunction;
};

/*****************************************************************************************************************
QCommandSubmit:submit
*****************************************************************************************************************/
class  QCommandSubmit :public QCommand
{
public:
    typedef  pair < string, function<void(int)>> SUBFPAIR;
    inline QCommandSubmit()
    {
        mComand = "submit";                                             /* set command name                     */
        mFunction.insert(SUBFPAIR("-help", [this](int) {this->description(); mbIsHelp = true; }));
         mFunction.insert(SUBFPAIR("-n", [this](int iRepeat) {miRepeat = iRepeat; }));
    }

    /*************************************************************************************************************
    Name:        action
    Description: Comannd action
    Argin:       ssAction  action name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool action(stringstream & ssAction,VirtualQCHttp * mpVirQCHttp);

    /*************************************************************************************************************
    Name:        description
    Description: description Command
    Argin:       None
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    void description();
private:

    bool mbIsHelp = false;

    int miRepeat = 0;

    map<string, function<void(int)> > mFunction;
};

/*****************************************************************************************************************
QCommandTaskList:tasklist
*****************************************************************************************************************/
class  QCommandTaskList :public QCommand
{
public:
    inline QCommandTaskList()
    {
        mComand = "tasklist";                                            /* set command name                     */
        mFunction.insert(FPAIR("-help", [this]() {this->description(); mbIsHelp = true; }));
    }

    /*************************************************************************************************************
    Name:        action
    Description: Comannd action
    Argin:       ssAction  action name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool action(stringstream & ssAction,VirtualQCHttp * mpVirQCHttp);

    /*************************************************************************************************************
    Name:        description
    Description: description Command
    Argin:       None
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    void description();
private:

    bool mbIsHelp = false;

    map<string, function<void()> > mFunction;
};

/*****************************************************************************************************************
QCommandGetResult:tasklist
*****************************************************************************************************************/
class  QCommandGetResult :public QCommand
{
public:
    inline QCommandGetResult()
    {
        mComand = "getresult";                                          /* set command name                     */
        mFunction.insert(FPAIR("-help", [this]() {this->description(); mbIsHelp = true; }));
    }

    /*************************************************************************************************************
    Name:        action
    Description: Comannd action
    Argin:       ssAction  action name
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    bool action(stringstream & ssAction,VirtualQCHttp * mpVirQCHttp);

    /*************************************************************************************************************
    Name:        description
    Description: description Command
    Argin:       None
    Argout:      None
    return:      true or false
    *************************************************************************************************************/
    void description();
private:

    bool mbIsHelp = false;

    map<string, function<void()> > mFunction;
};