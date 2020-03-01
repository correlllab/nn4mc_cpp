
/********************
    maxpool2d.cpp

    Code generated using nn4mc.

    This file implements a 1 dimensional maximum pooling layer.

*/

#include "maxpool2d.h"
#include "activations.h"
#include <math.h>
#include <stdlib.h>
#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

struct MaxPooling2D buildMaxPooling2D(int pool_size_0, int pool_size_1, int strides_0, int strides_1, int input_shape_0, int input_shape_1, int input_shape_2)
{
	MaxPooling2D layer;

	layer.strides[0] = strides_0;
    layer.strides[1] = strides_1;

    layer.pool_size[0] = pool_size_0;
    layer.pool_size[1] = pool_size_1;
    layer.input_shape[0] = input_shape_0;
    layer.input_shape[1] = input_shape_1;
    layer.input_shape[2] = input_shape_2;

	layer.output_shape[0] = pool_size_0;
	layer.output_shape[1] = pool_size_1;
    layer.output_shape[2] = input_shape_2;

	return layer;
}


float * fwdMaxPooling2D(struct MaxPooling2D L, float * input)
{

    // Data array:
     float * h = (float*)malloc((int)L.output_shape[0]*L.output_shape[1]*L.output_shape[2] * sizeof(float));

	// Loop through to calculate the output at each point
	for(int i = 0; i < L.output_shape[0]; i++)
	{
		for(int j = 0; j < L.output_shape[1]; j++)
		{
            for (int k = 0; k< L.output_shape[2]; j++)
            {
                int idx = i*L.output_shape[1]*L.output_shape[2] + L.output_shape[1]*j + k;
                float x1 = input[(2*i)*L.input_shape[2]*L.input_shape[1] + j*L.input_shape[1] + k];
                float x2 = input[(2*i+1)*L.input_shape[2]*L.input_shape[1] + j*L.input_shape[1]+k];
                h[idx] = max(x1, x2);
                // Now perform the activation function
								if(L.activation != 0xB)
									h[i] = activate(h[i],L.output_shape[0],L.activation);
            }
        }
    }
    free(input);
    return h;
}

