#ifndef _LAYER_H__
#define _LAYER_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>


class Layer{

    // Types of layers defined, and number of defined layers
    static std::array<std::string, 9> layer_types;    

    public:
        static std::string type;
        std::string layer_type;
        std::string identifier;
        Layer(std::string);
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

    public:
        static std::string type;
        Conv1D(std::string);
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

    public:
        static std::string type;
        Conv2D(std::string);
        void setLayer(){} 
};

class Dense : public Layer{
    

    public:
        int units;
        std::string activation;
        bool use_bias;

    public:
        static std::string type;
        Dense(std::string);
        void setLayer(){}
};


class Flatten : public Layer{
    

    public:
        static std::string type;
        Flatten(std::string);
        void setLayer(){}
};

class MaxPooling1D : public Layer{
    

    public:
        int pool_size;
        int strides;
        std::string padding;
        std::string data_format;

    public:
        static std::string type;
        MaxPooling1D(std::string);
        void setLayer(){}
} ;

class MaxPooling2D: public Layer{
    

    public:
        std::vector<int> pool_size;
        std::vector<int> strides;
        std::string padding;
        std::string data_format;

    public:
        static std::string type;
        MaxPooling2D(std::string);
        void setLayer(){}
};

class SimpleRNN : public Layer{
    

    public:
        int units;
        std::string activation;
        bool use_bias;

    public:
        static std::string type;
        SimpleRNN(std::string);
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

    public:
        static std::string type;

        GRU(std::string);
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

    public:
        static std::string type;

          //this->identifier = id;
        LSTM(std::string);
        void setLayer(){}
};


#endif
