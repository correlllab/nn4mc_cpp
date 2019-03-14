#include "LayerBuilder.h"

void Conv1DBuilder::create_from_json(json obj, std::string id){
    json object= obj["config"];
    this->layerObject.identifier.assign(id);
    this->layerObject.filters= object["filters"];
    this->layerObject.kernel_size.push_back(object["kernel_size"][0]);
    this->layerObject.strides = object["strides"][0];
    this->layerObject.padding.assign(object["padding"]); 
    this->layerObject.data_format.assign(object["data_format"]); 
    this->layerObject.dilation_rate= object["dilation_rate"][0];
    this->layerObject.activation.assign(object["activation"]);
    this->layerObject.use_bias = object["use_bias"];
}

void Conv2DBuilder::create_from_json(json obj, std::string id){
    json object= obj["config"];
    int dim_vars= 2;
    this->layerObject.identifier.assign(id);
    for (int i=0; i<dim_vars; i++){
        this->layerObject.kernel_size.push_back(object["kernel_size"][i]);
        this->layerObject.strides.push_back(object["strides"][i]);
        this->dilation_rate.push_back(object["dilation_rate"][i]);
    }

    this->layerObject.padding.assign(object["padding"]);
    this->layerObject.data_format.assign(object["data_format"]);
    this->layerObject.activation.assign(object["activation"]);
    this->use_bias= object["use_bias"];
}

void MaxPooling1DBuilder::create_from_json(json obj, std::string id){

    json object= obj["config"];
    this->layerObject.identifier.assign(id);
    this->layerObject.pool_size= object["pool_size"][0];
    this->layerObject.strides = object["strides"][0];
    this->layerObject.padding.assign(object["padding"]);
    this->layerObject.data_format.assign(object["data_format"])

}

void MaxPooling2DBuilder::create_from_json(json obj, std::string id){
    json object= obj["config"];
    int dim_vars= 2;
    this->layerObject.identifier.assign(id);
    for (int i=0; i<dim_vars; i++){
        this->layerObject.pool_size.push_back(object["pool_size"][i]);
        this->layerObject.strides.push_back(object["strides"][i]);
    }
    this->layerObject.padding.assign(object["padding"]);
    this->layerObject.data_format.assign(object["data_format"]);
}

void DenseBuilder::create_from_json(json obj, std::string id){
    json object= obj["config"];
    
    this->layerObject.identifier.assign(id);
    this->layerObject.units=object["units"];
    this->layerObject.activation.assign(object["activation"]);
    this->layerObject.use_bias = object["use_bias"];

}

void FlattenBuilder::create_from_json(json obj, std::string id){
    this->layerObject.identifier.assign(id);
}

void GRUBuilder::create_from_json(json obj, std::string id){

}

void LSTMBuilder::create_from_json(json obj, std::string id){
}

void SimpleRNNBuilder::create_from_json(json obj, std::string id){
}
