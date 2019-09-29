
#include "neural_network.h"
#include <stdlib.h>

void buildLayers(){

   
        conv2d_1 = malloc(sizeof (struct Conv2D)); 
        conv2d_1 = buildConv2D(&conv2d_1_W[0], conv2d_1_b, 3, 3, 32, 1, 1, 28, 28, 1);

        conv2d_2 = malloc(sizeof (struct Conv2D)); 
        conv2d_2 = buildConv2D(&conv2d_2_W[0], conv2d_2_b, 3, 3, 64, 1, 1, 5, 5, 5);

        dense_1 = malloc(sizeof(struct Dense));
        dense_1 = buildDense(&dense_1_W[0], dense_1_b, 10, 128, 0x06);

        dense_2 = malloc(sizeof(struct Dense));
        dense_2 = buildDense(&dense_2_W[0], dense_2_b, 256, 10, 0x00);

        max_pooling2d_1 = malloc(sizeof(struct MaxPooling1D));
        max_pooling2d_1 = buildMaxPooling1D(2,2, 2,2, 5,  5);
 

}


float * fwdNN(float* data)
{
  
   
        data = fwdConv2D(conv2d_1, data);

        data = fwdConv2D(conv2d_2, data);

        data = fwdDense(dense_1, data);

        data = fwdDense(dense_2, data);

        data = fwdMaxPooling1D(max_pooling2d_1, data);
 

    return data;
}

