/*************
* neural_net_params.h
*
* Neural Network Parameters
* Code Generated using nn4mc
* Hardware Plateform: ESP-32
*
* This file defines the weights used by the neural network implementation.  Weight representations were
* created automatically using nn4mp.
*/

#ifndef __NEURAL_NET_PARAMS_H__
#define __NEURAL_NET_PARAMS_H__

#ifdef __cpluscplus
extern "C" {
#endif




const float W_conv1_weight[24] = {  7.82637e-06,  0.131538,  0.755605,  0.45865,
                                     0.532767,  0.218959,  0.0470446,  0.678865,
                                     0.679296,  0.934693,  0.383502,  0.519416,
                                     0.830965,  0.0345721,  0.0534616,  0.5297,
                                     0.671149,  0.00769819,  0.383416,  0.0668422,
                                     0.417486,  0.686773,  0.588977,  0.930436};



const float W_conv1_bias[4] = {0.846167, 0.526929, 0.0919649, 0.653919};



const float W_dense_weight[24] = {  0.415999,  0.701191,  0.910321,  0.762198,
                                     0.262453,  0.0474645,  0.736082,  0.328234,
                                     0.632639,  0.75641,  0.991037,  0.365339,
                                     0.247039,  0.98255,  0.72266,  0.753356,
                                     0.651519,  0.0726859,  0.631635,  0.884707,
                                     0.27271,  0.436411,  0.766495,  0.477732};



const float W_dense_bias[4] = {0.237774, 0.274907, 0.359265, 0.166507};



#ifdef __cplusplus
}

#endif
#endif
