
/*************
* conv1d.h
*
* Conv1D Layer Header
* Code Generated using nn4mc
* Hardware Plateform: ESP-32
*
* This file defines the datastructure needed to create a 1D Convolutional layer.
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

struct Conv1D buildConv1D(const float* , const float* , int , int , int , int , int , char);

float * fwdConv1D(struct Conv1D , float* );

#endif

