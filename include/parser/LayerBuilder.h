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
#include "datastructures/Layer.h"
#include "datastructures/NeuralNetwork.h"
#include <nlohmann/json.hpp>

using json=nlohmann::json;

class LayerBuilder{
    // Builder class for dynamic instantiation
    public: 
            std::string layer_id;
            virtual void create_from_json(json obj, std::string id, std::map<std::string, Layer*>&)=0;
            virtual ~LayerBuilder() = default;
};

class InputBuilder : public LayerBuilder{
    public:
        InputLayer * layerObject;
        InputBuilder(std::string id){
            this->layer_id = id;
            layerObject = new InputLayer(id);
        }
        void create_from_json(json object, std::string id, std::map<std::string, Layer*>&);
};


class Conv1DBuilder : public LayerBuilder {
    public:
        Conv1D * layerObject; 
        Conv1DBuilder(std::string id){
            this->layer_id = id;
            layerObject= new Conv1D(id);
        }
        void create_from_json(json object, std::string id, std::map<std::string, Layer*>&);
};
class Conv2DBuilder : public LayerBuilder {
    public:
        Conv2D * layerObject;
        Conv2DBuilder(std::string id){
            this->layer_id = id;
            layerObject= new Conv2D(id);
        }
        void create_from_json(json object, std::string id, std::map<std::string, Layer*>&); 

};

class DenseBuilder : public LayerBuilder {
    public:
        Dense * layerObject;
        DenseBuilder(std::string id){
            this->layer_id = id;
            layerObject= new Dense(id);
        }
        void create_from_json(json object, std::string id, std::map<std::string, Layer*>&); 

};

class FlattenBuilder : public LayerBuilder {
    public:
        Flatten * layerObject;
        FlattenBuilder(std::string id){
            this->layer_id= id;
            layerObject= new Flatten(id);
        }
        void create_from_json(json object, std::string id, std::map<std::string, Layer*>&);

};

class GRUBuilder : public LayerBuilder {
    public:
        GRU * layerObject;
        GRUBuilder(std::string id){
            this->layer_id = id;
            layerObject= new GRU(id);
        }
        void create_from_json(json object, std::string id, std::map<std::string, Layer*>&);
};
class LSTMBuilder : public LayerBuilder {
    public:
        LSTM * layerObject;
        LSTMBuilder(std::string id){
            this->layer_id = id;
            layerObject = new LSTM(id);
        }
        void create_from_json(json object, std::string id, std::map<std::string, Layer*>&); 

};

class MaxPooling1DBuilder : public LayerBuilder {
    public:
        MaxPooling1D * layerObject;
        MaxPooling1DBuilder(std::string id){
            this->layer_id = id;
            layerObject= new MaxPooling1D(id);
        }
        void create_from_json(json object, std::string id, std::map<std::string, Layer*>&); 

};

class MaxPooling2DBuilder : public LayerBuilder {
    public:
        MaxPooling2D * layerObject;
        MaxPooling2DBuilder(std::string id){
            this->layer_id = id;
            layerObject= new MaxPooling2D(id);
        }
        void create_from_json(json object, std::string id, std::map<std::string, Layer*>&); 

};

class SimpleRNNBuilder : public LayerBuilder {
    public:
        SimpleRNN * layerObject;
        SimpleRNNBuilder(std::string id){
            this->layer_id= id;
            layerObject= new SimpleRNN(id);
        }
         void create_from_json(json object, std::string id, std::map<std::string, Layer*>&);

};
#endif
