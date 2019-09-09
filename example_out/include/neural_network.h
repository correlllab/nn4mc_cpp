#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include "neural_network_params.h"
#include "layers/conv1d.h"
#include "layers/dense.h"


volatile int num_layers = 0;

/*
conv1d layer1;
dense layer2;

*/

<%WEIGHT_DATATYPE> fwdNN(<%WEIGHT_DATATYPE>*);

#endif
