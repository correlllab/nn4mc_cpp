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

class LayerBuilder{
    private: 
            std::string layer_id;
    public:
            virtual void createLayer() = 0;
};


class Conv1DBuilder : public LayerBuilder {
    private:
        Parser parsedObject;
        Conv1D layerObject;

    public:
        virtual void createLayer(){

            
        } 

};


class Conv2DBuilder : public LayerBuilder {
    private:
        Parser parsedObject; 
        Conv2D layerObject;
    public:
        virtual void createLayer(){

            
        } 

};

class DenseBuilder : public LayerBuilder {
    private:
        Parser parsedObject; 
        Dense layerObject;
    public:
        virtual void createLayer(){

            
        } 

};

class FlattenBuilder : public LayerBuilder {
    private:
        Parser parsedObject; 
        Flatten layerObject;
    public:
        virtual void createLayer(){

            
        } 

};

class GRUBuilder : public LayerBuilder {
    private:
        Parser parsedObject; 
        GRU layerObject;
    public:
        virtual void createLayer(){

            
        } 

};

class LSTMBuilder : public LayerBuilder {
    private:
        Parser parsedObject; 
        LSTM layerObject;
    public:
        virtual void createLayer(){

            
        } 

};

class MaxPooling1DBuilder : public LayerBuilder {
    private:
        Parser parsedObject; 
        MaxPooling1D layerObject;
    public:
        virtual void createLayer(){

            
        } 

};

class MaxPooling2DBuilder : public LayerBuilder {
    private:
        Parser parsedObject; 
        MaxPooling2D layerObject;
    public:
        virtual void createLayer(){

            
        } 

};

class SimpleRNNBuilder : public LayerBuilder {
    private:
        Parser parsedObject; 
        SimpleRNN layerObject;
    public:
        virtual void createLayer(){

            
        } 

};







#endif
