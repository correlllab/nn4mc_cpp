/*      LayerWriter.cpp
 *
 * Sarah Aguasvivas Manzano
 *
 */

#include "generator/layer_writer.h"
#include <string>
#include <map>

LayerWriter* LayerWriter::make_writer(Layer* layer, std::string init_string)
{
  if(Conv1D* ptr = dynamic_cast<Conv1D*>(layer))
    return new Conv1DGenerator(ptr, init_string);

  else if(Conv2D* ptr = dynamic_cast<Conv2D*>(layer))
    return new Conv2DGenerator(ptr, init_string);

  else if(Dense* ptr = dynamic_cast<Dense*>(layer))
    return new DenseGenerator(ptr, init_string);

  else if(Flatten* ptr = dynamic_cast<Flatten*>(layer))
    return new FlattenGenerator(ptr, init_string);

  else if(MaxPooling1D* ptr = dynamic_cast<MaxPooling1D*>(layer))
    return new MaxPooling1DGenerator(ptr, init_string);

  else if(MaxPooling2D* ptr = dynamic_cast<MaxPooling2D*>(layer))
    return new MaxPooling2DGenerator(ptr, init_string);

  else
    return NULL;
}

void Conv1DGenerator::build_map(std::string prev_id){
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
std::string Conv1DGenerator::write_init()
{

}

void Conv2DGenerator::build_map(std::string prev_id){

}
std::string Conv2DGenerator::write_init()
{

}

void DenseGenerator::build_map(std::string prev_id){

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
std::string DenseGenerator::write_init()
{

}

void FlattenGenerator::build_map(std::string prev_id){
   mapping[LAYER_ID] = layer->identifier;
   //mapping[INPUT_SIZE_0] =
   //mapping[INPUT_SIZE_1] =
   mapping[PREVIOUS_LAYER_ID] = prev_id;
}
std::string FlattenGenerator::write_init()
{

}

void MaxPooling1DGenerator::build_map(std::string prev_id){


}
std::string MaxPooling1DGenerator::write_init()
{

}

void MaxPooling2DGenerator::build_map(std::string prev_id){


}
std::string MaxPooling2DGenerator::write_init()
{

}
