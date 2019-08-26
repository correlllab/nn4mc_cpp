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



const float W_conv1_weight[24] = {  0.840188,  0.394383,  0.783099,  0.79844,
                                    0.911647,  0.197551,  0.335223,  0.76823,
                                    0.277775,  0.55397,  0.477397,  0.628871,
                                    0.364784,  0.513401,  0.95223,  0.916195,
                                    0.635712,  0.717297,  0.141603,  0.606969,
                                    0.0163006,  0.242887,  0.137232,  0.804177};



const float W_conv1_bias[4] = {0.156679, 0.400944, 0.12979, 0.108809};



const float W_conv1_weight[24] = {  0,  0.394383,  0.783099,  0.79844,
                                    0.911647,  0.197551,  0.335223,  0.76823,
                                    0.277775,  0.55397,  0.477397,  0.628871,
                                    0.364784,  0.513401,  0.95223,  0.916195,
                                    0.635712,  0.717297,  0.141603,  0.606969,
                                    0.0163006,  0.242887,  0.137232,  0.804177};



const float W_conv1_bias[4] = {4.67436e-310, 0.400944, 0.12979, 0.108809};




#ifdef __cplusplus
}

#endif
#endif
