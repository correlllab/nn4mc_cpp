
#include "neural_network.h"

void buildLayers(){

   
        conv1d_1 = malloc(sizeof(struct Conv1D));  
        conv1d_1 = buildConv1D(&conv1d_1_b[0][0][0], conv1d_1_W, 4, 1, 50, 2, 8);

        conv1d_2 = malloc(sizeof(struct Conv1D));  
        conv1d_2 = buildConv1D(&conv1d_2_b[0][0][0], conv1d_2_W, 4, 1, 47, 8, 8);

        dense_1 = malloc(sizeof(struct Dense));
        dense_1 = buildDense(&dense_1_b[0][0], dense_1_W, 352, 64, 0x06);

        dense_2 = malloc(sizeof(struct Dense));
        dense_2 = buildDense(&dense_2_b[0][0], dense_2_W, 64, 42, 0x06);

        dense_3 = malloc(sizeof(struct Dense));
        dense_3 = buildDense(&dense_3_b[0][0], dense_3_W, 42, 28, 0x06);

        dense_4 = malloc(sizeof(struct Dense));
        dense_4 = buildDense(&dense_4_b[0][0], dense_4_W, 28, 18, 0x06);

        dense_5 = malloc(sizeof(struct Dense));
        dense_5 = buildDense(&dense_5_b[0][0], dense_5_W, 18, 12, 0x06);

        dense_6 = malloc(sizeof(struct Dense));
        dense_6 = buildDense(&dense_6_b[0][0], dense_6_W, 12, 8, 0x06);

        dense_7 = malloc(sizeof(struct Dense));
        dense_7 = buildDense(&dense_7_b[0][0], dense_7_W, 8, 5, 0x06);

        dense_8 = malloc(sizeof(struct Dense));
        dense_8 = buildDense(&dense_8_b[0][0], dense_8_W, 5, 3, 0xB);
 

}


float * fwdNN(float* data)
{
  
   
        data = fwdConv1D(conv1d_1, data);

        data = fwdConv1D(conv1d_2, data);

        data = fwdDense(dense_1, data);

        data = fwdDense(dense_2, data);

        data = fwdDense(dense_3, data);

        data = fwdDense(dense_4, data);

        data = fwdDense(dense_5, data);

        data = fwdDense(dense_6, data);

        data = fwdDense(dense_7, data);

        data = fwdDense(dense_8, data);
 

    return data;
}

