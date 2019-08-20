
/*************
* conv1d.cpp
*
* Conv1D Layer
* Hardware Plateform: ESP-32
*
* This file defines the functions needed to build a dense layer, and perform a forward pass.
*/

#include "dense.h"


Dense buildDense(const float* W, const float* b,
				 int input_size, int output_size)
{
	Dense layer;

	layer.weights = W;
	layer.bias = b;

	layer.input_size = input_size;
	layer.output_size = output_size;

	return layer;
}


void fwdDense(Dense* layer, float* input, float* output)
{
	// Dereference the provided layer to simplify the code
	Dense L = (*layer);

	// Loop through to calculate the output at each point
	for(int output_idx = 0; output_idx < L.output_size; output_idx++)
	{
		// Start with the bias
		output[output_idx] = L.bias[output_idx];

		for(int input_idx = 0; input_idx < L.input_size; input_idx++)
		{
			int weight_idx = input_idx * L.output_size + output_idx;

			output[output_idx] += L.weights[weight_idx] * input[input_idx];
		}

		// Now perform the activation function
		// NOTE: NEED TO IMPLEMENT
	}
}
