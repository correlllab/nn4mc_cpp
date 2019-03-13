/*
Sarah Aguasvivas :)
LayerBuilder: This is an abstract class that interacts with 
Parser, Layers and Neural network. This class maps the corresponding
parsed object to the right layer. 

*/
#ifndef __LAYERBUILDER_H__
#define __LAYERBUILDER_H__

#include <iostream>
#include <string>
#include <map>
#include "Layer.h"
#include "NeuralNetwork.h"
#include <nlohmann/json.hpp>

using json=nlohmann::json;

class LayerBuilder{
    // Builder class for dynamic instantiation
    private: 
            std::string layer_id;
            std::string layer_type;
            NeuralNetwork NN;
    public:
            virtual void create_from_json(json obj, std::string id)=0;
            virtual ~LayerBuilder() {};
};

class Conv1DBuilder : public LayerBuilder {
    private:
        Conv1D layerObject();

    public:
        void create_from_json(json object, std::string id);
};

class Conv2DBuilder : public LayerBuilder {
    private:
        Conv2D layerObject();
    public:
        void create_from_json(json object, std::string id); 

};

class DenseBuilder : public LayerBuilder {
    private:
        Dense layerObject();
    public:
        void create_from_json(json object, std::string id); 

};

class FlattenBuilder : public LayerBuilder {
    private:
        Flatten layerObject();
    public:
        void create_from_json(json object, std::string id);

};

class GRUBuilder : public LayerBuilder {
    private:
        GRU layerObject();
    public:
        void create_from_json(json object, std::string id);
};
class LSTMBuilder : public LayerBuilder {
    private:
        LSTM layerObject();
    public:
        void create_from_json(json object, std::string id); 

};

class MaxPooling1DBuilder : public LayerBuilder {
    private:
        MaxPooling1D layerObject();
    public:
        void create_from_json(json object, std::string id); 

};

class MaxPooling2DBuilder : public LayerBuilder {
    private:
        MaxPooling2D layerObject();
    public:
        void create_from_json(json object, std::string id); 

};

class SimpleRNNBuilder : public LayerBuilder {
    private:
        SimpleRNN layerObject();
    public:
         void create_from_json(json object, std::string id);

};
#endif
