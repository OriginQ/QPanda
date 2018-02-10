#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class QCommand
{
public:
     ~QCommand(){}
     inline QCommand()
     {
     }
     virtual bool action(stringstream & ssAction) = 0;
     virtual void description() = 0;

public:

    string  mComand;
    char  **mppcArgv;
    int     miArgc;
};


class QCommandSelectMode :public QCommand
{
public:
    inline QCommandSelectMode()
    {
        mComand = "mode";
    }
    bool action(stringstream & ssAction);
    void description();
};

class QCommandLoadFile :public QCommand
{
public:
    inline QCommandLoadFile()
    {
        mComand = "load";
    }
    bool action(stringstream & ssAction);
    void description();
};

class  QCommandRun :public QCommand
{
public:
    inline QCommandRun()
    {
        mComand = "run";
    }
    bool action(stringstream & ssAction);
    void description();
};

class  QCommandExit :public QCommand
{
public:
    inline QCommandExit()
    {
        mComand = "exit";
    }
    bool action(stringstream & ssAction);
    void description();
};

