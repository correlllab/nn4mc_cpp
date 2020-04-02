
/********************
    lstm.cpp

    Code generated using nn4mc.

    This file implements a long short term memory layer.

*/

#include "lstm.h"
#include "activation_func.h"
#include <math.h>
#include <stdlib.h>

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

struct LSTM buildLSTM(const float * W, const float * Wrec, const float * b, int input_sh0, int input_sh1, int output_sh, char activation, char recurrent_activation, float dropout, float recurrent_dropout, bool go_backwards)
{
	struct LSTM layer;

	layer.weights = W;
	layer.biases = b;
    layer.wrec = Wrec;

    layer.input_shape[0] = input_sh0;
    layer.input_shape[1] = input_sh1;

    layer.activation = activation;
    layer.recurrent_activation = recurrent_activation;

    layer.output_size = output_sh; 

    layer.dropout = dropout;
    layer.recurrent_dropout;

    layer.go_backwards = go_backwards;

    layer.prev_h = (float*)malloc(layer_output_size*sizeof(float));  
    layer.prev_c = (float*)malloc(layer_output_size*sizeof(float));  
    // TODO: Need to assign the above to 0''s
	return layer;
}

float * fwdLSTM(struct LSTM L, float* x)
{

    float * h = (float*)malloc(layer.output_size*layer.output_size*sizeof(float));

    float * forget_gate = (float*)malloc(layer.output_size*sizeof(float));
    float * input_gate = (float*)malloc(layer.output_size*sizeof(float));
    float * cell_state = (float*)malloc(layer.output_size*sizeof(float));
   float * output_gate = (float*)malloc(layer.output_size*sizeof(float));

   for (int i = 0; i < L.output_size; i++){
        int ind_f = i + L.output_size;
        int ind_i = i;
        int ind_o = 3*L.output_size + i;
        int ind_c = 2*L.output_size + i;
        forget_gate[i] = L.b[ind_f];
        input_gate[i] = L.b[ind_i];
        cell_state[i] = L.b[ind_c];
        output_gate[i] = L.b[ind_o];
       for (int j = 0; j < L.input_shape[0]*L.input_shape[1]; j++){
            forget_gate[i] += *(L.weights + (i+L.output_size)*(4*L.output_size) + j)*x[j] + *(L.wrec + (j+L.output_size)*(4*L.output_size))*L.prev_h[j]; 
            input_gate[i] += *(L.weights + i*(4*L.output_size) + j)*x[j] + *(L.wrec + i*(4*L.output_size))*L.prev_h[i];
            cell_state[i] += *(L.weights + (i+2*L.output_size)*(4*L.output_size + j))* x[j] + *(L.wrec + ()*4*L.output_size)*L.prev[j];
            output_state[i] += *(L.weights + (i*3*L.output_size)*(4*L.output_size + j))* x[j] + *(L.wrec + ()*4*L.output_size)*L.prev[j];
       }

    forget_gate[i] = activate(forget_gate[i], L.output_size, L.recurrent_activation);
    output_gate[i] = activate(output_gate[i], L.output_size, L.recurrent_activation);
    input_gate[i] = activate(input_gate[i], L.output_size, L.recurrent_activation);
    cell_state[i] = activate(cell_state[i], L.output_size, L.activation);

     h[i] = output_gate[i] * activate(forget_gate[i]*prev_c[i] + input_gate[i] * cell_state[i], L.output_size, L.activation ) ;
    
    L.prev_c[i] = forget_gate[i]*prev_c[i] + input_gate[i] * cell_state[i];
    L.prev_h[i] = h[i];
   }  
    
    free(forget_gate);
    free(input_gate);
    free(cell_state);
    free(output_gate);
    free(x);
    
    return h;
}

