#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__


//#define WINDOW_SIZE     50
//#define NUM_ADC         2

volatile int num_layers= 0;

struct Conv1D {
    int kernel_size[1];
    int filters;
    const float * weights;
    const float * biases;
    int strides;
    int output_shape[2];
    int input_shape[2];
    int weight_shape[3];
};

struct MaxPooling1D {
    int pool_size;
    int input_shape[2];
    int output_shape[2];
    int strides;
};

struct Dense {
    int input_shape[1];
    int output_shape[1];
    const float * weights;
    const float * biases;
    int weight_shape[2];
    char activation;
};

struct Flatten2D1D {
    int input_shape[2];
    int output_shape[1];
};


#endif


