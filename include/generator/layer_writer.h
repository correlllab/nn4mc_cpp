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
        static LayerWriter* make_writer(Layer*, std::string);
        virtual std::string write_init()=0;
        virtual void build_map(std::string)=0;
        virtual ~LayerWriter() = default;
};

class Conv1DGenerator : public LayerWriter{
    public:
        // mapping maps from delimiter to string value of the delimiter
        // e.g. <%INPUT_SHAPE_0> --> str(layer.input_sh1);
        std::map<std::string, std::string> mapping;

        std::string INPUT_CHANNELS= "<%INPUT_CHANNELS>";
        std::string OUTPUT_CHANNELS= "<%OUTPUT_CHANNELS>";

        std::string STRIDE_SIZE = "<%STRIDE_SIZE>";
        std::string KERNEL_SIZE = "<%KERNEL_SIZE>";
        std::string INPUT_SIZE = "<%INPUT_SIZE>";

        std::string WEIGHT_NAME = "<%WEIGHT_NAME>";
        std::string BIAS_NAME = "<%BIAS_NAME>";

        Conv1D* layer;
        Conv1DGenerator(Conv1D* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);
    std::string write_init();
};

class Conv2DGenerator : public LayerWriter{
    public:

        Conv2D* layer;
        Conv2DGenerator(Conv2D* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);
    std::string write_init();

};

class DenseGenerator : public LayerWriter{
    public:
        std::map<std::string, std::string> mapping;
        
        std::string INPUT_SIZE= "<%INPUT_SIZE>";
        std::string OUTPUT_SIZE= "<%OUTPUT_SIZE>";

        std::string WEIGHT_NAME = "<%WEIGHT_NAME>";
        std::string BIAS_NAME = "<%BIAS_NAME>";

        Dense* layer;
        DenseGenerator(Dense* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);
    std::string write_init();

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

        Flatten* layer;
        FlattenGenerator(Flatten* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);
    std::string write_init();

};

class MaxPooling1DGenerator : public LayerWriter{
    public:
        std::map<std::string, std::string> mapping;

        MaxPooling1D* layer;
        MaxPooling1DGenerator(MaxPooling1D* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);
    std::string write_init();
};

class MaxPooling2DGenerator : public LayerWriter{
    public:
        std::map<std::string, std::string> mapping;

        MaxPooling2D* layer;
        MaxPooling2DGenerator(MaxPooling2D* layer, std::string init){this->layer = layer; this->init_template.assign(init);}

    void build_map(std::string);
    std::string write_init();
};

#endif
