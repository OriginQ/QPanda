

#include <stdlib.h>
#include <iostream>
#include "../QuantumCommandControl/QuantumCommandCtrAPI.h"
#include <complex>
using namespace std;
using std::complex;

int main(int argc, char *argv[])
{
    int iMode = 1;
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp("-mode",argv[i]) == 0)
            {
                if ((argc - 1) == (i + 1))
                {
                    iMode = atoi(argv[i + 1]);
                    break;
                }
            }
        }
    }

    if (!initCommandVector(iMode))
    {
        return -1;
    }

    string ss;
    while (true)
    {
        cout << "command: ";
        getline(cin, ss, '\n');

        stringstream s1(ss);
        commandAction(s1);
        cin.clear();
        s1.str("");
    }

    system("pause");
    return 0;
}


