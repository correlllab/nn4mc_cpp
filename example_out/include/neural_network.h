#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include "neural_network_params.h"


volatile int num_layers = <%NUMBER_OF_LAYERS>;

<%STRUCTS>

void buildNN();
void fwdNN(<%WEIGHT_DATATYPE>*, <%WEIGHT_DATATYPE>*);

#endif