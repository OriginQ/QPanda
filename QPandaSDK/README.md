# QPandaSDK
## 1. QPandaSDK简介

&nbsp;&nbsp;&nbsp;&nbsp;Q-Panda SDK是由本源量子推出的，基于量子云服务的，开源的量子软件开发包。用户可基于此开发包开发在云端执行的量子程序。Q-Panda使用C++语言作为经典宿主语言，支持以QRunes书写的量子语言。

&nbsp;&nbsp;&nbsp;&nbsp;目前，Q-Panda支持本地仿真运行模式和云仿真运行模式，最高可支持到32位。Q-Panda提供了一个可执行的命令行程序，通过指令控制量子程序的加载、运行和读出。另外，Q-Panda提供了一组API，可供用户自行定制功能。
## 2. QPandaSDK接口介绍
- loadFile函数

&nbsp;&nbsp;&nbsp;&nbsp;loadFile函数的作用是加载并解析用户编写的量子程序，如果程序有语法错误则返回loadProgramError，否则返回qErrorNone。其输入参数为需要解析的量子程序的路径。输出参数为解析的量子程序需要解析的量子bit数。

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
    
## 3. QPandaSDK编译介绍

&nbsp;&nbsp;&nbsp;&nbsp;QPandaSDK分为两个部分：QPandaAPI以及基于QPandaAPI搭建的量子程序执行系统。

### QPandaAPI编译

&nbsp;&nbsp;&nbsp;&nbsp;QPandaAPI可使用makefile编译和Visual Studio编译。

- makefile编译

&nbsp;&nbsp;&nbsp;&nbsp;使用makefile编译比较简单，直接执行make命令即可。在此之前用户需要验证本机是否已经安装cuda，如果未安装则无法使用GPUEmulator库。

- Visual Studio编译

&nbsp;&nbsp;&nbsp;&nbsp;使用Visual Studio编译主要分为以下几步：

- 创建解决方案；

- 加载QPandaAPI、QRunesParser、QuantumInstructionHandle、GPUEmulator子项目；

- 分别编译QuantumInstructionHandle、GPUEmulator、QRunesParser、QPandaAPI，顺序从前向后。

### 量子程序执行系统编译

&nbsp;&nbsp;&nbsp;&nbsp;量子程序执行系统需要使用Visual Studio编译。本系统由于使用了一些公共库，所以只支持64位。量子程序执行系统在编译前需要准备以下环境：

- python 2.7.14

&nbsp;&nbsp;&nbsp;&nbsp;量子程序执行系统使用Visual Studio编译分为以下步骤：

- 除ConsoleApplication外，其他项目设置为dll动态链接库;

- 设置解决方案平台为x64;

- 依次编译QuantumInstructionHandle、GPUEmulator、QRunesParser、QPandaAPI、QuantumCloudHTTP、QuantumCommandControl库与ConsoleApplication应用程序。

## 4. QPandaAPI使用示例

表4.1&nbsp;&nbsp;使用示例
---


    int main(int argc, char *argv[])
    {
        string sResult,sQState;
        string sFilePath = "test.txt";
        int    iQnum     = 0;
        int    iRepeat   = 100;
        
        QParserSDK::QParserProgram  qParserProg();
        qParserProg.loadFile(sFilePath);
        qParserProg.setComputeUnit(CPU);
        qParserProg.run(iRepeat);
        qParserProg.getResult(sResult);
        qParserProg.getQuantumState(sQState);
        
        cout << "result:\n" << sResult << endl;
        cout << "QState:\n" << sQState << endl;
        
        return 0;
    }

## 5. 量子程序执行系统使用示例

&nbsp;&nbsp;&nbsp;&nbsp;使用量子程序执行系统前需要先进行以下步骤：

- 从 http://www.qubitonline.cn/ 获取APIkey；

- 把APIkey保存在文件中，命名文件为key，并把key文件保存在ConfigFile文件夹中；

- 把ConfigFile文件夹复制到ConsoleApplication.exe同一文件夹下；

- 安装DepInstalPackage中python 2.7.14。

&nbsp;&nbsp;&nbsp;&nbsp;量子程序执行系统分为本地仿真运行模式和云仿真运行模式，可在启动程序时使用mode命令选择运行模式。

---
    ConsoleApplication.exe mode [mode]
    
- mode 1 表示使用本地仿真模式；
- mode 2 表示使用云仿真模式。

### 本地仿真运行模式命令

&nbsp;&nbsp;&nbsp;&nbsp;本地仿真运行模式命令如下所示：
- load 加载本地量子程序文件

---
    load [path]
    
- run 运行已经加载的量子程序

---
    run -n [repeat] -gpu -f -o -b
    -n    重复次数
    -gpu  选择使用GPU仿真量子计算（不使用此命令时，默认选择使用CPU仿真量子计算）
    -f    保存quantum state
    -o    保存运行结果
    -b    以2进制的方式保存quantum state
    
 ### 云仿真模式
 
 &nbsp;&nbsp;&nbsp;&nbsp;云仿真运行模式命令如下所示：
 - submit 提交本地量子程序文件
 
---
    submit [path] -n [repeat]
    -n    重复次数
    

- tasklist 获取用户提交的量子程序的TaskID
- getresult 获取量子程序的运行结果

---
    getresult [TaskID]
























  
