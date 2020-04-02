/* LayerWriter
 *
 * by Sarah Aguasvivas Manzano
 *
 * LayerWriter: This is an abstract class (Builder) that represents how
 * each layer can write their feed forward events into the templates
 * in different ways. At the end I will map the std::string layer_type to
 * the actual layer writer object.
 *
 */

#ifndef __LAYERWRITER_H__
#define __LAYERWRITER_H__

#include <iostream>
#include <string>
#include <map>
#include "datastructures/Layer.h"

class LayerWriter{
    public:
        std::string init_template;
        std::map<std::string, std::string> activation_lookup;
        
        static LayerWriter* make_writer(Layer*, std::string);
        std::string write_init();
        std::map<std::string, std::string> mapping;
        virtual void build_map(std::string)=0;
        virtual ~LayerWriter() = default;


        void build_activation_lookup();
        std::string LAYER_NAME = "<%LAYER_NAME>";
};

class ActivationGenerator : public LayerWriter{
    public:
        std::string ACTIVATION = "<%ACTIVATION>";
        std::string INPUT_SIZE = "<%INPUT_SIZE>";
        std::string OUTPUT_SIZE= "<%OUTPUT_SIZE>";
        Activation * layer;
        ActivationGenerator(Activation * layer, std::string init) {this->layer= layer; this ->init_template.assign(init);}
        void build_map(std::string);
};

class Conv1DGenerator : public LayerWriter{
    public:
        // mapping maps from delimiter to string value of the delimiter
        // e.g. <%INPUT_SHAPE_0> --> str(layer.input_sh1);

        std::string INPUT_SHAPE_0= "<%INPUT_SHAPE_0>";
        std::string INPUT_SHAPE_1= "<%INPUT_SHAPE_1>";

        std::string STRIDE_SIZE = "<%STRIDE_SIZE>";
        std::string KERNEL_SIZE = "<%KERNEL_SIZE>";
        std::string INPUT_SIZE = "<%INPUT_SIZE>";
        std::string ACTIVATION = "<%ACTIVATION>"; 
        std::string WEIGHT_NAME = "<%WEIGHT_NAME>";
        std::string BIAS_NAME = "<%BIAS_NAME>";
        std::string FILTERS= "<%FILTERS>";

        Conv1D* layer;
        Conv1DGenerator(Conv1D* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);
};
/*
class DropoutGenerator : public LayerWriter{

}*/

class Conv2DGenerator : public LayerWriter{
    public:
        std::string INPUT_SHAPE_0= "<%INPUT_SHAPE_0>";
        std::string INPUT_SHAPE_1= "<%INPUT_SHAPE_1>";
        std::string INPUT_SHAPE_2= "<%INPUT_SHAPE_2>";
       
        std::string KERNEL_SHAPE_0= "<%KERNEL_SHAPE_0>";
        std::string KERNEL_SHAPE_1= "<%KERNEL_SHAPE_1>";
        
        std::string STRIDE_SHAPE_0= "<%STRIDE_SHAPE_0>";
        std::string STRIDE_SHAPE_1= "<%STRIDE_SHAPE_1>";

        std::string WEIGHT_NAME = "<%WEIGHT_NAME>";
        std::string BIAS_NAME = "<%BIAS_NAME>";
        std::string ACTIVATION = "<%ACTIVATION>";
        std::string FILTERS= "<%FILTERS>";
        
        Conv2D * layer;
        Conv2DGenerator(Conv2D* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);

};

class DenseGenerator : public LayerWriter{
    public:

        std::string INPUT_SHAPE_0= "<%INPUT_SHAPE_0>";
        std::string INPUT_SHAPE_1= "<%INPUT_SHAPE_1>";
        
        std::string OUTPUT_SIZE= "<%OUTPUT_SIZE>";

        std::string WEIGHT_NAME = "<%WEIGHT_NAME>";
        std::string BIAS_NAME = "<%BIAS_NAME>";
        std::string ACTIVATION = "<%ACTIVATION>"; 

        Dense* layer;
        DenseGenerator(Dense* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);

};

class SimpleRNNGenerator : public LayerWriter{
     
    public:
        std::string INPUT_SHAPE_0= "<%INPUT_SHAPE_0>";
        std::string INPUT_SHAPE_1= "<%INPUT_SHAPE_1>";
        
        std::string OUTPUT_SIZE= "<%OUTPUT_SIZE>";

