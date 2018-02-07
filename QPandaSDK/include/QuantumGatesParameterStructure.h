/*****************************************************************************************************************
Copyright:
Author:Dou Menghan
Date:2017-11-20
Description:quantum gates parameter
*****************************************************************************************************************/
#pragma once
/*****************************************************************************************************************
Parameter:gates parameter parent
*****************************************************************************************************************/
struct Parameter
{
    int    iGatesType;                                                  /* gate type                            */
    size_t stNumber;                                                    /* gate number                          */
    size_t stSize;                                                      /* gate parameter                       */
    int    iDagger;                                                     /* gate is dagger                       */
};

/*****************************************************************************************************************
HadamardParameter: Hadamard gates parameter 
*****************************************************************************************************************/
struct HadamardParameter : Parameter
{
    size_t stQubitNumber;                                               /* qubit number                         */
    double dErrorRate;                                                  /* error rate                           */
    int    iControlBitNumber;                                           /* control bit number                   */
};

/*****************************************************************************************************************
HadamardParameter: Hadamard gates parameter
*****************************************************************************************************************/
struct ResetParameter : Parameter
{
    size_t stQubitNumber;                                               /* qubit number                         */
    double dErrorRate;                                                  /* error rate                           */
    int    iControlBitNumber;                                           /* control bit number                   */
};


/*****************************************************************************************************************
RGatesParameter: R gates parameter
*****************************************************************************************************************/
struct RGatesParameter : Parameter
{
    size_t stQubitNumber;                                               /* qubit number                         */
    double dTheta;                                                      /* theta                                */
    double dErrorRate;                                                  /* error rate                           */
    int    iControlBitNumber;                                           /* control bit number                   */
};

/*****************************************************************************************************************
CNOTParameter: CNOT gates parameter
*****************************************************************************************************************/
struct CNOTParameter :Parameter
{
    size_t stQubitNumber1;                                              /* qubit number 1                       */
    size_t stQubitNumber2;                                              /* qubit number 2                       */
    double dErrorRate;                                                  /* error rate                           */
    int    iControlBitNumber;                                           /* control bit number                   */
};

/*****************************************************************************************************************
TOFFOLIParameter: TOFFOLI gates parameter
*****************************************************************************************************************/
struct TOFFOLIParameter :Parameter
{
    size_t stControlBit1;                                               /* first control qubit                  */
    size_t stControlBit2;                                               /* second control qubit                  */
    size_t stQuantumBit;                                                /* target qubit number                  */
    double dErrorRate;                                                  /* error rate                           */
    int    iControlBitNumber;                                           /* control bit number                   */
};

/*****************************************************************************************************************
NOTParameter: NOT gates parameter
*****************************************************************************************************************/
struct NOTParameter :Parameter
{
    size_t stQubitNumber;                                               /* qubit number                         */
    double dErrorRate;                                                  /* error rate                           */
    int    iControlBitNumber;                                           /* control bit number                   */
};

/*****************************************************************************************************************
CRParameter: CR gates parameter
*****************************************************************************************************************/
struct CRParameter : Parameter
{
    size_t stQubitNumber1;                                              /* control qubit number 1               */
    size_t stQubitNumber2;                                              /* qubit number 2                       */
    double dTheta;                                                      /* theta                                */
    double dErrorRate;                                                  /* error rate                           */
    int    iControlBitNumber;                                           /* control bit number                   */
};

/*****************************************************************************************************************
iSWAPParameter: iSWAP gates parameter
*****************************************************************************************************************/
struct iSWAPParameter : Parameter
{
    size_t stQubitNumber1;                                              /* qubit number 1                       */
    size_t stQubitNumber2;                                              /* qubit number 2                       */
    double dErrorRate;                                                  /* error rate                           */
    int    iControlBitNumber;                                           /* control bit number                   */
};

/*****************************************************************************************************************
sqiSWAPParameter: sqiSWAP gates parameter
*****************************************************************************************************************/
struct sqiSWAPParameter : Parameter
{
    size_t stQubitNumber1;                                              /* qubit number 1                       */
    size_t stQubitNumber2;                                              /* qubit number 2                       */
    double dErrorRate;                                                  /* error rate                           */
    int    iControlBitNumber;                                           /* control bit number                   */
};

/*****************************************************************************************************************
controlSwapParameter: controlSwap gates parameter
*****************************************************************************************************************/
struct controlSwapParameter : Parameter
{
    size_t stcontrolQubitNumber;                                        /* control qubit number                 */
    size_t stQubitNumber1;                                              /* qubit number 1                       */
    size_t stQubitNumber2;                                              /* qubit number 2                       */
    double dErrorRate;                                                  /* error rate                           */
    int    iControlBitNumber;                                           /* control bit number                   */
};

/*****************************************************************************************************************
qubitMeasureParameter: qubit measure parameter
*****************************************************************************************************************/
struct qubitMeasureParameter : Parameter
{
    size_t stQubitNumber;                                               /* qubit number                         */
    size_t creg;
    int    iControlBitNumber;                                           /* control bit number                   */
};
/*****************************************************************************************************************
pMeasure: qubit measure probability
*****************************************************************************************************************/
struct pMeasureParameter:Parameter
{
    int iPMeasureListSize;
};

/*****************************************************************************************************************
unitarySingleQubitGateParameter: unitary single qubit gate parameter
*****************************************************************************************************************/
struct  unitarySingleQubitGateParameter : Parameter
{
    size_t stQubitNumber;                                               /* qubit number                         */
    double dMatrix11real;                                               /* Matrix1 real                         */
    double dMatrix12img;                                                /* Matrix1 img                          */
    double dMatrix21real;                                               /* Matrix2 real                         */ 
    double dMatrix22img;                                                /* Matrix2 img                          */
    double dMatrix31real;                                               /* Matrix3 real                         */
    double dMatrix32img;                                                /* Matrix3 img                          */
    double dMatrix41real;                                               /* Matrix4 real                         */
    double dMatrix42img;                                                /* Matrix4 img                          */
    double dErrorRate;                                                  /* error rate                           */
    int    iControlBitNumber;                                           /* control bit number                   */
};

