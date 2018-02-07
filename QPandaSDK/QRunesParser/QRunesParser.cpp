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
************************************************************************/
#include "parser.h"
#include "y.tab.h"
#include <cstdio>
#include "LinkedListController.h"
#include <stdio.h>

/*************************************************
* global variable
*
* name      qList
* note      the final linked list saved in qList.qList
***************************************************/

/*************************************************
* global function
*
* name      parser
* arg       filename
* return    0  success
*           -1 when file not exist
*           -2 when bug encountered
***************************************************/
int parser(const char* filename, QList & qList)
{
    extern FILE* yyin;
    extern bool parserFailure;

    FILE *fp = fopen(filename, "r");
    yyin = fp;
    if (fp == NULL)
    {
        return -1;
    }
    parserFailure = false;
    yyparse(qList);
    if (parserFailure == true)
    {
        puts("At least 1 bug encountered.\n");
        fclose(fp);
        return -2;
    }
    else
    {
        puts("Parsing finished.\n");
    }
    fclose(fp);
    return 0;
}
