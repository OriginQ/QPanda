#include "head.h"
#include "../QuantumInstructionHandle/GPUQuantumGates.h"
class TestQPandaAPI : public testing::Test
{
protected:

};
#define CPU 1
#define GPU 2

TEST_F(TestQPandaAPI, testLoadFile)
{
    QPandaSDK mQpandaAPI;
    string sTest;
    
    /*
    * 测试空字符串
    */
    EXPECT_EQ(qParameterError, mQpandaAPI.loadFile(sTest));

    /*
    * 测试无效文本地址
    */
    sTest.append("hahah");
    EXPECT_EQ(qbitError, mQpandaAPI.loadFile(sTest));
    mQpandaAPI.msFileName.clear();

    /*
    * 测试正确量子程序文本地址
    */
    string sTest2("shor_15.txt");
    EXPECT_EQ(qErrorNone, mQpandaAPI.loadFile(sTest2));
}

TEST_F(TestQPandaAPI, testSetComputeUnit)
{

    {
        /*
        * 测试错误输入
        */
        QPandaSDK mQpandaAPI;
        for(int i = -100;i<1;i++)
            EXPECT_EQ(qParameterError, mQpandaAPI.setComputeUnit(i));

        for (int i = 3; i<10000; i++)
            EXPECT_EQ(qParameterError, mQpandaAPI.setComputeUnit(i));

        /*
        * 测试正确输入
        */
        EXPECT_EQ(qErrorNone, mQpandaAPI.setComputeUnit(CPU));
    }
    QPandaSDK mQpandaAPI;
    auto mGPUDll = dllLoad("GPUEmulator.dll");
    /*
    * 测试存在GPUEmulator.dll和不存在GPUEmulator.dll时，
    * 输入GPU的返回情况
    */
    if(nullptr == mGPUDll)
        EXPECT_EQ(setComputeUnitError, mQpandaAPI.setComputeUnit(GPU));
    else
        EXPECT_EQ(qErrorNone, mQpandaAPI.setComputeUnit(GPU));

}

TEST_F(TestQPandaAPI, testRun)
{
    /*
    * 测试没有读取文件时的返回情况
    */
    QPandaSDK mQpandaAPI;
    EXPECT_EQ(notReadFileError, mQpandaAPI.run(1));

    /*
    * 测试iRepeat在错误范围时的返回情况
    */
    string sTest("shor_15.txt");
    EXPECT_EQ(qErrorNone, mQpandaAPI.loadFile(sTest));
    EXPECT_EQ(qParameterError, mQpandaAPI.run(-1));

    /*
    * 测试正确情况的返回值
    */
    EXPECT_EQ(qErrorNone, mQpandaAPI.setComputeUnit(CPU));
    EXPECT_EQ(qErrorNone, mQpandaAPI.run(100));
}


TEST_F(TestQPandaAPI, testGetResult)
{
    /*
    * 测试没有运行时函数的返回值
    */
    QPandaSDK mQpandaAPI;
    string temp = mQpandaAPI.getResult();
    EXPECT_EQ(0, temp.size());

    /*
    * 测试运行后函数的返回值
    */
    string sTest("shor_15.txt");
    EXPECT_EQ(qErrorNone, mQpandaAPI.loadFile(sTest));
    EXPECT_EQ(qErrorNone, mQpandaAPI.setComputeUnit(CPU));
    EXPECT_EQ(qErrorNone, mQpandaAPI.run(100));
    string sResult = mQpandaAPI.getResult();
    EXPECT_LT(0, sResult.size());
}

TEST_F(TestQPandaAPI, testGetQuantumState)
{
    /*
    * 测试没有运行时函数的返回值
    */
    QPandaSDK mQpandaAPI;
    string temp = mQpandaAPI.getQuantumState();
    EXPECT_EQ(0, temp.size());

    /*
    * 测试运行后函数的返回值
    */
    string sTest("shor_15.txt");
    EXPECT_EQ(qErrorNone, mQpandaAPI.loadFile(sTest));
    EXPECT_EQ(qErrorNone, mQpandaAPI.setComputeUnit(CPU));
    EXPECT_EQ(qErrorNone, mQpandaAPI.run(100));
    string sResult = mQpandaAPI.getQuantumState();
    EXPECT_LT(0, sResult.size());
}
