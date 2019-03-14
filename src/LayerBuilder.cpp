#include "LayerBuilder.h"

void Conv1DBuilder::create_from_json(json obj, std::string id){
    json object= obj["config"];
    this->layerObject.identifier.assign(id);
    this->layerObject.filters= object["filters"];
    this->layerObject.kernel_size = object["kernel_size"][0];
    this->layerObject.strides = object["strides"][0];
    this->layerObject.padding.assign(object["padding"]); 
    this->layerObject.data_format.assign(object["data_format"]); 
    this->layerObject.dilation_rate= object["dilation_rate"][0];
    this->layerObject.activation.assign(object["activation"]);
    this->layerObject.use_bias = object["use_bias"];
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
