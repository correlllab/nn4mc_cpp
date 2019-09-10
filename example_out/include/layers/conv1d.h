
/*************
* conv1d.h
*
* Conv1D Layer Header
* Hardware Plateform: ESP-32
*
* This file defines the datastructure needed to create a 1D Convolutional layer.
*/

#ifndef __CONV1D_H__
#define __CONV1D_H__

#ifdef __cpluscplus
extern "C" {
#endif

struct Conv1D {
	// Weights and biases defining the layer
	const float* weights;			// Pointer to constant weight array
	const float* biases;				// Pointer to constant bias

	// Kernel information
	int strides;				
    int kernel_shape[1];
    int weight_shape[3];

	// Shape of the input and output
	int input_shape[2];		// (INPUT_SIZE x NUM_INPUT_CHANNELS)
	int output_shape[2];	// (OUTPUT_SIZE x NUM_OUTPUT_CHANNELS)
};


#ifdef __cplusplus
}

#endif
#endif

