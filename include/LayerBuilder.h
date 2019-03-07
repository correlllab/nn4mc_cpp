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

class LayerBuilder{
    // Builder class for dynamic instantiation
    private: 
            std::string layer_id;
            std::string layer_type;
            NeuralNetwork NN;
    public:
            void createLayer();
            ~LayerBuilder() {}
};

class Conv1DBuilder : public LayerBuilder {
    private:
        Conv1D layerObject();
    public:
        void createLayer(){
        };
};

class Conv2DBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        Conv2D layerObject();
    public:
        void createLayer(){
        } 

};

class DenseBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        Dense layerObject();
    public:
        void createLayer(){
        } 

};

class FlattenBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        Flatten layerObject();
    public:
        void createLayer(){
        } 

};

class GRUBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        GRU layerObject();
    public:
        void createLayer(){
        } 
};

class LSTMBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        LSTM layerObject();
    public:
        void createLayer(){

            
        } 

};

class MaxPooling1DBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        MaxPooling1D layerObject();
    public:
        void createLayer(){

            
        } 

};

class MaxPooling2DBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        MaxPooling2D layerObject();
    public:
        void createLayer(){

            
        } 

};

class SimpleRNNBuilder : public LayerBuilder {
    private:
        //Parser parsedObject(); 
        SimpleRNN layerObject();
    public:
         void createLayer(){

            
        } 

};
#endif
