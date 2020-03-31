
/********************
    lstm.cpp

    Code generated using nn4mc.

    This file implements a long short term memory layer.

*/

#include "lstm.h"
#include "activation_func.h"
#include <math.h>
#include <stdlib.h>

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

struct LSTM buildLSTM(const float * W, const float * Wrec, const float * b, int input_sh0, int input_sh1, int output_sh, char activation, char recurrent_activation, float dropout, float recurrent_dropout, bool go_backwards)
{
	struct LSTM layer;

	layer.weights = W;
	layer.biases = b;

    layer.input_shape[0] = input_sh0;
    layer.input_shape[1] = input_sh1;

    layer.activation = activation;
    layer.recurrent_activation = recurrent_activation;

    layer.output_size = output_sh; 

    layer.dropout = dropout;
    layer.recurrent_dropout;

    layer.go_backwards = go_backwards;

	return layer;
}

float * fwdLSTM(struct LSTM L, float* x)
{

    float * h = (float*)malloc(layer.output_size*layer.output_size*sizeof(float));

    float * forget_gate = (float*)malloc(layer.output_size*sizeof(float));
    float * input_gate = (float*)malloc(layer.output_size*sizeof(float));
    float * cell_state = (float*)malloc(layer.output_size*sizeof(float));
   float * output_gate = (float*)malloc(layer.output_size*sizeof(float));

    for (int t = 0; t < L.output_size; t++){
        for(int i = 0 ; i < L.output_size; i++){
                                               
        } 
    }       

    
    free(forget_gate);
    free(input_gate);
    free(cell_state);
    free(output_gate);

    free(x);
    return h;
}

