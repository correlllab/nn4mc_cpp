
/*************
* conv1d.cpp
*
* Conv1D Layer
* Hardware Plateform: ESP-32
*
* This file defines the functions needed to build a dense layer, and perform a forward pass.
*/

#include "dense.h"
#include "../include/activation.h"

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))


struct Dense buildDense(const float* W, const float* b, int input_size, int output_size, char activation)
{
	struct Dense layer;

	layer.weights = W;
	layer.biases = b;

	layer.input_shape[0] = input_size;
	layer.output_shape[0] = output_size;
    layer.weight_shape[0] = input_size;
    layer.weight_shape[1] = output_size;
    layer.activation = activation;
    num_layers++;
	return layer;
}


float * fwdDense(struct Dense L, float* input)
{

    float * h = (float*)malloc(L.output_shape[0] * sizeof(float));

	// Loop through to calculate the output at each point
	for(int i = 0; i < L.output_shape[0]; i++)
	{
		// Start with the bias
		h[i] = L.biases[i];

		for(int j = 0; j < L.input_shape[0]; j++)
		{
            h[i] += *(L.weights + j*L.weight_shape[1] + i)*input[j];
		}

		h[i] = activate(h[i],L.activation);

	}

    free(input);
    return h;

}
