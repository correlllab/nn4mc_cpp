
/********************
    nn4mc.h

    Code generated using nn4mc.

    This file defines a a neural network and associated functions.

*/

#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#ifdef __cplusplus
extern "C" {

#include "parameters.h"
#include "conv1d.h"
#include "conv1d.h"
#include "dense.h"
#include "dense.h"
#include "dense.h"
#include "dense.h"
#include "dense.h"
#include "dense.h"
#include "dense.h"
#include "dense.h"


struct Conv1D conv1d_1;
struct Conv1D conv1d_2;
struct Dense dense_1;
struct Dense dense_2;
struct Dense dense_3;
struct Dense dense_4;
struct Dense dense_5;
struct Dense dense_6;
struct Dense dense_7;
struct Dense dense_8;


float* fwdNN(float*);
void buildLayers();

}
#endif
#endif

