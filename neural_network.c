#include "neural_network.h"
#include "adc_collector.h"
#include  "neural_network_params.h"

#define max(a, b) (((a)>(b) ? (a) : (b)))
#define min(a, b) (((a)<(b) ? (a) : (b)))

void set_conv1D(struct Conv1D L, int input_shape, int kernel_size, int filters){
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

void set_maxpool1D(struct MaxPooling1D L, int pool_size, int strides){
    // These will emulate the constructors
    L.pool_size = pool_size;
    L.strides= strides;
    num_layers++;
    L.h= malloc((int)((WINDOW_SIZE-kernel_size)/2.0) * sizeof(float*));
    for (int i=0; i<(int)((WINDOW_SIZE-kernel_size)/2.0); i++){
        L.h[i]= malloc(pool_size)
    }

}

void set_dense(struct Dense L, int input_size, int output_size, char activation){
    // These will emulate the constructor
   L.input_size= input_size;
   L.output_size= output_size;
   L.activation = activation;
   num_layers++;
}


void neural_network_forward()
{
    // This will perform a feedforward in the neural network. 
    
    

}

