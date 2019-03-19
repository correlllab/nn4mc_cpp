#ifndef _LAYER_H__
#define _LAYER_H__

#include <iostream>
#include <string>
#include <vector>
#include "Weights.h"
#include <map>

class Layer{
    public:
        std::string identifier;
        Weights * WB;
        virtual void setLayer() = 0;
        virtual ~Layer() {};
};

class Conv1D : public Layer{
    public:
        int filters;
        std::vector<int> kernel_size;
        int strides;
        std::string padding;
        std::string data_format;
        int dilation_rate;
        std::string activation;
        bool use_bias;
        void setLayer(){}

};


class Conv2D : public Layer{
    public:
        int filters;
        std::vector<int> kernel_size;
        std::vector<int> strides;
        std::string padding;
        std::string data_format;
        std::vector<int> dilation_rate;
        std::string activation;
        bool use_bias;
        void setLayer(){} 
};

class Dense : public Layer{
    public:
        int units;
        std::string activation;
        bool use_bias;
        void setLayer(){}
};


class Flatten : public Layer{
    public:
        void setLayer(){}
};

class MaxPooling1D : public Layer{
    public:
        int pool_size;
        int strides;
        std::string padding;
        std::string data_format;
        void setLayer(){}
} ;

class MaxPooling2D: public Layer{
    public:
        std::vector<int> pool_size;
        std::vector<int> strides;
        std::string padding;
        std::string data_format;
        void setLayer(){}
};

class SimpleRNN : public Layer{
    public:
        int units;
        std::string activation;
        bool use_bias;
        void setLayer(){}
};

class GRU: public Layer{
    public:
        int units;
        std::string activation;
        std::string recurrent_activation;
        bool use_bias;
        float dropout;
        float recurrent_dropout;
        bool go_backwards;
        bool stateful;
        bool unrool;
        bool reset_after;
        void setLayer(){}
};


class LSTM: public Layer{
    public:
        int units;
        std::string activation;
        std::string recursive_activation;
        bool use_bias;
        float dropout;
        float recurrent_dropout;
        int implementation;
        bool go_backwards;
        bool stateful;
        bool unroll;
        void setLayer(){}
};


#endif
