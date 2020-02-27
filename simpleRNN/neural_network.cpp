
#include "neural_network.h"
#include <stdlib.h>

void buildLayers(){

   
        simple_rnn_1 = buildSimpleRNN();
 

}


float * fwdNN(float* data)
{

   
        data = fwdSimpleRNN(simple_rnn_1, data);
 

    return data;
}

