
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
#include "conv2d.h"
#include "conv2d.h"
#include "maxpool2d.h"
#include "dense.h"
#include "dense.h"


struct Conv2D conv2d_1;
struct Conv2D conv2d_2;
struct MaxPooling2D max_pooling2d_1;
struct Dense dense_1;
struct Dense dense_2;


float* fwdNN(float*);
void buildLayers();

}
#endif
#endif

