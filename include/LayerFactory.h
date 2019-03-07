#ifndef __LAYER_FACTORY_H__
#define __LAYER_FACTORY_H__

#include "LayerBuilder.h"

class LayerFactory{
    // Abstract Factory that instantiates LayerFactory depending on the type.
    public:
        LayerBuilder * create()=0;
};
// See src/LayerFactory.cpp for specific subclasses
class Conv1DFactory : public LayerFactory {
              public:
                     Conv1DBuilder* create(){return new Conv1DBuilder();};
                                               
                                          
};
  
  
class Conv2DFactory : public LayerFactory {
              public:
                     Conv2DBuilder* create(){return new Conv2DBuilder();}
                                           
                                           
                                      
};

class DenseFactory : public LayerFactory {
          public:
                 DenseBuilder* create(){return new DenseBuilder();} 
                                           
                                           
                                      
};

class FlattenFactory : public LayerFactory {
          public:
                                     FlattenBuilder* create(){return new FlattenBuilder();}
                                           
                                      
};

class GRUFactory : public LayerFactory {
          public:
                                     GRUBuilder* create(){return new GRUBuilder();}
                                           
                                      
};

class LSTMFactory : public LayerFactory {
          public:
                                     LSTMBuilder* create(){return new LSTMBuilder();}
                                           
                                      
};

class MaxPooling1DFactory : public LayerFactory {
          public:
                                     MaxPooling1DBuilder* create(){return new MaxPooling1DBuilder();}
                                           
                                      
};

class MaxPooling2DFactory : public LayerFactory {
          public:
                                     MaxPooling2DFactory* create(){return new MaxPooling2DBuilder();}
                                           
                                      
};

class SimpleRNNFactory : public LayerFactory {
          public:
                                     SimpleRNNBuilder* create(){return new SimpleRNNBuilder();}
                                           
                                      
};



#endif
