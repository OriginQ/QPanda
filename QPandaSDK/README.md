# QPandaSDK
## 1. QPandaSDK简介

&nbsp;&nbsp;&nbsp;&nbsp;QPandaSDK是由合肥本源量子科技有限公司开发，其作用是模拟量子计算，用户可根据自身需求基于此开发包开发应用程序。使用QPandaSDK开发的应用程序可运行基于QRuneScape量子指令集编写的量子程序。QPandaSDK提供CPU、GPU两种方式模拟量子计算，并提供多个接口方便用户使用。
## 2. QPandaSDK接口介绍
- loadfile函数

&nbsp;&nbsp;&nbsp;&nbsp;loadfile函数的作用是加载并解析用户编写的量子程序，如果程序有语法错误则返回loadProgramError，否则返回qErrorNone。其输入参数为需要解析的量子程序的路径。输出参数为解析的量子程序需要解析的量子bit数。

表 2.1 &nbsp;&nbsp;loadFile函数
---
    /*************************************************************************
    Name:        loadFile
    Description: load quantum program
    Argin:       sFilePath：quantum program file path
    Argout:      Qnum      ：    quantum bit num
    return:      qerror
    *************************************************************************/
    QError loadFile(const string &sFilePath,int &Qnum);

- setComputeUnit函数

&nbsp;&nbsp;&nbsp;&nbsp;setComputeUnit函数的作用是设置使用哪种方式模拟量子计算，用户有两种选择：CPU模式和GPU模式。如果设置失败则返回setComputeError，否则返回qErrorNone。函数的输入参数为需要计算单元类型。



表2.2&nbsp;&nbsp;setComputeUnit函数 
---
    /*************************************************************************
    Name:        setComputeUnit
    Description: set compute unit,you have two options:CPU or GPU.you can not 
    choose again when you have already selected a compute unit
    Argin:       iComputeUnit: the type of compute unit
    Argout:      None
    return:      qerror
    *************************************************************************/
    QError QParserProgram::setComputeUnit(int iComputeUnit);

- run函数

&nbsp;&nbsp;&nbsp;&nbsp;run函数的作用是运行解析的量子程序。量子程序根据其测量模式分类两种：Measure和PMeasure模式。Measure模式即为蒙特卡洛模式，由于目标量子在测量前，其状态是不确定的，所以该模式需要运行多次才能得到各种情况的概率。PMeasure模式即为概率模式，该模式会统计出每个目标量子各种可能的状态并统计其概率，PMeasure模式的程序只会运行一次。如果运行不成功则返回runProgramError，否则返回qErrorNone。函数的输入参数为需要重复运行的次数。



表2.3&nbsp;&nbsp;run函数
---
    /*************************************************************************
    Name:        run
    Description: run quantum program
    Argin:       iRepeat    quantum program repeat
    Argout:      None
    return:      qerror
    *************************************************************************/
    QError run(int iRepeat);
    
- getResult函数

&nbsp;&nbsp;&nbsp;&nbsp;getResult函数的作用是获取量子程序的运行结果。如果获取不成功则返回getResultError，否则返回qErrorNone。函数的输出参数为运行后的结果。


表2.4&nbsp;&nbsp;getResult函数  
---
    /*************************************************************************
    Name:        getResult
    Description: get quantum program result
    Argin:       None
    Argout:      sResult   result string
    return:      qerror
    *************************************************************************/
    QError getResult(STRING & sResult);
    
- getQuantumState函数

&nbsp;&nbsp;&nbsp;&nbsp;getQuantumState函数的作用是获取量子程序运行后的整个量子体系所有分量的复振幅。如果获取不成功返回getQStateError，否则返回qErrorNone。函数的输出参数为string类型的所有分量的复振幅。


表2.5&nbsp;&nbsp;getQuantumState函数  
---
    /************************************************************************
    Name:        getQuantumState
    Description: get quantum program qstate
    Argin:       None
    Argout:      sState   state string
    return:      qerror
    ************************************************************************/
    QError QParserProgram::getQState(STRING & sState);
    
## 3. QuantumParserSDK编译介绍

&nbsp;&nbsp;&nbsp;&nbsp;使用QuantumParserSDK需要使用Visual Studio编译。需要依次编译QuantumGPU库、QuantumInstructionHandle库、QRunesParser库、QParserSDK库。

## 4. QuantumParserSDK使用示例

表4.1&nbsp;&nbsp;使用示例
---


    int main(int argc, char *argv[])
    {
        string sResult,sQState;
        string sFilePath = "test.txt";
        int    iQnum     = 0;
        int    iRepeat   = 100;
        
        QParserSDK::QParserProgram  qParserProg();
        qParserProg.loadProgram(sFilePath);
        qParserProg.setComputeUnit(CPU);
        qParserProg.runProgram(iRepeat);
        qParserProg.getQResult(sResult);
        qParserProg.getQState(sQState);
        
        cout << "result:\n" << sResult << endl;
        cout << "QState:\n" << sQState << endl;
        
        return 0;
    }




















  
