
/********************
    lstm.h

    Code generated using nn4mc.

    This file defines a long short term memory layer.

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
