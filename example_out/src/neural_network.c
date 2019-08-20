#include "neural_network.h"

void buildNN()
{
   
Conv1D layer1 = buildConv1D(conv1_weight, conv1_bias, 5, <%STRIDE_SIZE>, 1, <%OUTPUT_CHANNELS>, 1);

Dense layer2 = buildDense(conv1_weight, conv1_bias, 1, <%OUTPUT_SIZE>);
 
}

void fwdNN(<%WEIGHT_DATATYPE>* input, <%WEIGHT_DATATYPE>* output)
{
    
}
