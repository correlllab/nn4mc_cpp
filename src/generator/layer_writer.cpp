/*      LayerWriter.cpp
 *
 * Sarah Aguasvivas Manzano
 *
 */
#include "generator/layer_writer.h"
#include <string>
#include <map>
 
/****************************
*   LAYER WRITER METHODS:
*****************************/

LayerWriter* LayerWriter::make_writer(Layer* layer, std::string init_string)
{

    // TODO: Dynamic instantiation needs factory using this software arch; although this works

  if (Activation* ptr = dynamic_cast<Activation*>(layer))
      return new ActivationGenerator(ptr, init_string);

  if(LSTM* ptr = dynamic_cast<LSTM*>(layer))
      return new LSTMGenerator(ptr, init_string);
  
  if(GRU* ptr = dynamic_cast<GRU*>(layer))
      return new GRUGenerator(ptr, init_string);
  
  if(Conv1D* ptr = dynamic_cast<Conv1D*>(layer))
    return new Conv1DGenerator(ptr, init_string);

  else if(Conv2D* ptr = dynamic_cast<Conv2D*>(layer))
    return new Conv2DGenerator(ptr, init_string);

  else if(Dense* ptr = dynamic_cast<Dense*>(layer))
    return new DenseGenerator(ptr, init_string);
 
  else if(SimpleRNN* ptr = dynamic_cast<SimpleRNN*>(layer))
    return new SimpleRNNGenerator(ptr, init_string);
  
  else if(MaxPooling1D* ptr = dynamic_cast<MaxPooling1D*>(layer))
    return new MaxPooling1DGenerator(ptr, init_string);

  else if(MaxPooling2D* ptr = dynamic_cast<MaxPooling2D*>(layer))
    return new MaxPooling2DGenerator(ptr, init_string);

  else
    return NULL;
}

void LayerWriter::build_padding_lookup(){

    this->padding_lookup["valid"] = "0x00";
    this->padding_lookup["causal"]= "0x02";
    this->padding_lookup["same"] = "0x03";
}

void LayerWriter::build_dataformat_lookup(){

    this->dataformat_lookup["channels_last"] = "0x00";
    this->dataformat_lookup["channels_first"]= "0x02";
}

void LayerWriter::build_activation_lookup(){

    this->activation_lookup["softmax"] = "0x00";
    this->activation_lookup["elu"]= "0x02";
    this->activation_lookup["selu"] = "0x03";
    this->activation_lookup["softplus"] = "0x04";
    this->activation_lookup["softsign"] = "0x05";
    this->activation_lookup["relu"] = "0x06";
    this->activation_lookup["tanh"] = "0x07";
    this->activation_lookup["sigmoid"] = "0x08";
    this->activation_lookup["hard_sigmoid"] = "0x09";
    this->activation_lookup["exponential"] = "0xA";
    this->activation_lookup["linear"] = "0xB";
    this->activation_lookup["custom"] = "0xC";
}


std::string LayerWriter::write_init()
{
  /*
  * This function is to be used by all generators
  * that derive from LayerWriter
  */
  
  build_map("");

  //Take init string and replace delimiters.
	std::string delim;
	size_t start = 0;
	size_t end = 0;

	start = init_template.find_first_of("<%",start);
	end = init_template.find_first_of(">",start);

	//Replace all delimiters in the string.
	while(start != std::string::npos)
	{
		delim = init_template.substr(start,end-start+1);

        int size_delim = delim.length();

        //Do stuff with the delimiter.
		delim = mapping[delim];

		//Replace the delimiter.
		init_template.replace(start,end-start+1,delim);

        end -= abs(size_delim); // added this line because some delimiters were skipped

        //Reset start and end positions.
		start = init_template.find_first_of("<%",end);
		end = init_template.find_first_of(">", start);
	}
    

  return init_template;
}


/****************************
*   BUILD_MAP METHODS:
*****************************/

void ActivationGenerator::build_map(std::string prev_id){
    mapping[INPUT_SIZE] = layer->input_shape[0];
    mapping[OUTPUT_SIZE] = layer->output_shape[0];
    mapping[ACTIVATION] = this->activation_lookup[layer->activation];
    this->build_activation_lookup();    
}


