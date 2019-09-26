

/*************
* conv2d.cpp
*
* Conv2D Layer
* Hardware Plateform: ESP-32
*
* This file defines the functions needed to build a 2D Convolutional layer, and perform a forward pass.
* TODO: This template.
*/

#include "conv2d.h"


Conv2D buildConv2D(const float* W, const float* b,
				   int* kernel_shape, int* stride,
				   int input_channels, int output_channels,
				   int* input_shape)
{
	Conv2D layer;

	layer.weights = W;
	layer.bias = b;

	layer.kernel_shape[0] = kernel_size[0];
	layer.kernel_shape[1] = kernel_size[1];
	layer.kernel_shape[2] = input_channels;
	layer.kernel_shape[3] = output_channels;

	layer.stride[0] = stride[0];				// NOTE: NOT YET IMPLEMENTED
	layer.stride[1] = stride[1];

	layer.input_shape[0] = input_shape[0];
	layer.input_shape[1] = input_shape[1];
	layer.input_shape[2] = input_channels;

	layer.output_shape[0] = layer.input_shape[0] - layer.kernel_shape[0] + 1;
	layer.output_shape[1] = layer.input_shape[1] - layer.kernel_shape[1] + 1;
	layer.output_shape[2] = layer.kernel_shape[3];

	return layer;
}


void fwdConv2D(Conv2D* layer, float* input, float* output)
{
	// Dereference the provided layer to simplify the code
	Conv2D L = (*layer);

	// Loop through to calculate the output at each point
	for(int output_position_x = 0; output_position_x < L.output_shape[0]; output_position_x++)
	{
		for(int output_position_y = 0; output_position_y < L.output_shape[1]; output_position_y++)
		{
			for(int output_channel = 0; output_channel < L.output_shape[2]; output_channel++)
			{
				// Convert the 2D output index (i,j) to the 1D index in the provided array
				output_idx = output_position_x * L.output_shape[1] * L.output_shape[2] + output_position_y * L.output_shape[2] + output_channel;

				// Start with the bias
				output[output_idx] = L.bias[output_channel];

				// Now multiply the input by the weight matrix
				int input_position_x = output_position_x * L.stride[0];
				int input_position_y = output_position_y * L.stride[1];

				for(int kernel_position_x = 0; kernel_position_x < L.kernel_shape[0]; kernel_position_x++)
				{
					for(int kernel_position_y = 0; kernel_position_y < L.kernel_shape[1]; kernel_position_y++)
					{				
						for(int input_channel = 0; input_channel < L.kernek_shape[2]; kernel_shape++)
						{
							// What are the flattened indices of the weight matrix and input
							// TODO:  NEED TO FIGURE OUT HOW TO DO THIS MULTIPLICATION...
						}
					}
				}

				// Now perform the activation function
				// NOTE: NEED TO IMPLEMENT

			}
		}
	}
}

