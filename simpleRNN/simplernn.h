
/********************
    simplernn.h

    Code generated using nn4mc.

    This file defines a simple recurrent layer.

*/

#ifndef __SIMPLERNN_H__
#define __SIMPLERNN_H__

struct SimpleRNN {

	// Weights and biases defining the layer
	const float* weights;			// Pointer to constant weight array
	const float* biases;			// Pointer to constant bias

    int input_shape[2];
    int output_shape[2];

    bool go_backwards;

    float * S;
};

struct SimpleRNN buildSimpleRNN(const float*, const float*, int, int, int, char);

float * fwdSimpleRNN(struct SimpleRNN, float* );

#endif
