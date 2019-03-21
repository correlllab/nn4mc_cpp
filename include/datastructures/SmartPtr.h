#ifndef __PARSER_H__
#define __PARSER_H__

#include "datastructures/NeuralNetwork.h"
#include "datastructures/Layer.h"
#include "parser/LayerBuilder.h"

/* Smart Pointer Class */

class SmartPtr{

    public:
        virtual void SmartPtr()=0;
        ~SmartPtr(){}
};

class SmartPtrLayers : SmartPtr{
    public:
        Layer * ptr;
        virtual explicit SmartPtr(Layer *p = NULL){
            ptr= p;
        }

        ~SmartPtr(){
            delete(ptr);
        }

        Layer &operator *(){
            return *ptr;
        }

};

class SmartPtrNN : SmartPtr{
    public:
        NeuralNetwork * ptr;
        explicit SmartPtr(NeuralNetwork *p = NULL){
            ptr=p;
        }
        ~SmartPtr(){
            delete *ptr;
        }
        Layer &operator *(){
            return *ptr;
        }

};

class SmartPtrLayerB : SmartPtr{
    public: 
        LayerBuilder * ptr;
        explicit SmartPtr(LayerBuilder * p  = NULL){
            ptr=p;
        }
        ~SmartPtr(){
            delete *ptr;
        }
        Layer &operator *(){
            return *ptr;
        }

};












#endif
