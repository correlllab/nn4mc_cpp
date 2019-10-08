
/*************
* maxpool1d.h
*
* MaxPool1D Layer Header
* Hardware Plateform: ESP-32
*
* This file defines the datastructure needed to create a 1D MaxPooling layer.
*/

#ifndef __MAXPOOL1D_H__
#define __MAXPOOL1D_H__

struct MaxPooling2D {
	// Kernel size
	int pool_size[2];	// How many entries to consider
	int strides[2];			// How many to skip	

	// Shape of the input and output
	int input_shape[3];		// (INPUT_SIZE x NUM_INPUT_CHANNELS)
	int output_shape[3];	// (OUTPUT_SIZE x NUM_OUTPUT_CHANNELS)
};
struct MaxPooling2D buildMaxPooling2D(int, int , int, int , int, int, int);

float * fwdMaxPooling2D(struct MaxPooling2D , float *);
#endif

