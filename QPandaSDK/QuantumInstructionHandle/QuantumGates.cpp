/*********************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-10
Description:the Parent of quantum logic gates class
*********************************************************************************************************/
#include "QuantumGates.h"
#include <time.h>

QuantumGates::QuantumGates()
{
}


QuantumGates::~QuantumGates()
{
}


/*****************************************************************************************************************
Name:        randGenerator
Description: 16807 random number generator
Argin:       None
Argout:      None
return:      random number in the region of [0,1]
*****************************************************************************************************************/
double QuantumGates::randGenerator()
{
    /*
     *  difine constant number in 16807 generator.
     */
    int  ia = 16807, im = 2147483647, iq = 127773, ir = 2836;
#ifdef _WIN32
    time_t rawtime;
    struct tm  timeinfo;
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);
    static int irandseed = timeinfo.tm_year + 70 *
                           (timeinfo.tm_mon + 1 + 12 *
                            (timeinfo.tm_mday + 31 *
                             (timeinfo.tm_hour + 23 *
                              (timeinfo.tm_min + 59 * timeinfo.tm_sec))));
#elif __linux__
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo  = localtime(&rawtime);

    static int irandseed = timeinfo->tm_year + 70 *
                           (timeinfo->tm_mon + 1 + 12 *
                            (timeinfo->tm_mday + 31 *
                             (timeinfo->tm_hour + 23 *
                              (timeinfo->tm_min + 59 * timeinfo->tm_sec))));   
#endif
    static int irandnewseed = 0;
    if (ia * (irandseed % iq) - ir * (irandseed / iq) >= 0)
    {
        irandnewseed = ia * (irandseed % iq) - ir * (irandseed / iq);
    }
    else
    {
        irandnewseed = ia * (irandseed % iq) - ir * (irandseed / iq) + im;
    }
    irandseed = irandnewseed;
    return (double)irandnewseed / im;
}
