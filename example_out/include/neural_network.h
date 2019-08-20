#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include "neural_network_params.h"
#include "layers/conv1d.h"
#include "layers/dense.h"


volatile int num_layers = <%NUMBER_OF_LAYERS>;

conv1d layer1;
dense layer2;


void buildNN();
void fwdNN(<%WEIGHT_DATATYPE>*, <%WEIGHT_DATATYPE>*);

#endif