#ifndef _CONV2D_h
#define _CONV2D_h
#include "Weights.h"

class Conv2D
{
    private:
        int filters;
        int kernel_size;
        std::vector<int> strides;
        std::string padding;
        std::string data_format;
        std::vector<int> dilation_rate;
        std::string activation;
        bool use_bias;
        Weights Wb;
        // no need for training-specific variables.

    public:
};

#endif
