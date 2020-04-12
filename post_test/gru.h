
/********************
    gru.h

    Code generated using nn4mc.

    This file defines a gated recurrent unit layer.

*/

#ifndef __GRU_H__
#define __GRU_H__

#include <stdbool.h>

struct GRU {
	// Weights and biases defining the layer
	const float* weights;			// Pointer to constant weight array
	const float* biases;				// Pointer to constant bias
    const float* wrec;

    float * prev_h;
    float dropout;
    float recurrent_dropout;
    int input_shape[2];
    int output_size;
    bool go_backwards;
    char activation;
    char recurrent_activation;

};

struct GRU buildGRU(const float*, const float *,const float *, int, int , int , char , char, float , float , bool);

float * fwdGRU(struct GRU , float* );

#endif
