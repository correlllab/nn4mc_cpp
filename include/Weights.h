#ifndef __WEIGHTS_H__
#define __WEIGHTS_H__

#include <iostream>
#include <string>
#include <vector>
#include "datastructures/tensor.h"

class Weights {
    public:
        std::vector<int> weights_size;
        std::vector<int> bias_size;
        Tensor<float> *W;
        Tensor<float> *b;
};

#endif