void Conv1DGenerator::build_map(std::string prev_id){

    mapping[LAYER_NAME] = layer->identifier;
    mapping[KERNEL_SIZE] = std::to_string(layer->kernel_size[0]);
    mapping[STRIDE_SIZE] = std::to_string(layer->strides);
    
    mapping[DILATION_RATE] = std::to_string(layer->dilation_rate);
    
    mapping[INPUT_SHAPE_0] = std::to_string(layer->input_shape[0]);
    mapping[INPUT_SHAPE_1] = std::to_string(layer->input_shape[1]); 
    
    mapping[USE_BIAS] = std::to_string(layer->use_bias); 
    
    this->build_activation_lookup();    
    this->build_padding_lookup();
    this->build_dataformat_lookup();

    mapping[ACTIVATION] = this->activation_lookup[layer->activation];
    mapping[PADDING] = this->padding_lookup[layer->padding];
    mapping[DATA_FORMAT] = this->dataformat_lookup[layer->data_format];
    
    mapping[WEIGHT_NAME]= layer->w->identifier;
    mapping[BIAS_NAME]= layer->b->identifier;
    mapping[FILTERS] = std::to_string(layer->filters);
}

void Conv2DGenerator::build_map(std::string prev_id){
    
    mapping[LAYER_NAME] = layer->identifier;
    
    mapping[INPUT_SHAPE_0] = std::to_string(layer->input_shape[0]);
    mapping[INPUT_SHAPE_1] = std::to_string(layer->input_shape[1]);
    mapping[INPUT_SHAPE_2] = std::to_string(layer->input_shape[2]);
    
    mapping[DILATION_RATE_0] = std::to_string(layer->dilation_rate[0]);
    mapping[DILATION_RATE_1] = std::to_string(layer->dilation_rate[1]);

    mapping[WEIGHT_NAME] = layer->w->identifier;
    mapping[BIAS_NAME] = layer->b->identifier;
    mapping[FILTERS] = std::to_string(layer->filters);

    mapping[STRIDE_SHAPE_0] = std::to_string(layer->strides[0]);
    mapping[STRIDE_SHAPE_1] = std::to_string(layer->strides[1]);

    mapping[KERNEL_SHAPE_0] = std::to_string(layer->kernel_size[0]);
    mapping[KERNEL_SHAPE_1] = std::to_string(layer->kernel_size[1]);
    
    this->build_activation_lookup();
    this->build_padding_lookup();
    this->build_dataformat_lookup();
    
    mapping[PADDING] = this->padding_lookup[layer->padding];
    mapping[DATA_FORMAT] = this->dataformat_lookup[layer->data_format];
    mapping[ACTIVATION] = this->activation_lookup[layer->activation]; 
}

void DenseGenerator::build_map(std::string prev_id){
    
    mapping[LAYER_NAME] = layer->identifier;
    mapping[INPUT_SHAPE_0] = std::to_string(layer->input_shape[0]); 
    mapping[USE_BIAS] = std::to_string(layer->use_bias);   
    mapping[OUTPUT_SIZE] = std::to_string(layer->units);
    mapping[WEIGHT_NAME] = layer->w->identifier;
    mapping[BIAS_NAME] = layer->b->identifier;
    this->build_activation_lookup();    
    mapping[ACTIVATION] = this->activation_lookup[layer->activation]; 
}


void SimpleRNNGenerator::build_map(std::string prev_id){
    mapping[LAYER_NAME] = layer->identifier;
    mapping[INPUT_SHAPE_0] = std::to_string(layer->input_shape[0]); 
    mapping[INPUT_SHAPE_1] = std::to_string(layer->input_shape[1]);  
    mapping[OUTPUT_SIZE] = std::to_string(layer->units);
    mapping[WEIGHT_NAME] = layer->w->identifier;
    mapping[RECURRENT_WEIGHT_NAME] = layer->w_rec->identifier;
    mapping[BIAS_NAME] = layer->b->identifier;
    mapping[GO_BACKWARDS] = std::to_string(layer->go_backwards);
    this->build_activation_lookup();    
    mapping[ACTIVATION] = this->activation_lookup[layer->activation]; 
}


