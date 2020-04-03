
/********************
    gru.cpp

    Code generated using nn4mc.

    This file implements a gated recurrent unit layer.

*/

#include "gru.h"
#include "activation_func.h"
#include <math.h>
#include <stdlib.h>

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

struct GRU buildGRU()
{
	struct GRU layer;

	layer.weights = W;
	layer.biases = b;

	return layer;
}


float * fwdGRU(struct GRU L, float* input)
{

    free(input);
    return h;
}

