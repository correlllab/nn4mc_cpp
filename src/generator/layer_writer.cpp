/*      LayerWriter.cpp
 *
 * Sarah Aguasvivas Manzano
 *
 */

#include "generator/layer_writer.h"
#include <string>
#include <map>

std::string Conv1DGenerator::write_fwd_function(Conv1D * layer, std::string prev_id){
    // takes in pointer to the layer and previous layer id
    // if previous layer is none then call prev_id is window
    mapping[PREVIOUS_LAYER_ID] = prev_id;
    mapping[LAYER_ID] = layer->identifier;
    mapping[KERNEL_SIZE]= std::to_string((int)layer->kernel_size[0]);
    mapping[FILTERS]= std::to_string((int)layer->filters);
    mapping[WEIGHT_VAR]= layer->identifier.append("_W"); //e.g. conv1d_1_b
    mapping[BIAS_VAR]= layer->identifier.append("_b"); //e.g. conv1d_1_b
    mapping[WEIGHT_SHAPE0]= std::to_string((int)layer->filters);
    //mapping[WEIGHT_SHAPE1]= second dimension of input dim
    mapping[WEIGHT_SHAPE2] = std::to_string((int)layer->kernel_size[0]);
    //mapping[INPUT_SHAPE_0]=
    //mapping[INPUT_SHAPE_1]=
}

std::string Conv2DGenerator::write_fwd_function(Conv2D * layer, std::string prev_id){

}

std::string DenseGenerator::write_fwd_function(Dense * layer, std::string prev_id){

    mapping[LAYER_ID]= layer->identifier;
    mapping[PREVIOUS_LAYER_ID] = prev_id;
    //mapping[INPUT_SIZE] = 
    mapping[OUTPUT_SIZE] = layer->units;
    //mapping[WEIGHT_SHAPE0]= 
    mapping[WEIGHT_SHAPE1] = layer->units;
    mapping[ACTIVATION] = layer->activation;
    mapping[WEIGHT_VAR] = layer->identifier.append("_W");
    mapping[BIAS_VAR] = layer->identifier.append("_b");
}

std::string FlattenGenerator::write_fwd_function(Flatten * layer, std::string prev_id){
   mapping[LAYER_ID] = layer->identifier;
   //mapping[INPUT_SIZE_0] = 
   //mapping[INPUT_SIZE_1] = 
   mapping[PREVIOUS_LAYER_ID] = prev_id;
}

std::string MaxPooling1DGenerator::write_fwd_function(MaxPooling1D * layer, std::string prev_id){


}

std::string MaxPooling2DGenerator::write_fwd_function(MaxPooling2D * layer, std::string prev_id){


}
