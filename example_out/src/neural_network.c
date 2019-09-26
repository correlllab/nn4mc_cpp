
#include "neural_network.h"

void buildLayers(){

   
        conv2d_1 = malloc(sizeof (struct Conv2D)); 
        conv2d_1 = buildConv2D(, , , , , , );

        conv2d_2 = malloc(sizeof (struct Conv2D)); 
        conv2d_2 = buildConv2D(, , , , , , );

        dense_1 = malloc(sizeof(struct Dense));
        dense_1 = buildDense(&dense_1_W[0][0], dense_1_b, 25, 500, 0xB);

        dense_2 = malloc(sizeof(struct Dense));
        dense_2 = buildDense(&dense_2_W[0][0], dense_2_b, 2500, 2, 0xB);

        max_pooling2d_1 = malloc(sizeof(struct MaxPooling1D));
        max_pooling2d_1 = buildMaxPooling1D(, , 1,  2);

        max_pooling2d_2 = malloc(sizeof(struct MaxPooling1D));
        max_pooling2d_2 = buildMaxPooling1D(, , 1,  2);
 

}


float * fwdNN(float* data)
{
  
   
        data2D = fwdConv2D(conv2d_1, data, <%OUTPUT>);

        data2D = fwdConv2D(conv2d_2, data, <%OUTPUT>);

        data = fwdDense(dense_1, data);

        data = fwdDense(dense_2, data);

        data = fwdMaxPooling1D(max_pooling2d_1, data);

        data = fwdMaxPooling1D(max_pooling2d_2, data);
 

    return data;
}

