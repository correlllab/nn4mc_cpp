

/*************
* lstm.cpp
*
* LSTM Layer
* Hardware Plateform: ESP-32
*
* This file defines the functions needed to build a Simple RNN layer, and perform a forward pass.
*/

#include "lstm.h"
#include "activation_func.h"
#include <math.h>
#include <stdlib.h>

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

struct LSTM buildLSTM()
{
	struct LSTM layer;

	layer.weights = W;
	layer.biases = b;

	return layer;
}


float * fwdLSTM(struct LSTM L, float* input)
{

    free(input);
    return h;
}

