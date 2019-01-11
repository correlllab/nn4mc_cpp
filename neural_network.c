#include "neural_network.h"
//#include "adc_collector.h"
#include "neural_network_params.h"
#include <stdlib.h>

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

void set_conv1D(struct Conv1D L, int input_shape, int kernel_size, int filters){
    // These will emulate the constructors
    L.input_shape= input_shape;
    L.kernel_size = kernel_size;
    L.filters= filters;
    L.h = (float **)malloc((input_shape-L.kernel_size+1) * sizeof(float*));
    for (int i=0; i< (input_shape- kernel_size+1); i++){
        L.h[i] = (float*)malloc(filters * sizeof(float));
    }
    num_layers++;
    L.output_shape= (int)((input_shape-kernel_size+1)/2.0);
}

void fwd_conv1D(struct Conv1D L, float ***W, float *b,  float ** window){

    for (int i=0; i<L.input_shape-L.kernel_size+1; i++){
        for (int j=0; j<L.filters; j++){
            L.h[i][j]= b[j];
            for (int x=0; x<L.kernel_size; x++){
                for (int y=0; y<NUM_ADC; y++){
                    L.h[i][j] += W[x][y][j] * window[i+x][y];
                }    
            }
        }
    }
}

void set_maxpool1D(struct MaxPooling1D L, int input_shape, int pool_size, int strides){
    // These will emulate the constructors
    L.pool_size = pool_size;
    L.strides= strides;
    L.input_shape = input_shape;
    num_layers++;
    L.h= malloc((int)(L.input_shape * sizeof(float*)));
    for (int i=0; i<(int)L.input_shape; i++){
        L.h[i]= malloc(pool_size * sizeof(float));
    }
    L.output_shape= pool_size;
}

void fwd_maxpool1D(struct MaxPooling1D L, float ***W, float *b, float ** window){
    for (int i=0; i< L.input_shape; i++){
        for (int j=0; j<L.pool_size; j++){
            L.h[i][j] = max(window[2*i][j], window[2*i+1][j]);
        }
    }
}

void set_dense(struct Dense L, int input_size, int output_size, char activation){
    // These will emulate the constructor

   L.input_size= input_size;
   L.output_size= output_size;
   L.activation = activation;
   num_layers++;
   L.h= malloc(output_size * sizeof (float));
}

void fwd_dense(struct Dense L, float ** W, float * b, float * window){
    for (int i=0; i<L.output_size; i++){
        L.h[i] = b[i];
        for (int j=0; j<L.input_size; j++){
            L.h[i]+= W[j][i] * window[j]; 
        }
        if (L.activation=='r'){
            L.h[i]= max(L.h[i], 0.0);
        } 
    } 
}

void flatten2D1D(struct Flatten2D1D FLAT, struct MaxPooling1D PREV){
    FLAT.in_shape_0 = sizeof(PREV.h)/ sizeof(PREV.h[0]);
    FLAT.in_shape_1 = sizeof(PREV.h[0])/FLAT.in_shape_0;

    FLAT.h= malloc(FLAT.in_shape_0*FLAT.in_shape_1 * sizeof(float));

    for (int i=0; i<FLAT.in_shape_0; i++){
        for (int j=0; j<FLAT.in_shape_1; j++){
            int idx= FLAT.in_shape_0*i+j;
            FLAT.h[idx] = PREV.h[i][j];
        }
    }
}

void neural_network_forward()
{
    // This will feed forward the neural newtork. 
    // First, we need to declare the structures 
    // for each layer. 
    
    struct Conv1D L1;
    set_conv1D(L1, WINDOW_SIZE, 20, 12);
    fwd_conv1D(L1, W_0, b_0, window);
    struct MaxPooling1D MP1;
    set_maxpool1D(MP1, L1.output_shape, 12, 1);
    fwd_maxpool1D(MP1, W_1, b_1, L1.h);
    struct Conv1D L2;
    set_conv1D(L2, MP1.output_shape, 20, 12);
    fwd_conv1D(L2, W_2, b_2, MP1.h);
    struct MaxPooling1D MP2;
    set_maxpool1D(MP2, L2.output_shape, 12, 1);
    fwd_maxpool1D(MP2, W_3, b_3, L2.h);
    struct Flatten2D1D FL;
    flatten2D1D(FL, MP2);
    struct Dense D1;
    set_dense(D1, FL.output_shape, 1000,  'r');
    fwd_dense(D1, W_4, b_4, FL.h);
    struct Dense D2;
    set_dense(D2, D1.output_shape, 500, 'r');
    fwd_dense(D2, W_5, b_5, D1.h);
    struct Dense D3;
    set_dense(D3, D2.output_shape, 3, 'n');
    fwd_dense(D3, W_6, b_6, D2.h);
}

