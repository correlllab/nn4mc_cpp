
#include "neural_network.h"

void buildLayers(){

   
        conv1d_1 = malloc(sizeof(struct Conv1D));  
        conv1d_1 = buildConv1D(&conv1d_1[0][0][0], conv1d_1, 4, 1, 50, 2, 8);

        conv1d_2 = malloc(sizeof(struct Conv1D));  
        conv1d_2 = buildConv1D(&conv1d_2[0][0][0], conv1d_2, 4, 1, 47, 8, 8);

        dense_1 = malloc(sizeof(struct Dense));
        dense_1 = buildDense(&dense_1[0][0], dense_1, 44, 64, 'l');

        dense_2 = malloc(sizeof(struct Dense));
        dense_2 = buildDense(&dense_2[0][0], dense_2, 64, 42, 'l');

        dense_3 = malloc(sizeof(struct Dense));
        dense_3 = buildDense(&dense_3[0][0], dense_3, 42, 28, 'l');

        dense_4 = malloc(sizeof(struct Dense));
        dense_4 = buildDense(&dense_4[0][0], dense_4, 28, 18, 'l');

        dense_5 = malloc(sizeof(struct Dense));
        dense_5 = buildDense(&dense_5[0][0], dense_5, 18, 12, 'l');

        dense_6 = malloc(sizeof(struct Dense));
        dense_6 = buildDense(&dense_6[0][0], dense_6, 12, 8, 'l');

        dense_7 = malloc(sizeof(struct Dense));
        dense_7 = buildDense(&dense_7[0][0], dense_7, 8, 5, 'l');

        dense_8 = malloc(sizeof(struct Dense));
        dense_8 = buildDense(&dense_8[0][0], dense_8, 5, 3, 'l');
 

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

