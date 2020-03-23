
#include "neural_network.h"
#include <stdlib.h>

void buildLayers(){

   
        lstm_1 = buildLSTM();

        dense_1 = buildDense(&dense_1_W[0], dense_1_b, 1, 8, 0x06);

        dense_2 = buildDense(&dense_2_W[0], dense_2_b, 8, 1, 0xB);
 

}


float * fwdNN(float* data)
{

   
        data = fwdLSTM(lstm_1, data);

        data = fwdDense(dense_1, data);

        data = fwdDense(dense_2, data);
 

    return data;
}

