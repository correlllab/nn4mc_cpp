#include <iostream>
#include <string>
#include <vector>
#include "Weights.h"

class Layer{
        private:
            std::string identifier;

        public:

            Layer(std::string id){
                this.identifier = id;
            }
};

class Conv1D : public Layer{
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


class Conv2D : public Layer{
    private:
        int filters;
        int kernel_size;
        std::vector<int> strides;
        std::string padding;
        std::string data_format;
        std::vector<int> dilation_rate;
        std::string activation;
        bool use_bias;
        Weight4D Wb;
        // no need for training-specific variables. 
        
    public:
};

class Dense : public Layer{
    private:
        int units;
        std::string activation;
        bool use_bias;
        //no training-specific parameters
        Weight2D Wb;
    public:

};


class Flatten : public Layer{


};

class MaxPooling1D : public Layer{
    private:
        int pool_size;
        int strides;
        std::string padding;
        std::string data_format;
    public:
} ;

class MaxPooling2D: public Layer{
    private:
        std::vector<int> pool_size;
        std::vector<int> strides;
        std::string padding;
        std::string data_format;
    public:

};

class SimpleRNN : public Layer{
    private:
        int units;
        std::string activation;
        bool use_bias;
    public:

};

class GRU: public Layer{
    private:
        int units;
        std::string activation;
        std::string recurrent_activation;
        bool use_bias;
        float dropout;
        float recurrent dropout;
        bool go_backwards;
        bool stateful;
        bool unrool;
        bool reset_after;
    public:
};


class LSTM: public Layer{
    private:
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
};
