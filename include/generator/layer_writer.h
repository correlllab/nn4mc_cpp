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
        std::string template_path;
        std::string layer_type;
        virtual std::string write_fwd_function(Layer *)=0;
        virtual ~LayerWriter() = default;
};

class Conv1DGenerator : public LayerWriter{
    public:
        // mapping maps from delimiter to string value of the delimiter
        // e.g. <%INPUT_SHAPE_0> --> str(layer.input_sh1);
        std::map<std::string, std::string> mapping; 

        std::string BEGIN_CALL_TEMPLATE = "<%BEGIN_CALL_TEMPLATE>";
        std::string END_CALL_TEMPLATE = "<%END_CALL_TEMPLATE>";
        std::string LAYER_ID = "<%LAYER_ID>";
        std::string PREVIOUS_LAYER_ID= "<%PREVIOUS_LAYER_ID>";
        std::string INPUT_SHAPE_0= "<%INPUT_SHAPE_0>";
        std::string INPUT_SHAPE_1= "<%INPUT_SHAPE_1>";
        std::string KERNEL_SIZE= "<%KERNEL_SIZE>";
        std::string FILTERS= "<%FILTERS>";
        std::string WEIGHT_SHAPE0= "<%WEIGHT_SHAPE0>";
        std::string WEIGHT_SHAPE1= "<%WEIGHT_SHAPE1>";
        std::string WEIGHT_SHAPE2= "<%WEIGHT_SHAPE2>";
        std::string WEIGHT_VAR = "<%WEIGHT_VAR>";
        std::string BIAS_VAR= "<%BIAS_VAR>";

        std::string template_path;
        Conv1DGenerator(std::string template_path){this->template_path.assign(template_path);}

    std::string write_fwd_function(Conv1D * layer, std::string prev_id);
};

class DenseGenerator : public LayerWriter{
    public:
        std::map<std::string, std::string> mapping;
        std::string BEGIN_CALL_TEMPLATE = "<%BEGIN_CALL_TEMPLATE>";
        std::string END_CALL_TEMPLATE = "<%END_CALL_TEMPLATE>";
        std::string LAYER_ID = "<%LAYER_ID>";
        std::string PREVIOUS_LAYER_ID = "<%PREVIOUS_LAYER_ID>";
        std::string INPUT_SIZE= "<%INPUT_SIZE>";
        std::string OUTPUT_SIZE= "<%OUTPUT_SIZE>";
        std::string WEIGHT_SHAPE0= "<%WEIGHT_SHAPE0>";
        std::string WEIGHT_SHAPE1= "<%WEIGHT_SHAPE1>";
        std::string WEIGHT_SHAPE2= "<%WEIGHT_SHAPE2>";
        std::string ACTIVATION = "<%ACTIVATION>";
        std::string WEIGHT_VAR = "<%WEIGHT_VAR>";
        std::string BIAS_VAR= "<%BIAS_VAR>";

        std::string template_path = ""; 
        DenseGenerator(std::string template_path){this->template_path.assign(template_path);}

    std::string write_fwd_function(Dense * layer, std::string prev_id);

};

class Conv2DGenerator : public LayerWriter{
    public:

        Conv2DGenerator(){}

    std::string write_fwd_function(Conv2D * layer, std::string prev_id);

};

class FlattenGenerator : public LayerWriter{
    public:
        std::map<std::string, std::string> mapping;
        std::string BEGIN_CALL_TEMPLATE= "<%BEGIN_CALL_TEMPLATE>";
        std::string END_CALL_TEMPLATE= "<%END_CALL_TEMPLATE>";
        std::string LAYER_ID= "<%LAYER_ID>";
        std::string INPUT_SIZE_0 = "<%INPUT_SIZE_0>";
        std::string INPUT_SIZE_1 = "<%INPUT_SIZE_1>";
        std::string PREVIOUS_LAYER_ID = "<%PREVIOUS_LAYER_ID>";


        FlattenGenerator(std::string template_path){this->template_path.assign(template_path);}

    std::string write_fwd_function(Flatten * layer, std::string prev_id);

};

class MaxPooling1DGenerator : public LayerWriter{
    public:
        std::map<std::string, std::string> mapping;
        MaxPooling1DGenerator(std::string template_path){this->template_path.assign(template_path);}

    std::string write_fwd_function(MaxPooling1D * layer, std::string prev_id);
};

class MaxPooling2DGenerator : public LayerWriter{
    public:
        std::map<std::string, std::string> mapping;
        MaxPooling2DGenerator(std::string template_path){this->template_path.assign(template_path);}

    std::string write_fwd_function(MaxPooling2D * layer, std::string prev_id);
};

#endif
