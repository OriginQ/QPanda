#include "head.h"
#include "../QuantumInstructionHandle/CPUQuantumGates.h"
#include "../QuantumInstructionHandle/QuantumGates.h"

#define PI 3.141592653589793
#define ZERO 1e-12
#define REPEAT 50
class TestCPUQuantumGates : public testing::Test
{
protected:

};

TEST_F(TestCPUQuantumGates, testInitState)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));

    double dProbSum = 0;

    for (size_t j = 0; j < cpuGates.getQStateSize(); j++)
    {
        dProbSum += cpuGates.mvQuantumStat[j].real()*cpuGates.mvQuantumStat[j].real()
            + cpuGates.mvQuantumStat[j].imag()*cpuGates.mvQuantumStat[j].imag();
    }
    EXPECT_EQ(true, abs(dProbSum - 1)<ZERO &&
        abs(cpuGates.mvQuantumStat[0].real() - 1)<ZERO);
}

TEST_F(TestCPUQuantumGates, testReset)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        ;
        EXPECT_EQ(qErrorNone, cpuGates.RX(i, cpuGates.randGenerator(), 0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.Reset(i));
    }

    EXPECT_EQ(true, abs(abs(cpuGates.mvQuantumStat[0]) - 1)<ZERO);
}

TEST_F(TestCPUQuantumGates, testNOT)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real() - 1) < ZERO);
        EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
    }
}

TEST_F(TestCPUQuantumGates, testHadamard)
{
#define SQ2 0.707106781186548
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(i, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - SQ2) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real() - SQ2) < ZERO);
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(i, 0));
    }

    for (int i = 0; i < iQBitNum; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(i, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - SQ2) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real() + SQ2) < ZERO);
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(i, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
    }
}

TEST_F(TestCPUQuantumGates, testRX)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    double dTheta = cpuGates.randGenerator();
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.RX(i, dTheta, 0, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - cos(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].imag() + sin(dTheta / 2)) < ZERO);
        EXPECT_EQ(qErrorNone, cpuGates.RX(i, dTheta, 0, 1));
    }

    for (int i = 0; i < iQBitNum; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
        EXPECT_EQ(qErrorNone, cpuGates.RX(i, dTheta, 0, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].imag() + sin(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real() - cos(dTheta / 2)) < ZERO);
        EXPECT_EQ(qErrorNone, cpuGates.RX(i, dTheta, 0, 1));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
    }
}

TEST_F(TestCPUQuantumGates, testRY)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    double dTheta = cpuGates.randGenerator();
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.RY(i, dTheta, 0, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - cos(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real() - sin(dTheta / 2)) < ZERO);
        EXPECT_EQ(qErrorNone, cpuGates.RY(i, dTheta, 0, 1));
    }

    for (int i = 0; i < iQBitNum; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
        EXPECT_EQ(qErrorNone, cpuGates.RY(i, dTheta, 0, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() + sin(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real() - cos(dTheta / 2)) < ZERO);
        EXPECT_EQ(qErrorNone, cpuGates.RY(i, dTheta, 0, 1));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
    }
}

TEST_F(TestCPUQuantumGates, testRZ)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    double dTheta = cpuGates.randGenerator();
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.RZ(i, dTheta, 0, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - cos(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].imag() + sin(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real()) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].imag()) < ZERO);
        EXPECT_EQ(qErrorNone, cpuGates.RZ(i, dTheta, 0, 1));
    }

    for (int i = 0; i < iQBitNum; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
        EXPECT_EQ(qErrorNone, cpuGates.RZ(i, dTheta, 0, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real()) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].imag()) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real() - cos(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].imag() - sin(dTheta / 2)) < ZERO);
        EXPECT_EQ(qErrorNone, cpuGates.RZ(i, dTheta, 0, 1));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
    }
}

