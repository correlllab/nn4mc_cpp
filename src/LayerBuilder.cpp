#include "LayerBuilder.h"

void Conv1DBuilder::create_from_json(json obj, std::string id){

    this->layerObject.filters= obj["config"]["filters"];
    this->layerObject.kernel_size = obj["config"]["kernel_size"];
    this->layerObject.strides = obj["config"]["strides"];
    std::cout<<obj["config"]["padding"]<<std::endl;
    /*std::strcpy(this->layerObject.padding, std::string(obj["config"]["padding"]);
    std::strcpy(this->layerObject.data_format, std::string(obj["config"]["data_format"]));
    this->layerObject.dilation_rate= obj["config"]["dilation_rate"];
    std::strcpy(this->layerObject.activation, std::string(obj["config"]["data_format"]));
    this->layerObject.use_bias = obj["config"]["use_bias"];*/
}

void Conv2DBuilder::create_from_json(json obj, std::string id){

}

void MaxPooling1DBuilder::create_from_json(json obj, std::string id){

}

void MaxPooling2DBuilder::create_from_json(json obj, std::string id){

}

void DenseBuilder::create_from_json(json obj, std::string id){
}

void FlattenBuilder::create_from_json(json obj, std::string id){
}

void GRUBuilder::create_from_json(json obj, std::string id){

}

void LSTMBuilder::create_from_json(json obj, std::string id){
}

void SimpleRNNBuilder::create_from_json(json obj, std::string id){
}
