#include "generator/code_generator.h"
#include "generator/file_creator.h"
#include <iostream>

std::string CodeGenerator::LAYER_TEMPLATE_INCLUDE_DIR = "include/layers";
std::string CodeGenerator::LAYER_TEMPLATE_SRC_DIR = "src/layers";
std::string CodeGenerator::PARAMETER_TEMPLATE_PATH = "include";
std::string CodeGenerator::SOURCE_TEMPLATE_PATH = "src";
std::string CodeGenerator::PARAMETER_FILENAME = "parameters.h";
std::string CodeGenerator::HEADER_FILENAME = "nn4mc.h";
std::string CodeGenerator::SOURCE_FILENAME = "nn4mc.cpp";
std::string CodeGenerator::ACTIVATION_HEADER_FILENAME = "activations.h";
std::string CodeGenerator::ACTIVATION_SOURCE_FILENAME = "activations.cpp";
std::string CodeGenerator::PARAMETER_DATATYPE = "const float";
std::string CodeGenerator::LAYER_OUTPUT_DATATYPE = "float";
std::string CodeGenerator::INDEX_DATATYPE = "int";
std::string CodeGenerator::ACTIVATION_DATATYPE = "char";

/*******************
* LayerGenerator(std::string template_header_directory, template_source_directory)
*
* Create a new object for generating C code for layer representation.
*
* Arguments:
*   template_header_directory - Path to the files acting as a template for the layer header code.
*   template_source_directory - Path to the files acting as a template for the layer source code.
*/
CodeGenerator::CodeGenerator(NeuralNetwork* neural_network, std::string template_directory, std::string output_directory)
{
	// Store the template and output folders, and the neural network to process
	template_folder = template_directory;
	output_folder = output_directory;

    // Creating folder tree necessary for nn4mc:
    FileCreator file_creator(output_directory);
    file_creator.create_codegen_file_tree();

	// Store the neural network
	neural_net = neural_network;

	// Construct the paths for needed files
	std::string network_param_template_path = template_folder + "/" + PARAMETER_TEMPLATE_PATH + "/" + PARAMETER_FILENAME + ".template";

	std::string neural_network_header = template_folder + "/" + PARAMETER_TEMPLATE_PATH + "/" +
HEADER_FILENAME + ".template";
	std::string neural_network_source = template_folder + "/" + SOURCE_TEMPLATE_PATH + "/" +
SOURCE_FILENAME + ".template";
	std::string activation_header = template_folder + "/" + PARAMETER_TEMPLATE_PATH + "/" +
ACTIVATION_HEADER_FILENAME + ".template";
	std::string activation_source = template_folder + "/" + SOURCE_TEMPLATE_PATH + "/" +
ACTIVATION_SOURCE_FILENAME + ".template";

	std::string layer_include_template_path = template_folder + "/" + LAYER_TEMPLATE_INCLUDE_DIR;
	std::string layer_src_template_path = template_folder + "/" + LAYER_TEMPLATE_SRC_DIR;

	// Create the Layer and Weight builders
	weight_generator = new WeightGenerator(network_param_template_path, true);
	layer_generator = new LayerGenerator(layer_include_template_path, layer_src_template_path, PARAMETER_DATATYPE, INDEX_DATATYPE, ACTIVATION_DATATYPE, LAYER_OUTPUT_DATATYPE);
	nn_generator = new NNGenerator(neural_network_header, neural_network_source, activation_header, activation_source, layer_generator); //Finish this
}

CodeGenerator::~CodeGenerator()
{
	delete weight_generator;
	delete layer_generator;
	delete nn_generator;
}

void CodeGenerator::generate()
{
	NeuralNetwork::iterator it;

    for(it=neural_net->begin(); it != neural_net->end(); it++)
	{
        if(it->layer->layer_type != "input" && it->layer->layer_type != "flatten" && it->layer->layer_type !="activation" && it->layer->layer_type != "maxpool1d" && it->layer->layer_type != "maxpool2d" && it->layer->layer_type != "dropout")
            {
                weight_generator->addWeight(it->layer->w);
                weight_generator->addWeight(it->layer->b);
                if (it->layer->w_rec != NULL){
                    weight_generator->addWeight(it->layer->w_rec);
                }
            }
	}

	neural_net->reset();


	for(it=neural_net->begin(); it != neural_net->end(); it++)
	{
		if(it->layer->layer_type != "input" && it->layer->layer_type != "flatten" && it->layer->layer_type != "dropout")
		{
			layer_generator->addLayer(it->layer);
		}
	}
    
	
    neural_net->reset();

	for(it=neural_net->begin(); it!=neural_net->end(); it++)
	{
		if(it->layer->layer_type != "input" && it->layer->layer_type != "flatten" && it->layer->layer_type != "dropout")
		{
			nn_generator->addLayer_Header(it->layer);
			nn_generator->addLayer_Init(*it);
			nn_generator->addLayer_Fwd(it->layer);
		}
	}
	neural_net->reset();
    

	nn_generator->addActivation(); //NOTE: Should change this to only add neccessary functions
}

void CodeGenerator::dump()
{
	// Write all of the code to the output directory
	weight_generator->dump(output_folder + "/" +  PARAMETER_FILENAME);

    // Write all of the layer header and source
	layer_generator->dumpLayerHeaders(output_folder );
	layer_generator->dumpLayerSources(output_folder );

    //Write out header file and source file for neural_network
	nn_generator->dumpHeader(output_folder + "/" + HEADER_FILENAME);
	nn_generator->dumpSource(output_folder + "/" + SOURCE_FILENAME);
	nn_generator->dumpActivation(output_folder + "/" + ACTIVATION_HEADER_FILENAME, output_folder + "/" + ACTIVATION_SOURCE_FILENAME);

}