TEST_F(TestCPUQuantumGates, testCNOT)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        for (int j = 0; j < iQBitNum; j++)
        {
            if (i != j)
            {
                // |00> -> |00>
                EXPECT_EQ(qErrorNone, cpuGates.CNOT(i, j, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
                // |01> -> |01>
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                EXPECT_EQ(qErrorNone, cpuGates.CNOT(i, j, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << j].real() - 1) < ZERO);
                // |11> -> |10>
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                EXPECT_EQ(qErrorNone, cpuGates.CNOT(i, j, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real() - 1) < ZERO);
                // |10> -> |11>
                EXPECT_EQ(qErrorNone, cpuGates.CNOT(i, j, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << i) + (1ll << j)].real() - 1) < ZERO);
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
            }
        }
    }
}

TEST_F(TestCPUQuantumGates, testCR)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    double dTheta = cpuGates.randGenerator();
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        for (int j = 0; j < iQBitNum; j++)
        {
            if (i != j)
            {
                // |00> -> |00>
                EXPECT_EQ(qErrorNone, cpuGates.CR(i, j, dTheta, 0, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
                // |01> -> |01>
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                EXPECT_EQ(qErrorNone, cpuGates.CR(i, j, dTheta, 0, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << j].real() - 1) < ZERO);
                // |11> -> exp(i*dTheta)|11>
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                EXPECT_EQ(qErrorNone, cpuGates.CR(i, j, dTheta, 0, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << i) + (1ll << j)].real() - cos(dTheta)) < ZERO);
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << i) + (1ll << j)].imag() - sin(dTheta)) < ZERO);
                EXPECT_EQ(qErrorNone, cpuGates.CR(i, j, dTheta, 0, 1));
                // |10> -> |10>
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                EXPECT_EQ(qErrorNone, cpuGates.CR(i, j, dTheta, 0, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real() - 1) < ZERO);
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));

            }
        }
    }
}

TEST_F(TestCPUQuantumGates, testISWAP)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    double dTheta = cpuGates.randGenerator();
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        for (int j = 0; j < iQBitNum; j++)
        {
            if (i != j)
            {
                // |00> -> |00>
                EXPECT_EQ(qErrorNone, cpuGates.iSWAP(i, j, 0, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
                // |01> -> i*|10>
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                EXPECT_EQ(qErrorNone, cpuGates.iSWAP(i, j, 0, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].imag() - 1) < ZERO);
                EXPECT_EQ(qErrorNone, cpuGates.iSWAP(i, j, 0, 1));
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                // |10> -> i*|01>
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                EXPECT_EQ(qErrorNone, cpuGates.iSWAP(i, j, 0, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << j].imag() - 1) < ZERO);
                EXPECT_EQ(qErrorNone, cpuGates.iSWAP(i, j, 0, 1));
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                // |11> -> |11>
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                EXPECT_EQ(qErrorNone, cpuGates.iSWAP(i, j, 0, 1));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << i) + (1ll << j)].real() - 1) < ZERO);
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
            }
        }
    }
}

TEST_F(TestCPUQuantumGates, testSqiSWAP)
{
#define SQ2 0.707106781186548
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    double dTheta = cpuGates.randGenerator();
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        for (int j = 0; j < iQBitNum; j++)
        {
            if (i != j)
            {
                // |00> -> |00>
                EXPECT_EQ(qErrorNone, cpuGates.sqiSWAP(i, j, 0, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
                // |01> -> SQ2*|01>+SQ2*i*|10>
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                EXPECT_EQ(qErrorNone, cpuGates.sqiSWAP(i, j, 0, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].imag() - SQ2) < ZERO);
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << j].real() - SQ2) < ZERO);
                EXPECT_EQ(qErrorNone, cpuGates.sqiSWAP(i, j, 0, 1));
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                // |10> -> SQ2*i*|01>+SQ2*|10>
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                EXPECT_EQ(qErrorNone, cpuGates.sqiSWAP(i, j, 0, 0));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real() - SQ2) < ZERO);
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << j].imag() - SQ2) < ZERO);
                EXPECT_EQ(qErrorNone, cpuGates.sqiSWAP(i, j, 0, 1));
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                // |11> -> |11>
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                EXPECT_EQ(qErrorNone, cpuGates.sqiSWAP(i, j, 0, 1));
                EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << i) + (1ll << j)].real() - 1) < ZERO);
                EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
            }
        }
    }
}

