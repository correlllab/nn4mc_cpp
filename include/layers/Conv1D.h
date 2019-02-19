#ifndef _CONV1D_H
#define _CONV1D_H

class Conv1D
{
    private:
        int filters;
        int kernel_size;
        int strides;
        std::string padding;
        std::string data_format;
        int dilation_rate;
        std::string activation;
        bool use_bias;
        Weight3D Wb;

        // no need for training-specific variables
    public:
};

#endif
