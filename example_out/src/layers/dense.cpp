
/*************
* conv1d.cpp
*
* Conv1D Layer
* Hardware Plateform: ESP-32
*
* This file defines the functions needed to build a dense layer, and perform a forward pass.
*/

#include "dense.h"
#include <math.h> 
#include <stdlib.h>

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
             for (int ii=0; ii<L.output_shape[0]; ii++){
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

    free(input);
    return h;

}
