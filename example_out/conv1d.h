
/********************
    conv1d.h

    Code generated using nn4mc.

    This file defines an 1 dimensional convolution layer.

*/

#ifndef __CONV1D_H__
#define __CONV1D_H__

struct Conv1D {
	// Weights and biases defining the layer
	const float* weights;			// Pointer to constant weight array
	const float* biases;				// Pointer to constant bias

	// Kernel information
	int strides;
    int kernel_shape[1];
    int weight_shape[3];
    int filters;

    char activation;

	// Shape of the input and output
	int input_shape[2];		// (INPUT_SIZE x NUM_INPUT_CHANNELS)
	int output_shape[2];	// (OUTPUT_SIZE x NUM_OUTPUT_CHANNELS)
};

struct Conv1D buildConv1D(const float*, const float*, int, int, int, int, int, char);

float * fwdConv1D(struct Conv1D, float*);

#endif
