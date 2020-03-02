
#include "neural_network.h"
#include <stdlib.h>

void buildLayers(){

   
        dense_39 = buildDense(&dense_39_W[0], dense_39_b, 2, 20, 0x06);

        dense_40 = buildDense(&dense_40_W[0], dense_40_b, 20, 10, 0x06);

        dense_41 = buildDense(&dense_41_W[0], dense_41_b, 10, 1, 0x08);
 

}


float * fwdNN(float* data)
{

   
        data = fwdDense(dense_39, data);

        data = fwdDense(dense_40, data);

        data = fwdDense(dense_41, data);
 

    return data;
}

