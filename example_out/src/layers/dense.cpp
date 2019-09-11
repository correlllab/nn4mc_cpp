
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


        // TODO: Actual lookup table

        if (L.activation==0x08){ //sigmoid
            h[i] = exp(h[i])/(exp(h[i]) + 1);
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
                 if isnan(calc){
                     h[i] = 1.0;
                 } else h[i] = (float)(expf(h[i]) / sum_exp);
             }
         }



	}

    free(input);
    return h;

}
