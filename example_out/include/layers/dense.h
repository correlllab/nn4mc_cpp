
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
	const float* weights;			// Pointer to first element of weights array (should be 'const float' in weight.best.hdf5)
	const float* biases;				// Pointer to constant bias

    char activation;  // in our case this delimiter is a char that indicates which activation function to call

    int weight_shape[2];

	// Shape of the input and output
	int input_shape[1];
	int output_shape[1];
};


#ifdef __cplusplus
}

#endif
#endif

