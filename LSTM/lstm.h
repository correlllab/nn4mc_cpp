
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
    
    int input_shape[2];
    int output_size;
    
    char activation;
    char recurrent_activation;

    float dropout;
    float recurrent_dropout;

    bool go_backwards;

};

struct LSTM buildLSTM(const float*, const float *, const float *, int, int , int , char , char, float , float , bool);

float * fwdLSTM(struct LSTM, float*);

#endif
