
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
#include "layers/conv1d.h"
#include "layers/conv1d.h"
#include "layers/dense.h"
#include "layers/dense.h"
#include "layers/dense.h"
#include "layers/dense.h"
#include "layers/dense.h"
#include "layers/dense.h"
#include "layers/dense.h"
#include "layers/dense.h"


volatile int num_layers = 0;

struct conv1d *conv1d_1;
struct conv1d *conv1d_2;
struct dense *dense_1;
struct dense *dense_2;
struct dense *dense_3;
struct dense *dense_4;
struct dense *dense_5;
struct dense *dense_6;
struct dense *dense_7;
struct dense *dense_8;



float fwdNN(float*);

#endif