        std::string WEIGHT_NAME = "<%WEIGHT_NAME>";
        std::string RECURRENT_WEIGHT_NAME = "<%RECURRENT_WEIGHT_NAME>";
        std::string BIAS_NAME = "<%BIAS_NAME>";
        std::string ACTIVATION = "<%ACTIVATION>"; 
        std::string RECURRENT_ACTIVATION = "<%RECURRENT_ACTIVATION>";

        SimpleRNN* layer;
        SimpleRNNGenerator(SimpleRNN* layer, std::string init){
            this->layer = layer; 
            this->init_template.assign(init);
        }

    void build_map(std::string);

};

class LSTMGenerator : public LayerWriter{
     
    public:
        std::string INPUT_SHAPE_0= "<%INPUT_SHAPE_0>";
        std::string INPUT_SHAPE_1= "<%INPUT_SHAPE_1>";
        
        std::string OUTPUT_SIZE= "<%OUTPUT_SIZE>";

        std::string WEIGHT_NAME = "<%WEIGHT_NAME>";
        std::string RECURRENT_WEIGHT_NAME = "<%RECURRENT_WEIGHT_NAME>";

        std::string BIAS_NAME = "<%BIAS_NAME>";
        std::string ACTIVATION = "<%ACTIVATION>"; 
        std::string RECURRENT_ACTIVATION = "<%RECURRENT_ACTIVATION>";
        std::string USE_BIAS = "<%USE_BIAS>";
        std::string DROPOUT = "<%DROPOUT>";
        std::string RECURRENT_DROPOUT = "<%RECURRENT_DROPOUT>";
        std::string IMPLEMENTATION = "<%IMPLEMENTATION>";
        std::string GO_BACKWARDS = "<%GO_BACKWARDS>";

        LSTM* layer;
        LSTMGenerator(LSTM* layer, std::string init){
            this->layer = layer; 
            this->init_template.assign(init);
        }
    void build_map(std::string);
};


/*class FlattenGenerator : public LayerWriter{
    public:
        std::string BEGIN_CALL_TEMPLATE= "<%BEGIN_CALL_TEMPLATE>";
        std::string END_CALL_TEMPLATE= "<%END_CALL_TEMPLATE>";
        std::string LAYER_ID= "<%LAYER_ID>";
        std::string INPUT_SIZE_0 = "<%INPUT_SIZE_0>";
        std::string INPUT_SIZE_1 = "<%INPUT_SIZE_1>";
        std::string PREVIOUS_LAYER_ID = "<%PREVIOUS_LAYER_ID>";

        Flatten* layer;
        FlattenGenerator(Flatten* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);

};
*/
class MaxPooling1DGenerator : public LayerWriter{
    public:
        std::string INPUT_SHAPE_0= "<%INPUT_SHAPE_0>";
        std::string INPUT_SHAPE_1= "<%INPUT_SHAPE_1>";
        
        std::string OUTPUT_SHAPE_0= "<%OUTPUT_SHAPE_0>";
        std::string OUTPUT_SHAPE_1= "<%OUTPUT_SHAPE_1>";
        
        std::string STRIDES = "<%STRIDES>";
        std::string POOL_SIZE = "<%POOL_SIZE>";

        MaxPooling1D* layer;
        MaxPooling1DGenerator(MaxPooling1D* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);
};

class MaxPooling2DGenerator : public LayerWriter{
    public:
        std::string INPUT_SHAPE_0= "<%INPUT_SHAPE_0>";
        std::string INPUT_SHAPE_1= "<%INPUT_SHAPE_1>";
        std::string INPUT_SHAPE_2= "<%INPUT_SHAPE_2>";
        
        std::string POOL_SHAPE_0 = "<%POOL_SHAPE_0>";
        std::string POOL_SHAPE_1 = "<%POOL_SHAPE_1>";

        std::string STRIDE_SHAPE_0 = "<%STRIDE_SHAPE_0>";
        std::string STRIDE_SHAPE_1 = "<%STRIDE_SHAPE_1>";

        std::string OUTPUT_SHAPE_0= "<%OUTPUT_SHAPE_0>";
        std::string OUTPUT_SHAPE_1= "<%OUTPUT_SHAPE_1>";
        std::string OUTPUT_SHAPE_2= "<%OUTPUT_SHAPE_2>";

        MaxPooling2D* layer;
        MaxPooling2DGenerator(MaxPooling2D* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);
};

#endif
