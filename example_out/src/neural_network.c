
include "neural_network.h"

void buildLayers(){

   
        layer1 = malloc(sizeof(struct Conv1D));  
        layer1 = buildConv1D(&conv1_weight[0][0][0], conv1_bias, 5, 3, 1, 2, 1);

        layer2 = malloc(sizeof(struct Dense));
        layer2 = buildDense(&dense_weight[0][0], dense_bias, , 5, 'l');
 

}


float * fwdNN(float* data)
{
  
   
        data = fwdConv1D(layer1, data);

        data = fwdDense(layer2, data);
 

    return data;
}

