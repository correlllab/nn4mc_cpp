
/***************************
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
    const float* wrec;

    float * prev_h;
    float * prev_c;

    int input_shape[2];
    int output_size;
    
    char activation;
    char recurrent_activation;

    float dropout;
    float recurrent_dropout;

    int go_backwards;
};

struct LSTM buildLSTM(const float*, const float *, const float *, int, int , int , char , char, float , float , int);

float * fwdLSTM(struct LSTM, float*);

#endif
