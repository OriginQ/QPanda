%module QPandaAPI
%include "std_string.i"
%include "cpointer.i"
%pointer_class(int,intp); 
using std::string;

%{
#include "QPandaAPI.h"

%}
%apply char * {std::string &x};
%include QPandaAPI.h
%include ../QuantumInstructionHandle/QError.h
