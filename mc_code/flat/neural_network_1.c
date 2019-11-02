#include "neural_network.h"
#include "neural_network_params.h"
#include <stdlib.h>
#include <math.h>
#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))
#define TAG "neural network. c: "

struct Conv1D buildConv1D(int input_sh1, int input_sh2, int kernel_size, int filters, int strides, const float * W, const float *b){
    
    struct Conv1D L;
    L.weights = W; // pointer to first element
    L.biases = b;
    L.input_shape[0]= input_sh1;
    L.input_shape[1]= input_sh2;
    L.weight_shape[0] = kernel_size;
    L.weight_shape[1] = input_sh2;
    L.weight_shape[2] = filters;
    L.kernel_size[0] = kernel_size;
    L.filters= filters;
    L.output_shape[0]= (int)(input_sh1-kernel_size+1);
    L.output_shape[1] = filters;

    num_layers++;
    return L;
}

float * fwdConv1D(struct Conv1D  L, float * window){
    
    float * h = (float*)malloc((int)L.output_shape[0]*L.output_shape[1] * sizeof(float));

    for (int i=0; i < L.output_shape[0]; i++){
        for (int j=0; j < L.output_shape[1]; j++){
            int idx = i*L.output_shape[1] + j;
            h[idx]= L.biases[j];
            for (int x=0; x < L.kernel_size[0]; x++){
                for (int y=0; y < L.weight_shape[1]; y++){
                  h[idx] += *(L.weights + x*L.weight_shape[1]*L.weight_shape[2] + y*L.weight_shape[2] + j) *  window[(i+x) * L.input_shape[1] + y];
                }
            }
         }
      }

    free(window);    
    return h;
}

struct MaxPooling1D buildMaxPooling1D(int input_sh1,int input_sh2, int pool_size, int strides){
   // These will emulate the constructors
    struct MaxPooling1D L;
    L.pool_size = pool_size;
    L.strides= strides;
    L.input_shape[0] = input_sh1;
    L.input_shape[1]= input_sh2;
    num_layers++;
    L.output_shape[0]= L.pool_size;
    L.output_shape[1]= input_sh1;
    num_layers++;
    return L;
}

float * fwdMaxPooling1D(struct MaxPooling1D  L, float * window){
    
    float * h = (float*)malloc(L.output_shape[0]*L.output_shape[1] * sizeof(float));

    for (int i=0; i< L.input_shape[0]; i++){
        for (int j=0; j<L.pool_size; j++){
            int idx = i*L.output_shape[1] + j;
            float x1= window[(2*i)*L.input_shape[1]+j];
            float x2= window[(2*i + 1)*L.input_shape[1] + j];
            h[idx] = max(x1, x2);
        }
    }
    
    free(window);
    
    return h;
}

struct Dense buildDense(int input_size, int output_size, char activation, const float * W, const float * b){
   // TESTED
   // These will emulate the constructor
   struct Dense L;
   L.input_shape[0]= input_size;
   L.output_shape[0]= output_size;
   L.weight_shape[0] = input_size;
   L.weight_shape[1]= output_size;
   L.weights = W; // pointer to first element
   L.biases = b;
   L.activation = activation;
   num_layers++;
   return L;
}

float * fwdDense(struct Dense L, float * window){
  //TESTED

    float * h = (float*)malloc(L.output_shape[0] * sizeof(float));

    for (int i=0; i<L.output_shape[0]; i++){
        h[i] = L.biases[i];
        for (int j=0; j< L.input_shape[0]; j++){
           h[i] += *(L.weights + j*L.weight_shape[1] + i)* window[j];
        }

        if (L.activation=='r'){
            h[i]= max(h[i], 0.0);
        }

        if (L.activation== 't'){
            h[i]=tanh(h[i]);
        }
    }

    free(window);
    
    return h;
}

struct Flatten2D1D buildFlatten2D1D(int a, int b){
    //TESTED
    struct Flatten2D1D FLAT;
    FLAT.input_shape[0] = a;
    FLAT.input_shape[1] = b;
    FLAT.output_shape[0]= a*b;
    return FLAT;
}

float * fwdFlatten2D1D(struct Flatten2D1D  FLAT, float * incoming){
  // TESTED

    float * h = malloc(FLAT.output_shape[0]*sizeof(float));

    for (int i=0; i<FLAT.input_shape[0]; i++){
        for (int j=0; j<FLAT.input_shape[1]; j++){
            int idx= FLAT.input_shape[1]*i+j;
            h[idx] = (float) incoming[FLAT.input_shape[1]*i + j] ;
        }
    }

    free(incoming);

    return h; 
}

