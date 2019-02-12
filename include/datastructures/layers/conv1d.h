#ifndef __LAYERS_CONV1D_H__
#define __LAYERS_CONV1D_H__

#include "datastructures/weights.h"

class Conv1D
{
    private:
        bool has_bias;
        Weights* kernel;
        Weights* bias;

        std::vector<unsigned int> input_shape;
        std::vector<unsigned int> output_shape;

        std::vector<unsigned int> stride;

    public:
        Conv1D(Weights*, Weights*, std::vector<unsigned int>, std::vector<unsigned int>);
        ~Conv1D();
};


#endif


