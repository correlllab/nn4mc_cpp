 /* example.i */
%module example
%{
     /* Put header files here or function declarations like below */
#include "activations.h"
#include "parameters.h"
%}

%include activations.h
%include parameters.h

