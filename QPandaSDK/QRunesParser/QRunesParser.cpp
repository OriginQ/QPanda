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