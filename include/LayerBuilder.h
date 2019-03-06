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
#include "Layers.h"
#include "Parser.h"
#include "NeuralNetwork.h"
#include "LayerFactory.h"

typedef std::map<std::string, LayerFactory *> builder_map;

class LayerBuilder{
    // Builder class for dynamic instantiation
    private: 
        // need some sort of dynamic instantiation
            std::string layer_id;
            std::string layer_type;
            struct LayerNode;
            NeuralNetwork NN;
            builder_map LayerFactories;
    public:
            ~LayerBuilder();
            LayerBuilder(std::string type){
                LayerFactories[]= new 
            }

};


class Conv1DBuilder : public LayerBuilder {
    private:
        //Parser parsedObject();
        Conv1D layerObject();

    public:
};


class Conv2DBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        Conv2D layerObject();
    public:

            
        } 

};

class DenseBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        Dense layerObject();
    public:

            
        } 

};

class FlattenBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        Flatten layerObject();
    public:

            
        } 

};

class GRUBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        GRU layerObject();
    public:

            
        } 

};

class LSTMBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        LSTM layerObject();
    public:

            
        } 

};

class MaxPooling1DBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        MaxPooling1D layerObject();
    public:

            
        } 

};

class MaxPooling2DBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        MaxPooling2D layerObject();
    public:

            
        } 

};

class SimpleRNNBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        SimpleRNN layerObject();
    public:

            
        } 

};

#endif