void LSTMGenerator::build_map(std::string prev_id){
    mapping[LAYER_NAME] = layer->identifier;
    mapping[OUTPUT_SIZE] = std::to_string(layer->units);
    mapping[WEIGHT_NAME] = layer->w->identifier;
    mapping[RECURRENT_WEIGHT_NAME] = layer->w_rec->identifier;
    mapping[BIAS_NAME] = layer->b->identifier;
    this->build_activation_lookup();    
    mapping[ACTIVATION] = this->activation_lookup[layer->activation]; 
    mapping[RECURRENT_ACTIVATION] = this->activation_lookup[layer->recurrent_activation];
    mapping[DROPOUT] = std::to_string(layer->dropout);
    mapping[RECURRENT_DROPOUT] = std::to_string(layer->recurrent_dropout);
    mapping[IMPLEMENTATION] = std::to_string(layer->implementation);
    mapping[GO_BACKWARDS] = std::to_string(layer->go_backwards);
    mapping[INPUT_SHAPE_0] = std::to_string(layer->input_shape[0]);
    mapping[INPUT_SHAPE_1] = std::to_string(layer->input_shape[1]);
}

void GRUGenerator::build_map(std::string prev_id){
    mapping[LAYER_NAME] = layer->identifier;
    mapping[OUTPUT_SIZE] = std::to_string(layer->units);
    mapping[WEIGHT_NAME] = layer->w->identifier;
    mapping[RECURRENT_WEIGHT_NAME] = layer->w_rec->identifier;
    mapping[BIAS_NAME] = layer->b->identifier;
    this->build_activation_lookup();    
    mapping[ACTIVATION] = this->activation_lookup[layer->activation]; 
    mapping[RECURRENT_ACTIVATION] = this->activation_lookup[layer->recurrent_activation];
    mapping[DROPOUT] = std::to_string(layer->dropout);
    mapping[RECURRENT_DROPOUT] = std::to_string(layer->recurrent_dropout);
    mapping[IMPLEMENTATION] = std::to_string(layer->implementation);
    mapping[GO_BACKWARDS] = std::to_string(layer->go_backwards);
    mapping[INPUT_SHAPE_0] = std::to_string(layer->input_shape[0]);
    mapping[INPUT_SHAPE_1] = std::to_string(layer->input_shape[1]);
}

void MaxPooling1DGenerator::build_map(std::string prev_id){

    mapping[LAYER_NAME] = layer->identifier;
    
    mapping[INPUT_SHAPE_0] = std::to_string(layer->input_shape[0]);
    mapping[INPUT_SHAPE_1] = std::to_string(layer->input_shape[1]);

    mapping[OUTPUT_SHAPE_0] = std::to_string(layer->output_shape[0]);
    mapping[OUTPUT_SHAPE_1] = std::to_string(layer->output_shape[1]);
    mapping[POOL_SIZE] = std::to_string(layer->pool_size);
    mapping[STRIDES] = std::to_string(layer->strides);

}

void MaxPooling2DGenerator::build_map(std::string prev_id){
    
    mapping[LAYER_NAME] = layer->identifier;
    mapping[INPUT_SHAPE_0] =  std::to_string(layer->input_shape[0]);
    mapping[INPUT_SHAPE_1] =  std::to_string(layer->input_shape[1]);
    mapping[INPUT_SHAPE_2] =  std::to_string(layer->input_shape[2]);
    mapping[POOL_SHAPE_0] = std::to_string(layer->pool_size[0]);
    mapping[POOL_SHAPE_1] = std::to_string(layer->pool_size[1]);
    mapping[STRIDE_SHAPE_0] = std::to_string(layer->strides[0]);
    mapping[STRIDE_SHAPE_1] = std::to_string(layer->strides[1]);
    mapping[OUTPUT_SHAPE_0] = std::to_string(layer->output_shape[0]);
    mapping[OUTPUT_SHAPE_1] = std::to_string(layer->output_shape[1]);
    mapping[OUTPUT_SHAPE_2] = std::to_string(layer->output_shape[2]);
}
