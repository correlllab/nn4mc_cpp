

/*************
* conv1d.cpp
*
* Conv1D Layer
* Hardware Plateform: ESP-32
*
* This file defines the functions needed to build a 1D Convolutional layer, and perform a forward pass.
*/

#include "conv1d.h"


Conv1D buildConv1D(const float* W, const float* b,
				   int kernel_size, int stride,
				   int input_channels, int output_channels,
				   int input_size)
{
	Conv1D layer;

	layer.weights = W;
	layer.bias = b;

	layer.kernel_shape[0] = kernel_size;
	layer.kernel_shape[1] = input_channels;
	layer.kernel_shape[2] = output_channels;

	layer.stride = 1;				// NOTE: NOT YET IMPLEMENTED

	layer.input_shape[0] = input_size;
	layer.input_shape[1] = input_channels;

	layer.output_shape[0] = layer.input_shape[0] - layer.kernel_shape[1] + 1;
	layer.output_shape[1] = layer.kernel_shape[2];

	return layer;
}


void fwdConv1D(Conv1D* layer, float* input, float* output)
{
	// Dereference the provided layer to simplify the code
	Conv1D L = (*layer);

	// Loop through to calculate the output at each point
	for(int output_position = 0; output_position < L.output_shape[0]; output_position++)
	{
		for(int output_channel = 0; output_channel < L.output_shape[1]; output_channel++)
		{
			// Convert the 2D output index (i,j) to the 1D index in the provided array
			output_idx = output_position*L.kernel_shape[2] + output_channel;

			// Start with the bias
			output[output_idx] = L.bias[output_channel];

			// Now multiply the input by the weight matrix
			int input_position = output_position * L.stride;
			for(int kernel_position = 0; kernel_position < L.kernel_shape[0]; kernel_position++)
			{
				for(int input_channel = 0; input_channel < L.kernel_shape[1]; kernel_shape++)
				{
					// What are the flattened indices of the weight matrix and input
					weight_idx = L.kernel_shape[1] * L.kernel_shape[2] * kernel_position +
					             L.kernel_shape[2] * input_channel + output_channel;
					input_idx = (input_position + kernel_position) * L.kernel_shape[1] + input_channel;

					output[output_idx] += L.weights[weight_idx] * input[input_idx];
				}
			}

			// Now perform the activation function
			// NOTE: NEED TO IMPLEMENT
		}
	}
}

