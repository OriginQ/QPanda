
#include "QRState.h"

namespace QRunes
{
    /********************************************************************
    Name:           Hadamard
    Description:    in ofstream output the cmd
    Argin:          reference of qubit
    Argout:         reference of qubit -> after gate
    return:         n/a
    ********************************************************************/
    void Hadamard(qubit&);

    /********************************************************************
    Name:           CNOT
    Description:    in ofstream output the cmd
    Argin:          reference of qubit1&2 ( 1 control 2 target )
    Argout:         reference of qubit1&2 -> after gate
    return:         n/a
    ********************************************************************/
    void CNOT(qubit&, qubit&);

    void BEGIN_DAGGER();

    void END_DAGGER();

    void BEGIN_CONTROL(qubit&);

    void END_CONTROL(qubit&);

    void RX(qubit&, double);

	void X(qubit& q);

    void RY(qubit&, double);

    void RZ(qubit&, double);

    void CR(qubit&, qubit&, double);

    void Measure(qubit&);

	void Toffoli(qubit& q1, qubit& q2, qubit& q3);
    
}