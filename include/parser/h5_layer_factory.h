#ifndef __LAYER_FACTORY_H__
#define __LAYER_FACTORY_H__

#include "parser/h5_layer_builder.h"
#include <string>

class LayerFactory{
    public:
        LayerBuilder* layer_builder;
        virtual LayerBuilder * create(std::string)=0;
};

class DropoutFactory : public LayerFactory{
    public:
        DropoutBuilder * layer_builder;
        DropoutBuilder * create(std::string id){
        layer_builder = new DropoutBuilder(id);
        return layer_builder;
        }

};

class ActivationFactory : public LayerFactory{
    public:
        ActivationBuilder * layer_builder;
        ActivationBuilder * create(std::string id){
        layer_builder = new ActivationBuilder(id);
        return layer_builder;
        }

};

class Conv1DFactory : public LayerFactory {
            
              public:
                     Conv1DBuilder* layer_builder;
                     Conv1DBuilder* create(std::string id){
                     layer_builder = new Conv1DBuilder(id);
                     return layer_builder;
                     }
};
  
  
class Conv2DFactory : public LayerFactory {
              public:
                    Conv2DBuilder* layer_builder;
                    Conv2DBuilder* create(std::string id){
                         layer_builder = new Conv2DBuilder(id);
                         return layer_builder;              
                     }
                                      
};

class DenseFactory : public LayerFactory {
          public:
                    DenseBuilder* layer_builder;
                    DenseBuilder* create(std::string id){
                     layer_builder =new DenseBuilder(id);
                     return layer_builder;        
                 } 
};

class FlattenFactory : public LayerFactory {
          public:
                    FlattenBuilder* layer_builder;              
                     FlattenBuilder* create(std::string id){
                         layer_builder = new FlattenBuilder(id);
                         return layer_builder;
                     }
};

class GRUFactory : public LayerFactory {
          public:
                    GRUBuilder* layer_builder;
                     GRUBuilder* create(std::string id){
                         layer_builder = new GRUBuilder(id);
                         return layer_builder;
                     }
                                   
                                      
};

class LSTMFactory : public LayerFactory {
          public:
              LSTMBuilder* layer_builder;
                 LSTMBuilder* create(std::string id){
                     layer_builder = new LSTMBuilder(id);
                     return layer_builder;
                 }
                                           
                                      
};

class MaxPooling1DFactory : public LayerFactory {
          public:
              MaxPooling1DBuilder* layer_builder;
                     MaxPooling1DBuilder* create(std::string id){
                         layer_builder = new MaxPooling1DBuilder(id);
                         return layer_builder;}
                                           
                                      
};

class MaxPooling2DFactory : public LayerFactory {
          public:
                    MaxPooling2DBuilder* layer_builder;
                 MaxPooling2DBuilder* create(std::string id){
                     layer_builder = new MaxPooling2DBuilder(id);
                     return layer_builder;
                 }
};

class SimpleRNNFactory : public LayerFactory {
          public:
                    SimpleRNNBuilder* layer_builder;
                    SimpleRNNBuilder* create(std::string id){
                    layer_builder =new SimpleRNNBuilder(id);
                    return layer_builder;        
                 } 
};


#endif
