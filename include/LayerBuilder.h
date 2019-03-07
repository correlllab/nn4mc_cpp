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
#include "Parser.h"
#include "NeuralNetwork.h"
#include "LayerFactory.h"


class LayerBuilder{
    // Builder class for dynamic instantiation
    private: 
            std::string layer_id;
            std::string layer_type;
            NeuralNetwork NN;
    public:
            virtual void createLayer(Parser parsedObject) = 0;
            virtual ~LayerBuilder() {}
};

class Conv1DBuilder : public LayerBuilder {
    private:
        Conv1D layerObject();
    public:
        virtual void createLayer(){
        };
};

class Conv2DBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        Conv2D layerObject();
    public:
        virtual void createLayer(Parser parsedObject){
        } 

};

class DenseBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        Dense layerObject();
    public:
        virtual void createLayer(Parser parsedObject){
        } 

};

class FlattenBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        Flatten layerObject();
    public:
        virtual void createLayer(Parser parsedObject){
        } 

};

class GRUBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        GRU layerObject();
    public:
        virtual void createLayer(Parser parsedObject){
        } 
};

class LSTMBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        LSTM layerObject();
    public:
        virtual void createLayer(Parser parsedObject){

            
        } 

};

class MaxPooling1DBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        MaxPooling1D layerObject();
    public:
        virtual void createLayer(Parser parsedObject){

            
        } 

};

class MaxPooling2DBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        MaxPooling2D layerObject();
    public:
        virtual void createLayer(Parser parsedObject){

            
        } 

};

class SimpleRNNBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        SimpleRNN layerObject();
    public:
        virtual void createLayer(Parser parsedObject){

            
        } 

};
#endif
