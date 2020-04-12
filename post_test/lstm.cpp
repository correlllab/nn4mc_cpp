
/********************
    lstm.cpp

    Code generated using nn4mc.

    This file implements a long short term memory layer.

*/

#include "lstm.h"
#include "activations.h"
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
    layer.recurrent_dropout = recurrent_dropout;

    layer.go_backwards = go_backwards;

    layer.prev_h = (float*)malloc(layer.output_size*sizeof(float));  
    layer.prev_c = (float*)malloc(layer.output_size*sizeof(float));  

    for (int i=0; i< layer.output_size; i++){
        layer.prev_h[i] = 0.0;
        layer.prev_c[i] = 0.0;
    }

    // TODO: Need to assign the above to 0''s
	return layer;
}

void reverseInput(float * x, int start, int end){
    while(start < end){
        float temp = x[start];
        x[start] = x[end];
        x[end] = temp;
        start++;
        end--;
    }
}

float * fwdLSTM(struct LSTM L, float* x)
{
    if (L.go_backwards == 1){
        reverseInput(x, 0, L.input_shape[0]*L.input_shape[1] - 1);           
    }

    float * h = (float*)malloc(L.output_size*sizeof(float));

    float * f = (float*)malloc(L.output_size*sizeof(float));
    float * ig = (float*)malloc(L.output_size*sizeof(float));
    float * c = (float*)malloc(L.output_size*sizeof(float));
    float * og = (float*)malloc(L.output_size*sizeof(float));

   for (int i = 0; i < L.output_size; i++){
        
        int ind_i = i;
        int ind_f = i + L.output_size;
        int ind_o = i + 3*L.output_size;
        int ind_c = i + 2*L.output_size;
        
        f[i]  = L.biases[ind_f];
        ig[i] = L.biases[ind_i];
        c[i]  = L.biases[ind_c];
        og[i] = L.biases[ind_o];
       
      for (int j = 0; j < L.input_shape[0]*L.input_shape[1]; j++){
       
           f[i] += *(L.weights + ind_f*L.output_size + j)*x[j];  
           ig[i]+= *(L.weights + ind_i*L.output_size + j)*x[j];
           c[i] += *(L.weights + ind_c*L.output_size + j)*x[j]; 
           og[i]+= *(L.weights + ind_o*L.output_size + j)*x[j];
       }

      for (int j = 0; j < L.output_size; j++){
            f[i]+= *(L.wrec + ind_f*L.output_size + j)*L.prev_h[j];
            ig[i]+= *(L.wrec + ind_i*L.output_size+j)*L.prev_h[j];
            c[i] += *(L.wrec + ind_c*L.output_size+j)*L.prev_h[j];
            og[i]+= *(L.wrec + ind_o*L.output_size+j)*L.prev_h[j];
       }
     }
      
      for (int j = 0; j < L.output_size; j++){
            f[j] = activate(f[j], L.output_size, L.recurrent_activation);
            ig[j]= activate(ig[j], L.output_size, L.recurrent_activation);
            c[j] = activate(c[j], L.output_size, L.activation);
            og[j]= activate(c[j], L.output_size, L.recurrent_activation);
       }

      for (int j = 0; j < L.output_size; j++){
            h[j] = og[j] * activate(f[j]*L.prev_c[j] + ig[j]*c[j], L.output_size, L.activation);
       } 

    free(f);
    free(ig);
    free(c);
    free(og);
    free(x);
    
    return h;
}

