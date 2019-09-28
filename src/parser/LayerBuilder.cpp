#include "parser/LayerBuilder.h"
#include <string>

void DropoutBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){
    json object = obj["config"];
    this->layerObject->identifier.assign(id);
    layerMap[this->layerObject->identifier] = this->layerObject;
    std::cout<< "LAYER_BUILDER: Dropout Layer "<< this->layerObject->identifier << " Built!"<<std::endl;
}

void ActivationBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){
    json object = obj["config"];
    this->layerObject->identifier.assign(id);

    layerMap[this->layerObject->identifier] = this->layerObject;
    std::cout<< "LAYER_BUILDER: Activation Layer "<< this->layerObject->identifier << " Built!"<<std::endl;
}


void Conv1DBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){
    json object= obj["config"];
    
    if (object["batch_input_shape"].size() > 0){ // this layer is the input layer
        this->layerObject->input_shape.push_back(object["batch_input_shape"][1]);
        this->layerObject->input_shape.push_back(object["batch_input_shape"][2]);
    } 

    this->layerObject->identifier.assign(id);
    this->layerObject->filters= object["filters"];
    this->layerObject->kernel_size.push_back(object["kernel_size"][0]);
    this->layerObject->strides = object["strides"][0];
    this->layerObject->padding.assign(object["padding"].get<std::string>()); 
    this->layerObject->data_format.assign(object["data_format"].get<std::string>()); 
    this->layerObject->dilation_rate= object["dilation_rate"][0];
    this->layerObject->activation.assign(object["activation"].get<std::string>());
    this->layerObject->use_bias = object["use_bias"];

    layerMap[this->layerObject->identifier] = this->layerObject;

    std::cout<< "LAYER_BUILDER: Conv1D Layer "<< this->layerObject->identifier << " Built!"<<std::endl;
}



void InputBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){
//    json object = obj["config"];
    
   // TODO: Figure out if I actually need this 


}


void Conv2DBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){
    json object= obj["config"];
    int dim_vars= 2;
    this->layerObject->identifier.assign(id);
    
    if (object["batch_input_shape"].size() > 0){
        for (int i=0; i<(dim_vars+1); i++){
        this->layerObject->input_shape.push_back(object["batch_input_shape"][1+i]);
        }
    }  

    for (int i=0; i<dim_vars; i++){
        this->layerObject->kernel_size.push_back(object["kernel_size"][i]);
        this->layerObject->strides.push_back(object["strides"][i]);
        this->layerObject->dilation_rate.push_back(object["dilation_rate"][i]);
    }

    this->layerObject->padding.assign(object["padding"].get<std::string>());
    this->layerObject->data_format.assign(object["data_format"].get<std::string>());
    this->layerObject->activation.assign(object["activation"].get<std::string>());
    this->layerObject->use_bias= object["use_bias"];

    layerMap[this->layerObject->identifier] = this->layerObject;

    std::cout<< "LAYER_BUILDER: Conv2D Layer " << this->layerObject->identifier << " Built!"<<std::endl;
}



void MaxPooling1DBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){

    json object= obj["config"];
    int dim_vars = 2;
    if (object["batch_input_shape"].size() > 0){ // this layer is the input layer
        for (int i=0; i<(dim_vars);i++){
            this->layerObject->input_shape.push_back(object["batch_input_shape"][i+1]);
        }
    }  

    this->layerObject->identifier.assign(id);
    this->layerObject->pool_size= object["pool_size"][0];
    this->layerObject->strides = object["strides"][0];
    this->layerObject->padding.assign(object["padding"].get<std::string>());
    this->layerObject->data_format.assign(object["data_format"].get<std::string>());
 
    layerMap[this->layerObject->identifier] = this->layerObject;

    std::cout<<"LAYER_BUILDER: MaxPooling1D Layer Built!"<<std::endl;
}


void MaxPooling2DBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){
    json object= obj["config"];
    int dim_vars= 2; 
    if (object["batch_input_shape"].size() > 0){
        for (int i=0; i<(dim_vars+1); i++){
            this->layerObject->input_shape.push_back(object["batch_input_shape"][i+1]);
        }
    } 

    this->layerObject->identifier.assign(id);
    for (int i=0; i<dim_vars; i++){
        this->layerObject->pool_size.push_back(object["pool_size"][i]);
        this->layerObject->strides.push_back(object["strides"][i]);
    }
    this->layerObject->padding.assign(object["padding"].get<std::string>());
    this->layerObject->data_format.assign(object["data_format"].get<std::string>());
   
    layerMap[this->layerObject->identifier] = this->layerObject;
    
    std::cout<< "LAYER_BUILDER: MaxPooling2D Layer " << this->layerObject->identifier << " Built!"<<std::endl;
}



void DenseBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){
    json object= obj["config"];
    this->layerObject->identifier.assign(id);
    this->layerObject->units=object["units"];
    this->layerObject->activation.assign(object["activation"].get<std::string>());
    this->layerObject->use_bias = object["use_bias"];

    if (object["batch_input_shape"].size() > 0){ // this layer is the input layer
            this->layerObject->input_shape.push_back(object["batch_input_shape"][1]);
    }  

    this->layerObject->output_shape.push_back(this->layerObject->units);
    
    layerMap[this->layerObject->identifier] = this->layerObject;

    std::cout<< "LAYER_BUILDER: Dense Layer " << this->layerObject->identifier << " Built!"<<std::endl;
}



void FlattenBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){
    this->layerObject->identifier.assign(id);
    layerMap[this->layerObject->identifier] = this->layerObject;
    std::cout<< "LAYER_BUILDER: Flatten Layer " << this->layerObject->identifier << " Built!"<<std::endl;

}


void GRUBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){

}

void LSTMBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){
}


void SimpleRNNBuilder::create_from_json(json obj, std::string id, std::map<std::string, Layer*>& layerMap){
}

