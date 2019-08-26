/*************
* neural_net_params.h
*
* Neural Network Parameters
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



<<<<<<< HEAD
const float W_conv1_bias[4] = {0.156679, 0.400944, 0.12979, 0.108809};



const float W_conv1_weight[24] = {  0,  0.394383,  0.783099,  0.79844,
                                    0.911647,  0.197551,  0.335223,  0.76823,
                                    0.277775,  0.55397,  0.477397,  0.628871,
                                    0.364784,  0.513401,  0.95223,  0.916195,
                                    0.635712,  0.717297,  0.141603,  0.606969,
                                    0.0163006,  0.242887,  0.137232,  0.804177};
=======
const float W_conv1_bias[4] = {0.846167, 0.526929, 0.0919649, 0.653919};



const float W_conv1_weight[24] = {  7.82637e-06,  0.131538,  0.755605,  0.45865,
                                    0.532767,  0.218959,  0.0470446,  0.678865,
                                    0.679296,  0.934693,  0.383502,  0.519416,
                                    0.830965,  0.0345721,  0.0534616,  0.5297,
                                    0.671149,  0.00769819,  0.383416,  0.0668422,
                                    0.417486,  0.686773,  0.588977,  0.930436};



const float W_conv1_bias[4] = {0.846167, 0.526929, 0.0919649, 0.653919};
>>>>>>> 1a9786f4e2583d31e858dda42b28b595ded991e3



const float W_conv1_bias[4] = {4.67436e-310, 0.400944, 0.12979, 0.108809};




#ifdef __cplusplus
}

#endif
#endif
