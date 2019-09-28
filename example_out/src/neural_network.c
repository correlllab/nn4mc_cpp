
#include "neural_network.h"
#include <stdlib.h>

void buildLayers(){

   
/*(* W, * b,                                 kernel_shape_0,  kernel_shape_1,         kernel_shape_2,  filters,  strides_0,                                 strides_1,  input_shape_0,
 * input_shape_1, input_shape_2)*/
        conv2d_1 = malloc(sizeof (struct Conv2D)); 
        conv2d_1 = buildConv2D(, , 3, 3, ,  0, 1, 1, 28, 28, 1);

/*(* W, * b,                                 kernel_shape_0,  kernel_shape_1,         kernel_shape_2,  filters,  strides_0,                                 strides_1,  input_shape_0,
 * input_shape_1, input_shape_2)*/
        conv2d_2 = malloc(sizeof (struct Conv2D)); 
        conv2d_2 = buildConv2D(, , 3, 3, ,  0, 1, 1, 5, 5, 5);

        dense_1 = malloc(sizeof(struct Dense));
        dense_1 = buildDense(&dense_1_W[0], dense_1_b, 25, 128, 0x06);

        dense_2 = malloc(sizeof(struct Dense));
        dense_2 = buildDense(&dense_2_W[0], dense_2_b, 640, 10, 0x00);

        max_pooling2d_1 = malloc(sizeof(struct MaxPooling1D));
        max_pooling2d_1 = buildMaxPooling1D(, , 10,  5);
 

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

