
/********************

    NEURAL_NETWORK_H

Code Generated using nn4mc

*/

#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "neural_network_params.h"
#include "layers/conv2d.h"
#include "layers/conv2d.h"
#include "layers/dense.h"
#include "layers/dense.h"
#include "layers/maxpool2d.h"


struct Conv2D *conv2d_1;
struct Conv2D *conv2d_2;
struct Dense *dense_1;
struct Dense *dense_2;
struct MaxPooling2D *max_pooling2d_1;



float* fwdNN(float*);
void buildLayers();


#endif

