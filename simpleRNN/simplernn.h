
/*************
* simpleRNN.h
*
* SimpleRNN Layer Header
* Code Generated using nn4mc
* Hardware Plateform: ESP-32
*
* This file defines the datastructure needed to create a 1D Convolutional layer.
*/

#ifndef __SIMPLERNN_H__
#define __SIMPLERNN_H__

struct SimpleRNN {

	// Weights and biases defining the layer
	const float* weights;			// Pointer to constant weight array
	const float* biases;				// Pointer to constant bias
    
    int input_shape[2];
    int output_shape[2];
    
    bool go_backwards;

    float * S;

};

struct SimpleRNN buildSimpleRNN();

float * fwdSimpleRNN(struct SimpleRNN , float* );

#endif

