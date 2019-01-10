#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__


#define WINDOW_SIZE     100
#define NUM_ADC         2

volatile int num_layers= 0;

struct Conv1D {
    int input_shape;
    int kernel_size;
    int filters;
    int output_shape;
    static float **h;
};

struct MaxPooling1D {
    int pool_size;
    int input_shape;
    int output_shape;
    int strides;
    static float **h;
};

struct Dense {
    int input_size;
    int output_size;
    char activation;
    static float *h;
};

struct Flatten2D1D {
    int in_shape_0;
    int in_shape_1;
    static float *h;
};

void neural_network_forward();

#endif


