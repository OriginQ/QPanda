#pragma once
#define STATE_T double

namespace GATEGPU
{

    struct probability
    {
        STATE_T prob;
        int state;
    };

    struct QState
    {
        STATE_T * real;
        STATE_T * imag;
        int qnum;
    };
}

