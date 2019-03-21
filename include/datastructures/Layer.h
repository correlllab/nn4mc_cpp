#ifndef _LAYER_H__
#define _LAYER_H__

#include <iostream>
#include <string>
#include <vector>
#include "datastructures/weights.h"
#include <map>


class Layer{

    // Types of layers defined, and number of defined layers
    static std::array<std::string, 9> layer_types; 

    public:
        static std::string type;
        std::string layer_type;
        std::string identifier;
        Weight* w;
        Weight* b;
        virtual void setLayer() = 0;
        virtual ~Layer() {};
        virtual bool isInput() = 0;
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
        Conv1D(std::string id){this->identifier = id;}
        void setLayer(){}
        bool isInput() {return false;}

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
        Conv2D(std::string id){this->identifier= id;}
        void setLayer(){} 
        bool isInput() {return false;}
};

class Dense : public Layer{
    

    public:
        int units;
        std::string activation;
        bool use_bias;

    public:
        static std::string type;
        Dense(std::string id){this->identifier= id;}
        void setLayer(){}
        bool isInput() {return false;}
};


class Flatten : public Layer{
    

    public:
        static std::string type;
        Flatten(std::string id){this->identifier= id;}
        void setLayer(){}
        bool isInput() {return false;}
};

class MaxPooling1D : public Layer{
    

    public:
        int pool_size;
        int strides;
        std::string padding;
        std::string data_format;

    public:
        static std::string type;
        MaxPooling1D(std::string id){this->identifier=id;}
        void setLayer(){}
        bool isInput() {return false;}
} ;

class MaxPooling2D: public Layer{
    

    public:
        std::vector<int> pool_size;
        std::vector<int> strides;
        std::string padding;
        std::string data_format;

    public:
        static std::string type;
        MaxPooling2D(std::string id){this->identifier= id;}
        void setLayer(){}
        bool isInput() {return false;}
};

class SimpleRNN : public Layer{
    

    public:
        int units;
        std::string activation;
        bool use_bias;

    public:
        static std::string type;
        SimpleRNN(std::string id){this->identifier= id;}
        void setLayer(){}
        bool isInput() {return false;}
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

        GRU(std::string id){this->identifier= id;}
        void setLayer(){}
        bool isInput() {return false;}
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

        LSTM(std::string id){this->identifier= id;}
        void setLayer(){}
        bool isInput() {return false;}
};

class InputLayer: public Layer{
    public:
      static std::string type;
      std::vector<int> layer_size;
      InputLayer(std::string id){this->identifier=id;}
      void setLayer(){}
      bool isInput() {return true;};
};


#endif
