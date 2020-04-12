
/********************
    gru.cpp

    Code generated using nn4mc.

    This file implements a gated recurrent unit layer.

*/

#include "gru.h"
#include "activations.h"
#include <math.h>
#include <stdlib.h>

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

struct GRU buildGRU(const float * W, const float * Wrec, const float * b, int input_sh0, int input_sh1, int output_sh, char activation, char recurrent_activation, float dropout,   float
recurrent_dropout, bool go_backwards)
{
	struct GRU layer;

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

    layer.prev_h = (float*)malloc(layer.output_size *sizeof(float));
    for (int i = 0; i< layer.output_size; i++) layer.prev_h[i] = 0.0;

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

float * fwdGRU(struct GRU L, float* input)
{

    if (L.go_backwards){
        reverseInput(input, 0, L.input_shape[0]*L.input_shape[1] - 1);
    }

    float * h = (float*)malloc(L.output_size*sizeof(float));

     float * z = (float*)malloc(L.output_size * sizeof(float));
     float * r = (float*)malloc(L.output_size * sizeof(float));
     float * hh = (float*)malloc(L.output_size * sizeof(float));

    for (int i=0; i< L.output_size; i++){
        int ind_z = i;
        int ind_r = 1*L.output_size + i;
        int ind_h = 2*L.output_size + i;

        z[i] = L.biases[ind_z];
        r[i] = L.biases[ind_r];
        hh[i] = L.biases[ind_h];

       for (int j=0; j< L.input_shape[0]*L.input_shape[1]; j++){
            z[i]+= *(L.weights + ind_z*L.output_size + j)*input[j];
            r[i]+= *(L.weights + ind_r*L.output_size + j)*input[j];
            hh[i]+= *(L.weights + ind_h*L.output_size + j)*input[j];
       }

       for (int j=0; j<L.output_size; j++){
            z[i]+= *(L.wrec + ind_z*L.output_size + j) * L.prev_h[j];
            r[i]+= *(L.wrec + ind_r*L.output_size + j) * L.prev_h[j];
       }

       for (int j=0;j<L.output_size;j++){
            z[i] = activate(z[i], L.output_size, L.recurrent_activation);
            r[i] = activate(r[i], L.output_size, L.recurrent_activation);
       }

       for (int j=0; j<L.output_size; j++){
            hh[i]+= *(L.wrec + ind_h*L.output_size + j) *(r[j]*L.prev_h[j]);
       }

      for (int j=0; j<L.output_size; j++){
            hh[i]= activate(hh[i], L.output_size, L.activation);
            h[i] = z[i]*L.prev_h[i] + (1 - z[i]) * hh[i];
            L.prev_h[i] = h[i];
       }        
      
    } 

    free(z);
    free(input);
    free(r);
    free(hh);
    
    return h;
}