TEST_F(TestCPUQuantumGates, testQubitMeasure)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 4;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    int iq0 = 0;
    int iq1 = 0;
    int iTimes = 1ll << 16;
    for (int i = 0; i < iTimes; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(0, 0));
        if (cpuGates.qubitMeasure(0))
        {
            iq1++;
        }
        else
        {
            iq0++;
        }
    }
    EXPECT_EQ(true, abs(iq0*1.0 / iTimes - 0.5)< 1e-2);
}

TEST_F(TestCPUQuantumGates, testPMeasure)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(i, 0));
    }
    Qnum qMList = { 2,1,3 };
    vector<pair<size_t, double>> vOutcome;
    EXPECT_EQ(qErrorNone, cpuGates.pMeasure(qMList, vOutcome));
    for (int i = 0; i < (1ll << qMList.size()); i++)
    {
        EXPECT_EQ(true, abs(vOutcome[i].second - 1.0 / (1ll << qMList.size()))<ZERO);
    }
}

TEST_F(TestCPUQuantumGates, testToffoli)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    for (int i = 0; i < iQBitNum; i++)
    {
        for (int j = 0; j < iQBitNum; j++)
        {
            for (int k = 0; k < iQBitNum; k++)
            {
                if (i != j && j != k && i != k)
                {
                    // |000> -> |000>
                    EXPECT_EQ(qErrorNone, cpuGates.toffoli(i, j, k, 0, iQBitNum));
                    EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
                    // |001> -> |001>
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(k, 0));
                    EXPECT_EQ(qErrorNone, cpuGates.toffoli(i, j, k, 0, iQBitNum));
                    EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << k].real() - 1) < ZERO);
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(k, 0));
                    // |010> -> |010>
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                    EXPECT_EQ(qErrorNone, cpuGates.toffoli(i, j, k, 0, iQBitNum));
                    EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << j].real() - 1) < ZERO);
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                    // |011> -> |011>
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(k, 0));
                    EXPECT_EQ(qErrorNone, cpuGates.toffoli(i, j, k, 0, iQBitNum));
                    EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << j) + (1ll << k)].real() - 1) < ZERO);
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(k, 0));
                    // |100> -> |100>
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                    EXPECT_EQ(qErrorNone, cpuGates.toffoli(i, j, k, 0, iQBitNum));
                    EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[1ll << i].real() - 1) < ZERO);
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                    // |101> -> |101>
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(k, 0));
                    EXPECT_EQ(qErrorNone, cpuGates.toffoli(i, j, k, 0, iQBitNum));
                    EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << i) + (1ll << k)].real() - 1) < ZERO);
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(k, 0));
                    // |110> -> |111>
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                    size_t stIndex = (1ll << i) + (1ll << j) + (1ll << k);
                    EXPECT_EQ(qErrorNone, cpuGates.toffoli(i, j, k, 0, iQBitNum));
                    EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[stIndex].real() - 1) < ZERO);
                    // |111> -> |110>
                    EXPECT_EQ(qErrorNone, cpuGates.toffoli(i, j, k, 0, iQBitNum));
                    EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[stIndex - (1ll << k)].real() - 1) < ZERO);
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(i, 0));
                    EXPECT_EQ(qErrorNone, cpuGates.NOT(j, 0));
                }
            }
        }
    }
}


//controled-gate


