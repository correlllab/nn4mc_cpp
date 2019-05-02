#include "neural_network.h"
#include "neural_network_params.h"
#include <stdlib.h>
#include "esp_log.h"

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))
#define TAG "neural network. c: "

float fast_tanh(float x){
 float x2 = x * x;
 float a = x * (135135.0f + x2 * (17325.0f + x2 * (378.0f + x2)));
 float b = 135135.0f + x2 * (62370.0f + x2 * (3150.0f + x2 * 28.0));
 return a / b;
}

void set_conv1D(struct Conv1D * LL, int input_sh1, int input_sh2, int kernel_size, int filters){
  //TESTED

    struct Conv1D L;
    L= *LL;
    L.input_sh1= input_sh1;
    L.input_sh2= input_sh2;
    L.kernel_size = kernel_size;
    L.filters= filters;
    num_layers++;
    L.h = (float**)malloc((int)(L.input_sh1-L.kernel_size+1) * sizeof(float*));
    for (int i=0; i< (int)(L.input_sh1- L.kernel_size+1); i++){
        L.h[i] = (float*)malloc(L.filters * sizeof(float));
    }

    L.output_shape= (int)(L.input_sh1-L.kernel_size+1);
    *LL = L;
}

 void fwd_conv1D(struct Conv1D * LL, int a, int bb, int c, const float * W, const float * b, float ** window){
  
     // TESTED
    struct Conv1D L;
    L= *LL;
    
    for (int i=0; i<(int)(L.input_sh1-L.kernel_size+1); i++){
        for (int j=0; j<(int)L.filters; j++){
            L.h[i][j]= b[j];
            for (int x=0; x<(int)L.kernel_size; x++){
                for (int y=0; y<bb; y++){
                  L.h[i][j] += *(W + x*bb*c + y*c + j) * window[i+x][y];
                }
            }
         }
      }

   
    for (int i=0; i<L.input_sh1; i++){
        free(window[i]);
    }
    free(window);
    
    *LL = L;
}

void set_maxpool1D(struct MaxPooling1D * LL, int input_sh1,int input_sh2, int pool_size, int strides){
   // TESTED
    struct MaxPooling1D L;
    L= *LL;
    L.pool_size = pool_size;
    L.strides= strides;
    L.input_sh1 = input_sh1;
    L.input_sh2= input_sh2;
    L.output_shape= (int)(L.input_sh1/L.pool_size) ; // casting to int will be floor for >=0 

    num_layers++;
    L.h= (float**)malloc(L.output_shape * sizeof(float*));
    for (int i=0; i<L.output_shape; i++){
        L.h[i]= (float*)malloc((int)L.pool_size * sizeof(float));
    }
    L.input_sh2= L.pool_size;
    num_layers++;
    *LL = L;
}

void fwd_maxpool1D(struct MaxPooling1D * LL, float ** window){
    // TESTED
    struct MaxPooling1D L;
    L= *LL;
    for (int i=0; i< L.output_shape; i++){
        for (int j = 0; j < L.pool_size; j++){
            L.h[i][j] = max(window[2*i][j], window[2*i+1][j]);
        }
    }

    for (int i=0; i< L.input_sh1 ; i++){
        free(window[i]); 
    }
    free(window);
    *LL = L;
}

void set_dense(struct Dense * LL, int input_size, int output_size, char activation){
  // TESTED
   // These will emulate the constructor
   struct Dense L;
   L= *LL;
   L.input_size= input_size;
   L.output_size= output_size;
   L.activation = activation;
   num_layers++;
   L.h= (float*)malloc(L.output_size * sizeof (float));
   *LL = L;
}

void fwd_dense(struct Dense * LL, int a, int bb, const float * W, const float * b, float * window){
  //TESTED
    struct Dense L;
    L= *LL;

    for (int i=0; i<L.output_size; i++){
        L.h[i] = b[i];
        for (int j=0; j<L.input_size; j++){
           L.h[i] += *(W + j*bb + i)*window[j];
        }

        if (L.activation=='r'){
            L.h[i]= max(L.h[i], 0.0);
        }

        if (L.activation== 't'){
            L.h[i]=fast_tanh(L.h[i]);
        }
    }

    free(window);
    *LL = L;
}

void setflatten2D1D(struct Flatten2D1D * FLATFLAT, int a, int b){
  //TESTED
    struct Flatten2D1D FLAT;
    FLAT = *FLATFLAT;
    FLAT.h= (float *)malloc(a*b*sizeof(float));
    FLAT.in_shape_0 = a;
    FLAT.in_shape_1 = b;
    FLAT.output_size= a*b;
    *FLATFLAT= FLAT;
}

void flatten2D1D(struct Flatten2D1D * FLATFLAT, float ** incoming){
  // TESTED
    struct Flatten2D1D FLAT;
    FLAT= *FLATFLAT;

    for (int i=0; i<FLAT.in_shape_0; i++){
        for (int j=0; j<FLAT.in_shape_1; j++){
            int idx= FLAT.in_shape_1*i+j;
            FLAT.h[idx] = (float)incoming[i][j];
        }
    }
   

    for (int i=0; i < FLAT.in_shape_0; i++){
        free(incoming[i]); 
    }
    free(incoming);
    
    *FLATFLAT= FLAT;
}

