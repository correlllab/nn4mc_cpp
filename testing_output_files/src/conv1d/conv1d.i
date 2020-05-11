/* File: activation.i:

    This is the file that gives us enough to wrap the code. 
    Here we introduce headers that import the functions or header
    files. Since activations.h also imports all of the function 
    prototypes from activation.cpp, you only need to import the 
    header.
*/
%include "../../code_test/conv1d.cpp"
%include "../../code_test/conv1d.h"
%include "../../code_test/parameters.h"
%include "../../code_test/activations.h"
%include "../../code_test/activations.cpp"

%module conv1d
%{
#include "../../code_test/conv1d.h"
#include "../../code_test/parameters.h"
#include "../../code_test/activations.h"
extern float softplus(float);

%}
extern float activate(float, int, char);
extern float softplus(float);
