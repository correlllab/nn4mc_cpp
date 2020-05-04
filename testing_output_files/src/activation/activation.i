/* File: activation.i:

    This is the file that gives us enough to wrap the code. 
    Here we introduce headers that import the functions or header
    files. Since activations.h also imports all of the function 
    prototypes from activation.cpp, you only need to import the 
    header.
*/

%include "../../code_test/activations.cpp"
%include "../../code_test/activations.h"

%module activation
%{
 extern float activate(float input, int output_shape, char type);
 
 extern float sigmoid(float input);
 
 extern float softplus(float input);
 
 extern float softsign(float input);
 
 extern float hard_sigmoid(float input);
 
 extern float exponential(float input);
 
 extern float relu(float input);
 
 extern float hyper_tan(float input);
 
 extern float softmax(float input, int output_shape);

%}

 extern float activate(float input, int output_shape, char type);
 
 extern float sigmoid(float input);
 
 extern float softplus(float input);
 
 extern float softsign(float input);
 
 extern float hard_sigmoid(float input);
 
 extern float exponential(float input);
 
 extern float relu(float input);
 
 extern float hyper_tan(float input);
 
 extern float softmax(float input, int output_shape);


