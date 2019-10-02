

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
	Conv1D layer;

	layer.weights = W;
	layer.biases = b;

	layer.weight_shape[0] = kernel_size;
	layer.weight_shape[1] = input_sh0;
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
            h[i] = exp(h[i])/(exp(h[i]) + 1);
        }

        if (L.activation==0x04){ //softplus
            h[i] = log(exp(h[i]) + 1);
        }

        if (L.activation==0x05){ //softsign
            h[i] = h[i] / (abs(h[i]) + 1);
        }

        if (L.activation==0x09){ //hard_sigmoid
            if (h[i] < -2.5){
                h[i] = 0.0;
            } else if (h[i] > 2.5){
                h[i] = 1.0;
            } else{
                h[i] = 0.2*h[i] + 0.5;
            }
        }

        if (L.activation==0xA){ //exponential
            h[i] = (float)expf((float)h[i]);
        }
        
         if (L.activation==0x06){ //relu
             h[i]= max(h[i], 0.0);
         }

         if (L.activation== 0x07){ //tanh
             h[i]=tanh(h[i]);
         }
         if (L.activation==0x00){ //softmax
             float sum_exp = 0.0;
             for (int i=0; i<L.output_shape[0]; i++){
                 sum_exp+= expf(h[i]);
             }
             for (int i=0; i<L.output_shape[0];i++){
                 float calc = expf(h[i]) / sum_exp;
                 if (isnan(calc)){
                     h[i] = 1.0;
                 } else h[i] = (float)(expf(h[i]) / sum_exp);
             }
         }

		}
	}

    free(input); 
    return h;
}

