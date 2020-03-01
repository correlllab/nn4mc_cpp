
/********************
    Dense.h

    Code generated using nn4mc.

    This file defines a densely connected layer.

*/

#ifndef __DENSE_H__
#define __DENSE_H__


struct Dense {
	// Weights and biases defining the layer
	const float* weights;			// Pointer to first element of weights array (should be 'const float' in weight.best.hdf5)
	const float* biases;				// Pointer to constant bias

    char activation;  // in our case this delimiter is a char that indicates which activation function to call

    int weight_shape[2];

	// Shape of the input and output
	int input_shape[1];
	int output_shape[1];
};

struct Dense buildDense(const float*, const float*, int, int, char);

float * fwdDense(struct Dense, float* );

#endif
