
/*************
* lstm.h
*
* LSTM Layer Header
* Code Generated using nn4mc
* Hardware Plateform: ESP-32
*
* This file defines the datastructure needed to create a 1D Convolutional layer.
*/

#ifndef __LSTM_H__
#define __LSTM_H__

struct LSTM {
	// Weights and biases defining the layer
	const float* weights;			// Pointer to constant weight array
	const float* biases;				// Pointer to constant bias

};

struct LSTM buildLSTM();

float * fwdLSTM(struct LSTM , float* );

#endif

