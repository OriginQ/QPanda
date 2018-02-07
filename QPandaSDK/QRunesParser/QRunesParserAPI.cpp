#include "QRunesParserAPI.h"

extern int qNum;

/*****************************************************************************************************************
Name:        QRunesParser
Description: quantum run parser 
Argin:       sFilePath        quantum program file path
             QInstructionList quantum instruction list
Argout:      QInstructionList quantum instruction list
return:      number of quantum bit 
*****************************************************************************************************************/
int QRunesParser(string &sFilePath, QList &QInstructionList)
{
    int bResult = -1;
    if (sFilePath.empty())
    {
        return bResult;
    }
    QList qlist;
    int status = parser(sFilePath.c_str(), qlist);

    if (0 == status)
    {
        QInstructionList = qlist;
        bResult = qNum;
    }
    
    return bResult;
}
