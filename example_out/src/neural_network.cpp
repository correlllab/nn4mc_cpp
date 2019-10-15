
#include "neural_network.h"
#include <stdlib.h>

void buildLayers(){

   
        conv2d_1 = buildConv2D(&conv2d_1_W[0], conv2d_1_b, 2, 2, 5, 1, 1, 28, 28, 1, 0x06);

        conv2d_2 = buildConv2D(&conv2d_2_W[0], conv2d_2_b, 2, 2, 3, 1, 1, 27, 27, 5, 0x06);

        dense_1 = buildDense(&dense_1_W[0], dense_1_b, 26, 10, 0x06);

        dense_2 = buildDense(&dense_2_W[0], dense_2_b, 10, 10, 0x00);

        max_pooling2d_1 = buildMaxPooling2D(2,2, 2,2, 26,  26, 3);
 

}


float * fwdNN(float* data)
{
  
   
        data = fwdConv2D(conv2d_1, data);

        data = fwdConv2D(conv2d_2, data);

        data = fwdDense(dense_1, data);

        data = fwdDense(dense_2, data);

        data = fwdMaxPooling2D(max_pooling2d_1, data);
 

    return data;
}

