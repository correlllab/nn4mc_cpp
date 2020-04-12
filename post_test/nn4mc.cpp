
/********************
    nn4mc.cpp

    Code generated using nn4mc.

    This file implements the nerual network and associated functions.

*/

#ifdef __cplusplus
extern "C" {

#include "nn4mc.h"
#include <stdlib.h>

void buildLayers(){

   
        conv2d = buildConv2D(&conv2d_W[0], conv2d_b, 1, 1, 7, 1, 1, 1, 12, 1, 0xB, 0x00, 0x00,1, 1);

        dense = buildDense(&dense_W[0], dense_b, 84, 8, 0x06);

        dense_1 = buildDense(&dense_1_W[0], dense_1_b, 8, 1, 0xB);
 

}


float * fwdNN(float* data)
{

   
        data = fwdConv2D(conv2d, data);

        data = fwdDense(dense, data);

        data = fwdDense(dense_1, data);
 

    return data;
}

}
#endif
