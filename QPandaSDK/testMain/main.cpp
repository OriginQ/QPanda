#include "head.h"
#include <sstream>

int main(int argc, _TCHAR* argv[])
{
    testing::InitGoogleTest(&argc, argv);
   
    auto run = RUN_ALL_TESTS();
    system("pause");
    return run;
}