TEST_F(TestCPUQuantumGates, testControledNOT)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    size_t iq0, iq1, iq2;

    for (auto i = 0; i < REPEAT; i++)
    {
        iq0 = (size_t)(cpuGates.randGenerator() * 10);
        iq1 = (size_t)(cpuGates.randGenerator() * 10);
        iq2 = (size_t)(cpuGates.randGenerator() * 10);
        while (iq0 == iq1)
        {
            iq1 = (size_t)(cpuGates.randGenerator() * 10);
        }
        while (iq0 == iq2 || iq1 == iq2)
        {
            iq2 = (size_t)(cpuGates.randGenerator() * 10);
        }
        Qnum qList = { iq0,iq1,iq2 };
        // |000> -> |000>
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0, qList, iQBitNum));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
        // |110> -> |111>
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0, qList, iQBitNum));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1) + (1ll << iq2)].real() - 1) < ZERO);
        // |111> -> |110>
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0, qList, iQBitNum));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1)].real() - 1) < ZERO);
        // initialize to |000>
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
    }
}


TEST_F(TestCPUQuantumGates, testControledHadamard)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    size_t iq0, iq1, iq2;
    for (auto i = 0; i < REPEAT; i++)
    {
        iq0 = (size_t)(cpuGates.randGenerator() * 10);
        iq1 = (size_t)(cpuGates.randGenerator() * 10);
        iq2 = (size_t)(cpuGates.randGenerator() * 10);
        while (iq0 == iq1)
        {
            iq1 = (size_t)(cpuGates.randGenerator() * 10);
        }
        while (iq0 == iq2 || iq1 == iq2)
        {
            iq2 = (size_t)(cpuGates.randGenerator() * 10);
        }
        Qnum qList = { iq0,iq1,iq2 };
        // |000> -> |000>
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(iq2, 0, qList, iQBitNum));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
        // |110> -> SQ2*|110> + SQ2*|111>
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(iq2, 0, qList, iQBitNum));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1)].real() - SQ2) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1) + (1ll << iq2)].real() - SQ2) < ZERO);
        // |111> -> SQ2*|110> - SQ2*|111>
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(iq2, 0, qList, iQBitNum));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0));
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(iq2, 0, qList, iQBitNum));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1)].real() - SQ2) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1) + (1ll << iq2)].real() + SQ2) < ZERO);
        // initialize to |000>
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(iq2, 0, qList, iQBitNum));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0));
    }

}


TEST_F(TestCPUQuantumGates, testControledRX)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    double dTheta;
    size_t iq0, iq1, iq2;
    for (auto i = 0; i < REPEAT; i++)
    {
        dTheta = cpuGates.randGenerator() * 2 * PI;
        iq0 = (size_t)(cpuGates.randGenerator() * 10);
        iq1 = (size_t)(cpuGates.randGenerator() * 10);
        iq2 = (size_t)(cpuGates.randGenerator() * 10);
        while (iq0 == iq1)
        {
            iq1 = (size_t)(cpuGates.randGenerator() * 10);
        }
        while (iq0 == iq2 || iq1 == iq2)
        {
            iq2 = (size_t)(cpuGates.randGenerator() * 10);
        }
        Qnum qList = { iq0,iq1,iq2 };
        // |000> -> |000>
        EXPECT_EQ(qErrorNone, cpuGates.RX(iq2, dTheta, 0, qList, iQBitNum, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
        // |110> -> cos(dTheta/2)*|110> - i*sin(dTheta/2)*|111>
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
        EXPECT_EQ(qErrorNone, cpuGates.RX(iq2, dTheta, 0, qList, iQBitNum, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1)].real() - cos(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1) + (1ll << iq2)].imag()
            + sin(dTheta / 2)) < ZERO);
        // |111> -> cos(dTheta/2)*|111> - i*sin(dTheta/2)*|110>
        EXPECT_EQ(qErrorNone, cpuGates.RX(iq2, dTheta, 0, qList, iQBitNum, 1));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0));
        EXPECT_EQ(qErrorNone, cpuGates.RX(iq2, dTheta, 0, qList, iQBitNum, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1)].imag() + sin(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1) + (1ll << iq2)].real()
            - cos(dTheta / 2)) < ZERO);
        //initialize to |000>
        EXPECT_EQ(qErrorNone, cpuGates.RX(iq2, dTheta, 0, qList, iQBitNum, 1));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0));
    }
}

