#ifndef _MAXPOOLING1D_H
#define _MAXPOOLING1D_H

#include "Weights.h"
class MaxPooling1D
{
    private:
        int pool_size;
        int strides;
        std::string padding;
        std::string data_format;
};

#endif
