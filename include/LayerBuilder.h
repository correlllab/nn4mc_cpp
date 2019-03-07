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
            // Assign attributes
                       
            layerObject.kernel_size= parsedObject.kernel_size;
            layerObject.filters= parserdObject.filters;
            layerObject.padding= parsedObject.padding;
            layerObject.data_format= parsedObject.data_format;
            layerObject.dilation_rate= parsedObject.dilation_rate;
            layerObject.activation= parsedObject.activation;
            layerObject.use_bias= parsedObject.use_bias;
            layerObject.kernel_initializer= parsedObject.kernel_initializer;
            layerObject.bias_initializer= parsedObject.bias_initializer;
            layerObject.kernel_regularizer= parsedObject.kernel_regularizer;
            layerObject.bias_regularizer= parsedObject.bias_regularizer;
            layerObject.activity_regularizer= parsedObject.activity_regularizer;
            layerObject.kernel_constraint= parsedObject.kernel_constraint;
            layerObject.bias_constraint= parsedObject.bias_constraint;
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
