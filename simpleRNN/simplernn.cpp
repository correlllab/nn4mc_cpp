
/********************
    simplernn.cpp

    Code generated using nn4mc.

    This file implements a simple recurret layer.

*/

#include "simplernn.h"
#include "activation_func.h"
#include <math.h>
#include <stdlib.h>

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

struct SimpleRNN buildSimpleRNN(const float * W, const float * b, int input_sh0, int input_sh1, int output_sh, char activation)
{
	struct SimpleRNN layer;

	layer.weights = W;
	layer.biases = b;

    layer.input_shape[0] = input_sh0;
    layer.input_shape[1] = input_sh1;
    
    layer.activation = activation;
    layer.window_size= output_sh;

    layer.output_shape = output_sh;

    S = (float*)malloc(layer.input_shape[0]*(layer_input_shape[1]+1) * sizeof(float)); // rolling window

	return layer;
}

float * fwdSimpleRNN(struct SimpleRNN L, float* input)
{

    for (int i=0; i < L.input_shape[0]*(L.window_size+1); i++) S[i] = 0.0;

    for (int j=0 ;  j < L.output_shape; j++)  {
        for (int i=0; i< L.input_shape[0]*L.input_shape[1]; i++){
            for (int k = 0; k< L.window_size+1; k++){

                int index = i*L.window_size + k+1;
                int index_before = i*window_size + k;
                int bias_matrix_index = k*L.output_shape + i;
                S[index] = input[i]*L.biases[bias_matrix_index] + S[index_before] * *(L.weights + i*L.output_shape + k);
            }
        }
    }

    free(input);
    return h;
}

