
/********************
    conv2d.h

    Code generated using nn4mc.

    This file defines an 2 dimensional convolution layer.

*/

#ifndef __CONV2D_H__
#define __CONV2D_H__

struct Conv2D {
	// Weights and biases defining the layer
	const float* weights;			// Pointer to constant weight array
	const float* bias;				// Pointer to constant bias

	// Kernel information
	int weight_shape[4];	// (NUM_INPUT_CHANNELS x KERNEL_WIDTH x KERNEL_HEIGHT x NUM_OUTPUT_CHANNELS)

    int strides[2];			// (STRIDE_WIDTH x STRIDE_HEIGHT)

    int filters;

    char activation;

    int kernel_shape[2];

	// Shape of the input and output
	int input_shape[3];		// (INPUT_WIDTH x INPUT_HEIGHT x NUM_INPUT_CHANNELS)
	int output_shape[3];	// (OUTPUT_WIDTH x OUTPUT_HEIGHT x NUM_OUTPUT_CHANNELS)
};

struct Conv2D buildConv2D(const float*, const float*, int, int, int, int, int, int, int, int, char);

float* fwdConv2D(struct Conv2D, float*);

#endif
