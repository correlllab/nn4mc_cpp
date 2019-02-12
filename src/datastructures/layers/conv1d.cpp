#include "datastructures/weights.h"
#include "datastructures/layers/conv1d.h"

Conv1D::Conv1D(Weights* _kernel, Weights* _bias, std::vector<unsigned int> _stride, std::vector<unsigned int> _input_shape)
{
    // Store the kernel, bias and stride
    kernel = _kernel;
    bias = _bias;
    stride = _stride;

    // Keep track if there's no bias -- don't want to write it to the microcontroller code
    if(_bias == NULL)   has_bias = false;

    input_shape = _input_shape;

    // Calculate what the output shape should be...
}


Conv1D::~Conv1D()
{
    
}

#endif


