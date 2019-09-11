
#include "neural_network.h"

void buildLayers(){

   
        dense_1 = malloc(sizeof(struct Dense));
        dense_1 = buildDense(&dense_1[0][0], dense_1, 
, 10, 'l');

        dense_2 = malloc(sizeof(struct Dense));
        dense_2 = buildDense(&dense_2[0][0], dense_2, 
, 10, 'l');

        dense_3 = malloc(sizeof(struct Dense));
        dense_3 = buildDense(&dense_3[0][0], dense_3, 
, 3, 'l');
 

}


float * fwdNN(float* data)
{
  
   
        data = fwdDense(dense_1, data);

        data = fwdDense(dense_2, data);

        data = fwdDense(dense_3, data);
 

    return data;
}

