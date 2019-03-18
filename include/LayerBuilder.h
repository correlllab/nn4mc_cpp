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
    public: 
            std::string layer_id;
            virtual void create_from_json(json obj, std::string id)=0;
            virtual ~LayerBuilder() = default;
};

class Conv1DBuilder : public LayerBuilder {
    public:
        Conv1D layerObject;
        void create_from_json(json object, std::string id);
};
class Conv2DBuilder : public LayerBuilder {
    public:
        Conv2D layerObject;
        void create_from_json(json object, std::string id); 

};

class DenseBuilder : public LayerBuilder {
    public:
        Dense layerObject;
        void create_from_json(json object, std::string id); 

};

class FlattenBuilder : public LayerBuilder {
    public:
        Flatten layerObject;
        void create_from_json(json object, std::string id);

};

class GRUBuilder : public LayerBuilder {
    public:
        GRU layerObject;
        void create_from_json(json object, std::string id);
};
class LSTMBuilder : public LayerBuilder {
    public:
        LSTM layerObject;
        void create_from_json(json object, std::string id); 

};

class MaxPooling1DBuilder : public LayerBuilder {
    public:
        MaxPooling1D layerObject;
        void create_from_json(json object, std::string id); 

};

class MaxPooling2DBuilder : public LayerBuilder {
    public:
        MaxPooling2D layerObject;
        void create_from_json(json object, std::string id); 

};

class SimpleRNNBuilder : public LayerBuilder {
    public:
        SimpleRNN layerObject;
         void create_from_json(json object, std::string id);

};
#endif
