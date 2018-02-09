/******************************************************************************
Copyright (c) 2017-2018 Origin Quantum Computing Co., Ltd.. All Rights Reserved.


 
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at 

 	http://www.apache.org/licenses/LICENSE-2.0 
 
Unless required by applicable law or agreed to in writing, software

distributed under the License is distributed on an "AS IS" BASIS,

WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

See the License for the specific language
governing permissions and 
limitations under the License.
*******************************************************************************/
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
    {mZ        return -1;
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


