#ifndef _SIMPLERNN_H
#define _SIMPLERNN_H

#include "Weights.h"

class SimpleRNN
{
    private:
        int units;
        std::string activation;
        bool use_bias;
        Weights Wb; 
};

#endif
