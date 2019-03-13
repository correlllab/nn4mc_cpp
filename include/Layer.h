#ifndef _LAYER_H__
#define _LAYER_H__


#include <iostream>
#include <string>
#include <vector>

class Layer{
    private:
      //std::string identifier;

    public:
      std::string identifier;
      Layer(std::string id){
          this->identifier = id;
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
//        Weights* w;

        // no need for training-specific variables
    public:
        Conv1D(std::string id) : Layer(id) {}
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
        // no need for training-specific variables.

 //       Weights* w;
        // no need for training-specific variables.

    public:
        Conv2D(std::string id) : Layer(id) {}
};

class Dense : public Layer{
    private:
        int units;
        std::string activation;
        bool use_bias;
        //no training-specific parameters
    public:
  //      Weights* w;

    public:
        Dense(std::string id) : Layer(id) {}
};


class Flatten : public Layer{

    public:
        Flatten(std::string id) : Layer(id) {}
};

class MaxPooling1D : public Layer{
    private:
        int pool_size;
        int strides;
        std::string padding;
        std::string data_format;
    public:
        MaxPooling1D(std::string id) : Layer(id) {}
} ;

class MaxPooling2D: public Layer{
    private:
        std::vector<int> pool_size;
        std::vector<int> strides;
        std::string padding;
        std::string data_format;
    public:
        MaxPooling2D(std::string id) : Layer(id) {}
};

class SimpleRNN : public Layer{
    private:
        int units;
        std::string activation;
        bool use_bias;
    public:
        SimpleRNN(std::string id) : Layer(id) {}
};

class GRU: public Layer{
    private:
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
        GRU(std::string id) : Layer(id) {}
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
          //this->identifier = id;
        LSTM(std::string id) : Layer(id) {}
};


#endif
