

/*************
* maxpooling1d.cpp
*
* Conv1D Layer
* Hardware Plateform: ESP-32
*
* This file defines the functions needed to build a 1D Convolutional layer, and perform a forward pass.
*/

#include "maxpooling1d.h"
#include <math.h>
#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

struct MaxPooling1D buildMaxPooling1D(int pool_size, int strides,
				   int input_sh0, int input_sh1)
{
	Conv1D layer;
	layer.strides = strides;		
    layer.pool_size = pool_size;
    layer.input_shape[0] = input_sh0;
    layer.input_shape[1] = input_sh1;

	layer.output_shape[0] = pool_size;
	layer.output_shape[1] = input_sh0;

	return layer;
}


float * fwdMaxPooling1D(struct MaxPooling1D L, float * input)
{

    // Data array:
     float * h = (float*)malloc((int)L.output_shape[0]*L.output_shape[1] * sizeof(float));

	// Loop through to calculate the output at each point
	for(int i = 0; i < L.output_shape[1]; i++)
	{
		for(int j = 0; j < L.output_shape[0]; j++)
		{
            int idx = i*L.output_shape[1] + j;

            float x1 = input[(2*i)*L.input_shape[1] + j];
            float x2 = input[(2*i+1)*L.input_shape[1] + j];
            h[idx] = max(x1, x2);
			// Now perform the activation function
			// NOTE: NEED TO IMPLEMENT
		}
	}

    free(input);
    return h;
}

