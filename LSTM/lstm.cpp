
/********************
    lstm.cpp

    Code generated using nn4mc.

    This file implements a long short term memory layer.

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

