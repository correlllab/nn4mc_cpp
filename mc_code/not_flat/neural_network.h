#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

volatile int num_layers= 0;

struct Conv1D {
    int kernel_size;
    int filters;
    int strides;
    int weight_shape[3];
    int output_shape[2];
    int input_shape[2];
};

struct MaxPooling1D {
    int pool_size;
    int input_shape[2];
    int output_shape[2];
    int strides;
};

struct Dense {
    int input_shape[2];
    int output_shape[2];
    char activation;
};

struct Flatten2D1D {
    int input_shape[2];
    int output_shape;
};


#endif


