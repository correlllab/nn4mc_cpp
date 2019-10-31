

/*************
* conv1d.cpp
*
* Conv1D Layer
* Hardware Plateform: ESP-32
*
* This file defines the functions needed to build a 1D Convolutional layer, and perform a forward pass.
*/

#include "conv1d.h"
#include <math.h>
#include <stdlib.h>

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

struct Conv1D buildConv1D(const float* W, const float* b, int kernel_size, int strides, int input_sh0, int input_sh1, int filters, char activation)
{
	struct Conv1D layer;

	layer.weights = W;
	layer.biases = b;

	layer.weight_shape[0] = kernel_size;
	layer.weight_shape[1] = input_sh1;
	layer.weight_shape[2] = filters;

	layer.strides = strides;		
    layer.kernel_shape[0] = kernel_size;
	layer.input_shape[0] = input_sh0;
	layer.input_shape[1] = input_sh1;
    layer.activation = activation;  
    layer.filters= filters;

	layer.output_shape[0] = (int)(layer.input_shape[0] - layer.kernel_shape[0] + 1);
	layer.output_shape[1] = layer.filters;

	return layer;
}


float * fwdConv1D(struct Conv1D L, float* input)
{

     float * h = (float*)malloc(L.output_shape[0]*L.output_shape[1] * sizeof(float));

	// Loop through to calculate the output at each point
	for(int i = 0; i < L.output_shape[0]; i++)
	{
		for(int j = 0; j < L.output_shape[1]; j++)
		{
            int idx = i*L.output_shape[1] + j;

			h[idx] = L.biases[j];

			for(int x = 0; x < L.kernel_shape[0]; x++)
			{
				for(int y = 0; y < L.weight_shape[1]; y++)
				{
                    h[idx] += *(L.weights + x*L.weight_shape[1]*L.weight_shape[2] + y*L.weight_shape[2] +  j) * input[(i+x)*L.input_shape[1] +  y]; 
				}
			}

			// Now perform the activation function
			// NOTE: NEED TO IMPLEMENT
        // TODO: Make more elegant:
        // linear not here cause no action

        if (L.activation==0x08){ //sigmoid
            h[idx] = exp(h[idx])/(exp(h[idx]) + 1);
        }

        if (L.activation==0x04){ //softplus
            h[idx] = log(exp(h[idx]) + 1);
        }

        if (L.activation==0x05){ //softsign
            h[idx] = h[idx] / (abs(h[idx]) + 1);
        }

        if (L.activation==0x09){ //hard_sigmoid
            if (h[idx] < -2.5){
                h[idx] = 0.0;
            } else if (h[idx] > 2.5){
                h[idx] = 1.0;
            } else{
                h[idx] = 0.2*h[idx] + 0.5;
            }
        }

        if (L.activation==0xA){ //exponential
            h[idx] = (float)expf((float)h[idx]);
        }
        
         if (L.activation==0x06){ //relu
             h[idx]= max(h[idx], 0.0);
         }

         if (L.activation== 0x07){ //tanh
             h[idx]=tanh(h[idx]);
         }
         if (L.activation==0x00){ //softmax
             float sum_exp = 0.0;
             for (int ii=0; ii<L.output_shape[0]*L.output_shape[1]; ii++){
                 sum_exp+= expf(h[ii]);
             }
             for (int ii=0; ii<L.output_shape[0];ii++){
                 float calc = expf(h[ii]) / sum_exp;
                 if (isnan(calc)){
                     h[ii] = 1.0;
                 } else h[ii] = (float)(expf(h[ii]) / sum_exp);
             }
         }

		}
	}

    free(input); 
    return h;
}

