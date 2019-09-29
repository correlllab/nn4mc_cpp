
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
	int pool_size;	// How many entries to consider
	int strides;			// How many to skip	

	// Shape of the input and output
	int input_shape[2];		// (INPUT_SIZE x NUM_INPUT_CHANNELS)
	int output_shape[2];	// (OUTPUT_SIZE x NUM_OUTPUT_CHANNELS)
};


#endif