TEST_F(TestCPUQuantumGates, testControledRY)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    double dTheta;
    size_t iq0, iq1, iq2;
    for (auto i = 0; i < REPEAT; i++)
    {
        dTheta = cpuGates.randGenerator() * 2 * PI;
        iq0 = (size_t)(cpuGates.randGenerator() * 10);
        iq1 = (size_t)(cpuGates.randGenerator() * 10);
        iq2 = (size_t)(cpuGates.randGenerator() * 10);
        while (iq0 == iq1)
        {
            iq1 = (size_t)(cpuGates.randGenerator() * 10);
        }
        while (iq0 == iq2 || iq1 == iq2)
        {
            iq2 = (size_t)(cpuGates.randGenerator() * 10);
        }
        Qnum qList = { iq0,iq1,iq2 };
        // |000> -> |000>
        EXPECT_EQ(qErrorNone, cpuGates.RY(iq2, dTheta, 0, qList, iQBitNum, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
        // |110> -> cos(dTheta/2)*|110> + sin(dTheta/2)*|111>
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
        EXPECT_EQ(qErrorNone, cpuGates.RY(iq2, dTheta, 0, qList, iQBitNum, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1)].real() - cos(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1) + (1ll << iq2)].real()
            - sin(dTheta / 2)) < ZERO);
        // |111> -> cos(dTheta/2)*|111> - sin(dTheta/2)*|110>
        EXPECT_EQ(qErrorNone, cpuGates.RY(iq2, dTheta, 0, qList, iQBitNum, 1));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0));
        EXPECT_EQ(qErrorNone, cpuGates.RY(iq2, dTheta, 0, qList, iQBitNum, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1)].real() + sin(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1) + (1ll << iq2)].real()
            - cos(dTheta / 2)) < ZERO);
        // initialize to |000>
        EXPECT_EQ(qErrorNone, cpuGates.RY(iq2, dTheta, 0, qList, iQBitNum, 1));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0));
    }

}

TEST_F(TestCPUQuantumGates, testControledRZ)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    double dTheta;
    size_t iq0, iq1, iq2;
    for (auto i = 0; i < REPEAT; i++)
    {
        dTheta = cpuGates.randGenerator() * 2 * PI;
        iq0 = (size_t)(cpuGates.randGenerator() * 10);
        iq1 = (size_t)(cpuGates.randGenerator() * 10);
        iq2 = (size_t)(cpuGates.randGenerator() * 10);
        while (iq0 == iq1)
        {
            iq1 = (size_t)(cpuGates.randGenerator() * 10);
        }
        while (iq0 == iq2 || iq1 == iq2)
        {
            iq2 = (size_t)(cpuGates.randGenerator() * 10);
        }
        Qnum qList = { iq0,iq1,iq2 };
        // |000> -> |000>
        EXPECT_EQ(qErrorNone, cpuGates.RZ(iq2, dTheta, 0, qList, iQBitNum, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
        // |110> -> exp(-i*dTheta/2)*|110>
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
        EXPECT_EQ(qErrorNone, cpuGates.RZ(iq2, dTheta, 0, qList, iQBitNum, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1)].real() - cos(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1)].imag() + sin(dTheta / 2)) < ZERO);
        // |111> -> exp(i*dTheta/2)*|111>
        EXPECT_EQ(qErrorNone, cpuGates.RZ(iq2, dTheta, 0, qList, iQBitNum, 1));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0));
        EXPECT_EQ(qErrorNone, cpuGates.RZ(iq2, dTheta, 0, qList, iQBitNum, 0));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1) + (1ll << iq2)].real()
            - cos(dTheta / 2)) < ZERO);
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[(1ll << iq0) + (1ll << iq1) + (1ll << iq2)].imag()
            - sin(dTheta / 2)) < ZERO);
        //initialize to |000>
        EXPECT_EQ(qErrorNone, cpuGates.RZ(iq2, dTheta, 0, qList, iQBitNum, 1));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0));
    }

}

