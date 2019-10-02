
#include "neural_network.h"
#include <stdlib.h>

void buildLayers(){

   
        dense_1 = buildDense(&dense_1_W[0], dense_1_b, 10, 10, 0xB);

        dense_2 = buildDense(&dense_2_W[0], dense_2_b, 10, 10, 0xB);

        dense_3 = buildDense(&dense_3_W[0], dense_3_b, 10, 3, 0xB);
 

}


float * fwdNN(float* data)
{
  
   
        data = fwdDense(dense_1, data);

        data = fwdDense(dense_2, data);

        data = fwdDense(dense_3, data);
 

    return data;
}

