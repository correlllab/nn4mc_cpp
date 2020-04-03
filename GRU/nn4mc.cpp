
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

   
        gru = buildGRU();

        dense = buildDense(&dense_W[0], dense_b, 1, 8, 0x06);

        dense_1 = buildDense(&dense_1_W[0], dense_1_b, 8, 1, 0xB);
 

}


float * fwdNN(float* data)
{

   
        data = fwdGRU(gru, data);

        data = fwdDense(dense, data);

        data = fwdDense(dense_1, data);
 

    return data;
}

}
#endif
