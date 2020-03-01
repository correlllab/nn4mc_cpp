
/********************
    nn4mc.h

    Code generated using nn4mc.

    This file defines a a neural network and associated functions.

*/

#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#ifdef __cplusplus
extern "C" {

#include "neural_network_params.h"
#include "conv1d.h"
#include "dense.h"


struct Conv1D layer1;
struct Dense layer2;


float* fwdNN(float*);
void buildLayers();

}
#endif
#endif

