#include "head.h"

class TesttQRunesParser : public testing::Test
{
protected:

};

TEST_F(TesttQRunesParser, testQRunesParser)
{
    string sTest;
    QList qlist;
    /*
    * 测试空字符串
    */
    EXPECT_EQ(-1, QRunesParser(sTest, qlist));

    /*
    * 测试无效文本地址
    */
    sTest.append("hahah");
    EXPECT_EQ(-1, QRunesParser(sTest, qlist));

    /*
    * 测试正确量子程序文本地址
    */
    string sTest2("shor_15.txt");
    EXPECT_NE(-1, QRunesParser(sTest2, qlist));

    /*
    * 测试错误量子程序文本地址
    */
    string sTest3("testfile.txt");
    EXPECT_EQ(-1, QRunesParser(sTest3, qlist));
}