TEST_F(TestCPUQuantumGates, testControledCNOT)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 10;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));
    size_t iq0, iq1, iq2, iq3;
    for (auto i = 0; i < REPEAT; i++)
    {
        iq0 = (size_t)(cpuGates.randGenerator() * 10);
        iq1 = (size_t)(cpuGates.randGenerator() * 10);
        iq2 = (size_t)(cpuGates.randGenerator() * 10);
        iq3 = (size_t)(cpuGates.randGenerator() * 10);
        while (iq0 == iq1)
        {
            iq1 = (size_t)(cpuGates.randGenerator() * 10);
        }
        while (iq0 == iq2 || iq1 == iq2)
        {
            iq2 = (size_t)(cpuGates.randGenerator() * 10);
        }
        while (iq0 == iq3 || iq1 == iq3 || iq2 == iq3)
        {
            iq3 = (size_t)(cpuGates.randGenerator() * 10);
        }
        Qnum qList = { iq0,iq1,iq2,iq3 };
        // |0000> -> |0000>
        EXPECT_EQ(qErrorNone, cpuGates.CNOT(iq2, iq3, 0, qList, iQBitNum));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[0].real() - 1) < ZERO);
        // |1110> -> |1111>
        size_t stTemp = (1ll << iq0) + (1ll << iq1) + (1ll << iq2) + (1ll << iq3);
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0));
        EXPECT_EQ(qErrorNone, cpuGates.CNOT(iq2, iq3, 0, qList, iQBitNum));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[stTemp].real() - 1) < ZERO);
        // |1111> -> |1110>
        EXPECT_EQ(qErrorNone, cpuGates.CNOT(iq2, iq3, 0, qList, iQBitNum));
        EXPECT_EQ(true, abs(cpuGates.mvQuantumStat[stTemp - (1ll << iq3)].real() - 1) < ZERO);
        // initialize to |0000>
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq0, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq1, 0));
        EXPECT_EQ(qErrorNone, cpuGates.NOT(iq2, 0));
    }

}

TEST_F(TestCPUQuantumGates, testShorAlgorithm)
{
    CPUQuantumGates cpuGates;
    QuantumGateParam param;
    int iQBitNum = 12;
    param.setQBitNum(iQBitNum);
    EXPECT_EQ(qErrorNone, cpuGates.initState(&param));

    EXPECT_EQ(qErrorNone, cpuGates.NOT(0, 0));
    for (auto i = 4; i < 12; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(i, 0));
    }
    for (auto i = 0; i < 4; i++)
    {
        EXPECT_EQ(qErrorNone, cpuGates.CNOT(i, 4, 0));
    }
    EXPECT_EQ(qErrorNone, cpuGates.controlSwap(4, 2, 1));
    EXPECT_EQ(qErrorNone, cpuGates.controlSwap(4, 2, 3));
    EXPECT_EQ(qErrorNone, cpuGates.controlSwap(4, 3, 0));
    EXPECT_EQ(qErrorNone, cpuGates.controlSwap(5, 2, 0));
    EXPECT_EQ(qErrorNone, cpuGates.controlSwap(5, 3, 1));

    for (int i = 11; i >= 4; i--)
    {
        EXPECT_EQ(qErrorNone, cpuGates.Hadamard(i, 0));
        for (int j = i - 1; j >= 4; j--)
        {
            EXPECT_EQ(qErrorNone, cpuGates.CR(i, j, -PI / (1ll << (i - j)), 0, 0));
        }
    }
    Qnum qMList = { 5,4 };
    vector<pair<size_t, double>> vOutcome;
    EXPECT_EQ(qErrorNone, cpuGates.pMeasure(qMList, vOutcome));
    //vOutcome[i].second=0.25, i=0,1,2,3
    for (int i = 0; i < (1ll << qMList.size()); i++)
    {
        EXPECT_EQ(true, abs(vOutcome[i].second - 0.25) < ZERO);
    }
}
