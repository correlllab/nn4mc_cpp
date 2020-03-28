
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
#include "simplernn.h"
#include "dense.h"
#include "dense.h"


struct SimpleRNN simple_rnn;
struct Dense dense;
struct Dense dense_1;


float* fwdNN(float*);
void buildLayers();

}
#endif
#endif

