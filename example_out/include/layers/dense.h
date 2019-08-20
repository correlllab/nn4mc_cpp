
/*************
* dense.h
*
* Dense Layer Header
* Hardware Plateform: ESP-32
*
* This file defines the datastructure needed to create a Dense (Fully Connected) layer.
*/

#ifndef __DENSE_H__
#define __DENSE_H__

#ifdef __cpluscplus
extern "C" {
#endif

struct DENSE {
	// Weights and biases defining the layer
	const float* weights;			// Pointer to constant weight array
	const float* bias;				// Pointer to constant bias

	// Shape of the input and output
	int input_size;
	int output_size;
};


#ifdef __cplusplus
}

#endif
#endif

