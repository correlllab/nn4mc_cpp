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

void Conv1DGenerator::build_map(std::string prev_id){

    mapping[LAYER_NAME] = layer->identifier;

    mapping[KERNEL_SIZE] = std::to_string(layer->kernel_size[0]);
    mapping[STRIDE_SIZE] = std::to_string(layer->strides);

    mapping[INPUT_SHAPE_0] = "1"; //Fake
    mapping[INPUT_SHAPE_1] = "2"; //Fake

    mapping[ACTIVATION] = "l"; // TODO: Need to make activation lookup

    mapping[WEIGHT_NAME]= layer->w->identifier;
    mapping[BIAS_NAME]= layer->b->identifier;
    mapping[FILTERS] = std::to_string(layer->filters);
}

void Conv2DGenerator::build_map(std::string prev_id){

}

void DenseGenerator::build_map(std::string prev_id){

    mapping[LAYER_NAME] = layer->identifier;

    mapping[INPUT_SHAPE_0] = "1"; //Fake
    
    mapping[OUTPUT_SIZE] = std::to_string(layer->units);
    mapping[WEIGHT_NAME] = layer->w->identifier;
    mapping[BIAS_NAME] = layer->b->identifier;
    mapping[ACTIVATION] = "l"; // Fake // TODO: Need to make activation lookup
}

void FlattenGenerator::build_map(std::string prev_id){
   mapping[LAYER_ID] = layer->identifier;
   mapping[PREVIOUS_LAYER_ID] = prev_id;
}

void MaxPooling1DGenerator::build_map(std::string prev_id){


}

void MaxPooling2DGenerator::build_map(std::string prev_id){


}
