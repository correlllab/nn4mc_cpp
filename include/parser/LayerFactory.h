#ifndef __LAYER_FACTORY_H__
#define __LAYER_FACTORY_H__

#include "parser/LayerBuilder.h"
#include <string>

class LayerFactory{
    public:
        virtual LayerBuilder * create(std::string)=0;
};

class Conv1DFactory : public LayerFactory {
              public:
                     Conv1DBuilder* create(std::string id){return new Conv1DBuilder(id);}
};
  
  
class Conv2DFactory : public LayerFactory {
              public:
                     Conv2DBuilder* create(std::string id){return new Conv2DBuilder(id);}
                                      
};

class DenseFactory : public LayerFactory {
          public:
                 DenseBuilder* create(std::string id){return new DenseBuilder(id);} 
                                           
                                           
                                      
};

class FlattenFactory : public LayerFactory {
          public:
                                     FlattenBuilder* create(std::string id){return new FlattenBuilder(id);}
                                           
                                      
};

class GRUFactory : public LayerFactory {
          public:
                                     GRUBuilder* create(std::string id){return new GRUBuilder(id);}
                                           
                                      
};

class LSTMFactory : public LayerFactory {
          public:
                                     LSTMBuilder* create(std::string id){return new LSTMBuilder(id);}
                                           
                                      
};

class MaxPooling1DFactory : public LayerFactory {
          public:
                                     MaxPooling1DBuilder* create(std::string id){return new MaxPooling1DBuilder(id);}
                                           
                                      
};

class MaxPooling2DFactory : public LayerFactory {
          public:
                                     MaxPooling2DBuilder* create(std::string id){return new MaxPooling2DBuilder(id);}
                                           
                                      
};

class SimpleRNNFactory : public LayerFactory {
          public:
                                     SimpleRNNBuilder* create(std::string id){return new SimpleRNNBuilder(id);}
                                           
                                      
};



#endif
