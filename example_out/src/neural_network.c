#include "neural_network.h"

void buildNN()
{
   
Conv1D layer1 = buildConv1D(conv1_weight, conv1_bias, 5, <%STRIDE_SIZE>, 1, <%OUTPUT_CHANNELS>, 1);

Dense layer2 = buildDense(dense_weight, dense_bias, 1, <%OUTPUT_SIZE>);
 
}

void fwdNN(<%WEIGHT_DATATYPE>* input)
{
   
input = fwdConv1D(layer1, input, <%OUTPUT>);

input = fwdDense(layer2, input, <%OUTPUT>);
 
}
