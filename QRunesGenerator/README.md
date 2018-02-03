# QRunes生成器说明书

## 一.简介

QRunes生成器是本源量子推出的量子代码生成器，用来生成QRunes代码模块。QRunes生成器可以使用户更方便地写QRunes代码，QRunes生成器可定义满足特定功能的量子函数，然后调用这个函数即可生成对应的QRunes代码。

## 二.使用说明

QRunes生成器是用C\+\+书写的QRunes代码工具，下面介绍QRunes生成器中的基本变量类型和基本函数。

### 1.基本变量类型

基本变量类型描述了量子程序中的量子变量，声明在QRState.h中。

#### qubit
qubit表示量子比特型变量，用来定义一个量子比特，示例如下：

    qubit a;
    //定义一个量子比特，名称为a
#### qVec
qVec表示量子比特数组，用来定义多个量子比特，示例如下：

    qVec b[5];
    //定义一个量子比特数组，里面包含五个量子比特
#### qRefList
qRefList 是一种容器型变量，容器元素是量子比特指针，用来存放指向量子比特的指针，示例如下：

    qRefList qre;           //定义qRefList型变量 qre
    qubit q1;               //定义量子比特 q1
    qVec q[2];              //定义包含两个量子比特的数组q[2]
    qre.push_back(&q1);     //将q1量子比特地址插入到qre
    qre.push_back(&q[1]);   //将q[2]中2号量子比特q[1]地址插入到qre
    
#### ancilla
ancilla表示辅助量子比特，用来定义辅助量子比特，辅助量子比特只会作用在定义它的函数中，调出定义它的函数后，辅助比特会自动释放，示例如下：

    ancilla qa;
    //定义辅助量子比特qa
#### aVec
aVec表示辅助量子比特数组，用来定义辅助量子比特数组，其作用范围与辅助比特一样，示例如下：

    aVec qa[5];
    //定义包含5个量子比特的数组
    
### 2.基本函数

可以使用的基本函数包括各种逻辑门或者控制语句，它们声明在QRGateController.h中。

#### RX/RY/RZ
RX/RY/RZ分别是QRunes代码中的RX/RY/RZ指令生成函数，输入参数有两个，分别为***qubit***型和***double***型，表示对应的量子比特和旋转的角度，角度单位为弧度。示例如下：

    qubit q;
    qVec  qv[5];
    double theta=3.1415926;
    RX(q,theta)         //RX操作，对应量子比特为q,旋转角度为theta  
    RY(qv[2],theta/2);  //RY操作，对应量子比特为qv[2],旋转角度为theta/2
    RZ(qv[0],1);        //RZ操作，对应量子比特为qv[0],旋转角度为1
#### Hadamard
Hadamard操作生成函数，输入参数为***qubit***型，表示对应的量子比特，示例如下：

    qubit q;
    Hadamard(q);        //Hadamard操作，对应量子比特为q
#### CNOT
CNOT操作生成函数，输入参数为两个***qubit***型，表示对应量子比特，示例如下：

    qVec q[10];
    CNOT(q[2],q[6]);    //CNOT操作，对应量子比特分别为q[2],q[6],q[2]表示控制量子比特，q[6]表示目标量子比特
#### CR
CNOT操作生成函数，输入参数为两个***qubit***型和一个***double***型，分别表示对应量子比特和旋转角度，示例如下：

    qVec q[4];
    double theta=2.3;
    CR(q[3],q[0],theta);
    //CR操作，对应量子比特分别为q[4],q[0]。q[4]表示控制量子比特，q[0]表示目标量子比特，theta表示旋转角度
#### Toffoli
Toffoli操作生成函数，输入参数为三个***qubit***型，分别表示对应量子比特，示例如下：

    qVec q[20];
    Toffoli(q[2],q[4],q[6]);
    //Toffoli操作，对应量子比特分别为q[2],q[4],q[6]。q[2],q[4]表示控制量子比特，q[6]表示目标量子比特
#### Measure
Measure操作生成函数，输入参数为***qubit***型，表示对应量子比特，示例如下：

    qubit q;
    Hadamard(q);
    Measure(q);         //Measure操作，对应量子比特为q
## 三. 示例
下面举两个用QRunes生成器生成的两种电路，量子傅里叶变换QFT和量子加法器qAdder
### 1. QFT

    void qft(qRefList q)
    {
        if (q.size() == 0)    // if q has no qubit, do nothing
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



### 2. qAdder
量子加法器包含两个子函数MAJ和UMA，定义如下：

    //MAJ函数
    void MAJ(qubit& a, qubit& b, qubit&c)
    {
        CNOT(c, b);
        CNOT(c, a);
        Toffoli(a, b, c);
    }
    //UMA函数
    void UMA(qubit& a, qubit& b, qubit&c)
    {
        Toffoli(a, b, c);
        CNOT(c, a);
        CNOT(a, b);
    }
    //qadder函数
    void adder(qRefList a, qRefList b, qubit& c)
    {
        size_t dim = a.size();
        ancilla temp;
    #define a *a        //这种宏定义用来简化写法
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
    
    