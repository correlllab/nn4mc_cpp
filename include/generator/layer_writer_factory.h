#ifndef __LAYER_FACTORY_H__
#define __LAYER_FACTORY_H__

/* 
 * Might not need it 
 * 
 * */

#include <string>

class LayerWriterFactory{
    // Abstract Factory that instantiates LayerWriterFactory depending on the type.
    public:
        virtual LayerWriter * create(std::string)=0;
};

class ActivationFactory : public LayerWriterFactory{
    public:
        ActivationWriter* create(std::string template_path){return new ActivationWriter(template_path);}
}

// See src/LayerWriterFactory.cpp for specific subclasses
class Conv1DWriterFactory : public LayerWriterFactory {
              public:
                     Conv1DWriter* create(std::string template_path){return new Conv1DWriter(template_path);}
};
  
  
class Conv2DWriterFactory : public LayerWriterFactory {
              public:
                     Conv2DWriter* create(std::string template_path){return new Conv2DWriter(template_path);}
    
};

class DenseWriterFactory : public LayerWriterFactory {
          public:
                 DenseWriter* create(std::string template_path){return new DenseWriter(template_path);} 
    
    
    
};

class FlattenWriterFactory : public LayerWriterFactory {
          public:
                                     FlattenWriter* create(std::string template_path){return new FlattenWriter(template_path);}
    
    
};

class MaxPooling1DWriterFactory : public LayerWriterFactory {
          public:
                                     MaxPooling1DWriter* create(std::string template_path){return new MaxPooling1DWriter(template_path);}


};

class MaxPooling2DWriterFactory : public LayerWriterFactory {
          public:
                                     MaxPooling2DWriter* create(std::string template_path){return new MaxPooling2DWriter(template_path);}


};

#endif 
