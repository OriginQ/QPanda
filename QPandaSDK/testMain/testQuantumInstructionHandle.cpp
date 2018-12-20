#include "head.h"
#include "../QuantumInstructionHandle/GPUQuantumGates.h"
class TestQuantumInstructionHandle : public testing::Test
{
protected:
};

TEST_F(TestQuantumInstructionHandle, testSetComputeUnit)
{
    {
        /*
        * 测试错误输入
        */
        QuantumInstructionHandleAPI mHandle;
        for (int i = -100; i<1; i++)
            EXPECT_EQ(false, mHandle.setComputeUnit(i));

        for (int i = 3; i<10000; i++)
            EXPECT_EQ(false, mHandle.setComputeUnit(i));

        /*
        * 测试正确输入
        */
        EXPECT_EQ(true, mHandle.setComputeUnit(CPU));
    }
    QuantumInstructionHandleAPI mHandle;
    auto mGPUDll = dllLoad("GPUEmulator.dll");
    /*
    * 测试存在GPUEmulator.dll和不存在GPUEmulator.dll时，
    * 输入GPU的返回情况
    */
    if (nullptr == mGPUDll)
        EXPECT_EQ(false, mHandle.setComputeUnit(GPU));
    else
        EXPECT_EQ(true, mHandle.setComputeUnit(GPU));

}

TEST_F(TestQuantumInstructionHandle, testInitState)
{
    /*
    * 测试未设置计算单元时initState的输出
    */
    QuantumInstructionHandleAPI mHandle;
    QuantumGateParam param;
    EXPECT_EQ(false, mHandle.initState(&param));

    /*
    * 测试没有设置qbit数时initState的输出
    */
    EXPECT_EQ(true, mHandle.setComputeUnit(1));
    EXPECT_EQ(false, mHandle.initState(&param));
    
    /*
    * 测试qbit数范围设置错误时initState的输出
    */
    param.setQBitNum(-1);
    EXPECT_EQ(false, mHandle.initState(&param));

    /*
    * 测试qbit数范围超出时initState的输出
    */
    param.setQBitNum(40);
    EXPECT_EQ(false, mHandle.initState(&param));

    /*
    * 测试成功条件下的输出情况
    */
    param.setQBitNum(10);
    EXPECT_EQ(true, mHandle.initState(&param));

}


TEST_F(TestQuantumInstructionHandle, testDestroyState)
{
    /*
    * 测试传入参数为空时initState的输出
    */
    QuantumInstructionHandleAPI mHandle;
    EXPECT_EQ(true, mHandle.destroyState(nullptr));
    /*
    * 测试未设置计算单元时initState的输出
    */
    QuantumGateParam param;
    EXPECT_EQ(true, mHandle.destroyState(&param));

    /*
    * 测试没有设置qbit数时initState的输出
    */
    EXPECT_EQ(true, mHandle.setComputeUnit(1));
    EXPECT_EQ(true, mHandle.destroyState(&param));

    /*
    * 测试成功条件下的输出情况
    */
    EXPECT_EQ(true, mHandle.setComputeUnit(1));
    param.setQBitNum(10);
    EXPECT_EQ(true, mHandle.initState(&param));
    EXPECT_EQ(true, mHandle.destroyState(&param));
}

TEST_F(TestQuantumInstructionHandle, testTransmit)
{
    QuantumInstructionHandleAPI mHandle;
    QuantumGateParam param;
    QList qlist;
    /*
    * 测试传入参数为空时transmit的输出
    */
    EXPECT_EQ(false, mHandle.transmit(qlist, nullptr));

    /*
    * 测试未设置计算单元时transmit的输出
    */
    EXPECT_EQ(false, mHandle.transmit(qlist, &param));

    /*
    * 测试没有设置qbit数时transmit的输出
    */
    EXPECT_EQ(true, mHandle.setComputeUnit(1));
    EXPECT_EQ(false, mHandle.transmit(qlist, &param));

    /*
    * 测试没有initState时transmit的输出
    */
    param.setQBitNum(10);
    EXPECT_EQ(false, mHandle.transmit(qlist, &param));
    
    /*
    * 测试正确情况时transmit的输出
    */
    EXPECT_EQ(true, mHandle.initState(&param));
    EXPECT_EQ(true, mHandle.transmit(qlist, &param));

    /*
    * 测试qbitnum越界时transmit的输出
    */
    qlist.gateInsert(HADAMARD_GATE, 20);
    EXPECT_EQ(false, mHandle.transmit(qlist,&param));
    EXPECT_EQ(true, mHandle.destroyState(&param));
}

TEST_F(TestQuantumInstructionHandle, testGetQState)
{
    QuantumInstructionHandleAPI mHandle;
    QuantumGateParam param;
    string temp;
    /*
    * 测试传入参数为空时getState的输出
    */
    EXPECT_EQ(false, mHandle.getState(temp,nullptr));

    /*
    * 测试未设置计算单元时getState的输出
    */
    EXPECT_EQ(false, mHandle.getState(temp, &param));

    /*
    * 测试没有设置qbit数时getState的输出
    */
    EXPECT_EQ(true, mHandle.setComputeUnit(1));
    EXPECT_EQ(false, mHandle.getState(temp, &param));

    /*
    * 测试没有initState时getState的输出
    */
    param.setQBitNum(10);
    EXPECT_EQ(false, mHandle.getState(temp, &param));

    /*
    * 测试正确情况时transmit的输出
    */
    EXPECT_EQ(true, mHandle.initState(&param));
    EXPECT_EQ(true, mHandle.getState(temp, &param));
    EXPECT_EQ(true, mHandle.destroyState(&param));

}