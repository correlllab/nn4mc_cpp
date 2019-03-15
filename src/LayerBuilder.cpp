#include "LayerBuilder.h"
#include <string>
void Conv1DBuilder::create_from_json(json obj, std::string id){
    json object= obj["config"];
    this->layerObject.identifier.assign(id);
    this->layerObject.filters= object["filters"];
    this->layerObject.kernel_size.push_back(object["kernel_size"][0]);
    this->layerObject.strides = object["strides"][0];
    this->layerObject.padding.assign(object["padding"].get<std::string>()); 
    this->layerObject.data_format.assign(object["data_format"].get<std::string>()); 
    this->layerObject.dilation_rate= object["dilation_rate"][0];
    this->layerObject.activation.assign(object["activation"].get<std::string>());
    this->layerObject.use_bias = object["use_bias"];
    std::cout<< "Conv1D Layer "<< this->layerObject.identifier << " Built!"<<std::endl;
}

void Conv2DBuilder::create_from_json(json obj, std::string id){
    json object= obj["config"];
    int dim_vars= 2;
    this->layerObject.identifier.assign(id);
    for (int i=0; i<dim_vars; i++){
        this->layerObject.kernel_size.push_back(object["kernel_size"][i]);
        this->layerObject.strides.push_back(object["strides"][i]);
        this->layerObject.dilation_rate.push_back(object["dilation_rate"][i]);
    }

    this->layerObject.padding.assign(object["padding"].get<std::string>());
    this->layerObject.data_format.assign(object["data_format"].get<std::string>());
    this->layerObject.activation.assign(object["activation"].get<std::string>());
    this->layerObject.use_bias= object["use_bias"];
    std::cout<< "Conv2D Layer " << this->layerObject.identifier << " Built!"<<std::endl;
}

void MaxPooling1DBuilder::create_from_json(json obj, std::string id){

    json object= obj["config"];
    this->layerObject.identifier.assign(id);
    this->layerObject.pool_size= object["pool_size"][0];
    this->layerObject.strides = object["strides"][0];
    this->layerObject.padding.assign(object["padding"].get<std::string>());
    this->layerObject.data_format.assign(object["data_format"].get<std::string>());
    std::cout<<"MaxPooling1D Layer Built!"<<std::endl;

}

void MaxPooling2DBuilder::create_from_json(json obj, std::string id){
    json object= obj["config"];
    int dim_vars= 2;
    this->layerObject.identifier.assign(id);
    for (int i=0; i<dim_vars; i++){
        this->layerObject.pool_size.push_back(object["pool_size"][i]);
        this->layerObject.strides.push_back(object["strides"][i]);
    }
    this->layerObject.padding.assign(object["padding"].get<std::string>());
    this->layerObject.data_format.assign(object["data_format"].get<std::string>());
    std::cout<< "MaxPooling2D Layer " << this->layerObject.identifier << " Built!"<<std::endl;
}

void DenseBuilder::create_from_json(json obj, std::string id){
    json object= obj["config"];
    this->layerObject.identifier.assign(id);
    this->layerObject.units=object["units"];
    this->layerObject.activation.assign(object["activation"].get<std::string>());
    this->layerObject.use_bias = object["use_bias"];
    std::cout<< "Dense Layer " << this->layerObject.identifier << " Built!"<<std::endl;
}

void FlattenBuilder::create_from_json(json obj, std::string id){
    this->layerObject.identifier.assign(id);
    std::cout<< "Flatten Layer " << this->layerObject.identifier << " Built!"<<std::endl;

}

void GRUBuilder::create_from_json(json obj, std::string id){

}

void LSTMBuilder::create_from_json(json obj, std::string id){
}

void SimpleRNNBuilder::create_from_json(json obj, std::string id){
}
