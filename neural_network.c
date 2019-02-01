#include "neural_network.h"
#include "neural_network_params.h"
#include <stdlib.h>

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

#define COLS(arr) (int)sizeof((arr)[0])
#define ROWS(arr) (int)(sizeof(arr)/sizeof(arr[0])) 

void set_conv1D(struct Conv1D * LL, int input_sh1, int input_sh2, int kernel_size, int filters){
    // These will emulate the constructors
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

void fwd_conv1D(struct Conv1D * LL, int a, int bb, int c, const float W[a][bb][c], const float * b, float ** window){
    struct Conv1D L;
    L= *LL;

     for (int i=0; i<(int)(L.input_sh1-L.kernel_size+1); i++){
        for (int j=0; j<(int)L.filters; j++){
            L.h[i][j]= b[j];
            for (int x=0; x<(int)L.kernel_size; x++){
                for (int y=0; y<bb; y++){
                    L.h[i][j] += W[x][y][j] * window[i+x][y];
                }
            }
         }
      }

    *LL = L;
}

void set_maxpool1D(struct MaxPooling1D * LL, int input_sh1,int input_sh2, int pool_size, int strides){
   // These will emulate the constructors
    
    struct MaxPooling1D L;
    L= *LL;
    L.pool_size = pool_size;
    L.strides= strides;
    L.input_sh1 = input_sh1;
    L.input_sh2= input_sh2;
    num_layers++;
    L.h= malloc((int)L.input_sh1 * sizeof(float*));
    for (int i=0; i<(int)L.input_sh1; i++){
        L.h[i]= malloc((int)L.pool_size * sizeof(float));
    }
    L.output_shape= L.pool_size;
    L.input_sh1= L.input_sh1;
    L.input_sh2= L.pool_size;
    num_layers++;
    *LL = L;
}

void fwd_maxpool1D(struct MaxPooling1D * LL, int a, int bb, int c, const float W[a][bb][c], const float *b, float ** window){
    struct MaxPooling1D L;
    L= *LL;
    for (int i=0; i< L.input_sh1; i++){
        for (int j=0; j<L.pool_size; j++){
            L.h[i][j] = max(window[2*i][j], window[2*i+1][j]);
        }
    }
    *LL = L;
}

void set_dense(struct Dense * LL, int input_size, int output_size, char activation){
   // These will emulate the constructor
   
   struct Dense L;
   L= *LL;
   L.input_size= input_size;
   L.output_size= output_size;
   L.activation = activation;
   num_layers++;
   L.h= malloc((int)L.output_size * sizeof (float));
   *LL = L;
}

void fwd_dense(struct Dense * LL, int a, int bb, const float W[a][bb], const float * b, float window[a]){
    struct Dense L;
    L= *LL;

    for (int i=0; i<L.output_size; i++){
        L.h[i] = b[i];
        for (int j=0; j<L.input_size; j++){
            L.h[i]+= W[j][i] * window[j]; 
        }
        if (L.activation=='r'){
            L.h[i]= max(L.h[i], 0.0);
        } 
    }
    *LL = L;
}

void flatten2D1D(struct Flatten2D1D * FLATFLAT, int a, int b,float ** window){
    struct Flatten2D1D FLAT;
    FLAT= *FLATFLAT;
    FLAT.in_shape_0 = a; 
    FLAT.in_shape_1 = b;
    FLAT.h= malloc((int)(FLAT.in_shape_0*FLAT.in_shape_1) * sizeof(float));
    num_layers++; //does the flatten count?
    for (int i=0; i<FLAT.in_shape_0; i++){
        for (int j=0; j<FLAT.in_shape_1; j++){
            int idx= FLAT.in_shape_1*i+j;
            FLAT.h[idx] = window[i][j];
        }
    }
    FLAT.output_size= FLAT.in_shape_0*FLAT.in_shape_1;
    *FLATFLAT= FLAT;
}


