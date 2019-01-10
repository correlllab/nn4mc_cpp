#include "neural_network.h"
#include "adc_collector.h"
#include  "neural_network_params.h"

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

void set_conv1D(struct Conv1D L, int input_shape, int kernel_size, int filters, uint16_t **window){
    // These will emulate the constructors
    L.input_shape= input_shape;
    L.kernel_size = kernel_size;
    L.filters= filters;
    L.h = malloc((input_shape-kernel_size+1) * sizeof(float*));
    for (int i=0; i< (input_shape- kernel_size+1); i++){
        L.h[i] = malloc(filters * sizeof(float));
    }
    num_layers++;
    L.output_shape= (int)((input_shape-kernel_size+1)/2.0);

    }

void set_maxpool1D(struct MaxPooling1D L, int pool_size, int strides, uint16_t ** window){
    // These will emulate the constructors
    L.pool_size = pool_size;
    L.strides= strides;
    num_layers++;
    L.h= malloc((int)((WINDOW_SIZE-kernel_size)/2.0) * sizeof(float*));
    for (int i=0; i<(int)((WINDOW_SIZE-kernel_size)/2.0); i++){
        L.h[i]= malloc(pool_size * sizeof(float))
    }
    L.output_shape= pool_size;

}

void set_dense(struct Dense L, int input_size, int output_size, char activation, uint16_t ** window){
    // These will emulate the constructor
   L.input_size= input_size;
   L.output_size= output_size;
   L.activation = activation;
   num_layers++;
   L.h= malloc(output_size * sizeof (float));
}


void neural_network_forward()
{
    // This will feed forward the neural newtork. 
    // First, we need to declare the structures 
    // for each layer. 
       
    struct Conv1D L1;
    set_conv1D(L1, WINDOW_SIZE, 20, 12, window);
    struct MaxPooling1D MP1;
    set_maxpool1D(MP1, 12, 1, L1.h);
    struct Conv1D L2;
    set_conv1D(L2, MP1.output_shape, 20, 12, MP1.h);
    struct MaxPooling1D MP2;
    set_maxpool1D(MP2, 12, 1, L2);
    struct Dense D1;
    set_dense(D1, MP2.output_shape, 1000,  'r');
    struct Dense D2;
    set_dense(D2, D1.output_shape, 500, 'r');
    struct Dense D3;
    set_dense(D3, D2.output_shape, 3, 'n');
       
    
}

