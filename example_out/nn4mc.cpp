
/********************
    nn4mc.cpp

    Code generated using nn4mc.

    This file implements the nerual network and associated functions.

*/

#ifdef __cplusplus
#extern "C" {

#include "neural_network.h"
#include <stdlib.h>

void buildLayers(){

   
        layer1 = buildConv1D(&conv1_weight[0], conv1_bias, 5, 3, 1, 2, 1, );

        layer2 = buildDense(&dense_weight[0], dense_bias, 1, 5, 0xB);
 

}


float * fwdNN(float* data)
{

   
        data = fwdConv1D(layer1, data);

        data = fwdDense(layer2, data);
 

    return data;
}

}
#endif
