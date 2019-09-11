
include "neural_network.h"

float * fwdNN(float* data)
{
  
        struct Conv1D layer1 = buildConv1D(&conv1_weight[0][0][0], conv1_bias, 5, 3, 1, 2, 1);

        struct Dense layer2 = buildDense(&dense_weight[0][0], dense_bias, , 5, 'l');
 

   
        data = fwdConv1D(layer1, data);

        data = fwdDense(layer2, data);
 

    return data;
}

