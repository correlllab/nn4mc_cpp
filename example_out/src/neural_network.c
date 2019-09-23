
#include "neural_network.h"

void buildLayers(){

   
        conv1d_1 = malloc(sizeof(struct Conv1D));  
        conv1d_1 = buildConv1D(&conv1d_1_W[0][0][0], conv1d_1_b, 4, 1, 200, 1, 8);

        dense_1 = malloc(sizeof(struct Dense));
        dense_1 = buildDense(&dense_1_W[0][0], dense_1_b, 1576, 20, 0x06);

        dense_2 = malloc(sizeof(struct Dense));
        dense_2 = buildDense(&dense_2_W[0][0], dense_2_b, 20, 10, 0xB);

        dense_3 = malloc(sizeof(struct Dense));
        dense_3 = buildDense(&dense_3_W[0][0], dense_3_b, 10, 2, 0xB);
 

}


float * fwdNN(float* data)
{
  
   
        data = fwdConv1D(conv1d_1, data);

        data = fwdDense(dense_1, data);

        data = fwdDense(dense_2, data);

        data = fwdDense(dense_3, data);
 

    return data;
}

