#include "generator/code_generator.h"
#include "generator/file_creator.h"
#include <iostream>

std::string CodeGenerator::LAYER_TEMPLATE_INCLUDE_DIR = "include/layers";
std::string CodeGenerator::LAYER_TEMPLATE_SRC_DIR = "src/layers";
std::string CodeGenerator::PARAMETER_TEMPLATE_PATH = "include";
std::string CodeGenerator::SOURCE_TEMPLATE_PATH = "src";
std::string CodeGenerator::PARAMETER_FILENAME = "neural_network_params.h";
std::string CodeGenerator::HEADER_FILENAME = "neural_network.h";
std::string CodeGenerator::SOURCE_FILENAME = "neural_network.c";
std::string CodeGenerator::PARAMETER_DATATYPE = "const float";
std::string CodeGenerator::LAYER_OUTPUT_DATATYPE = "float";
std::string CodeGenerator::INDEX_DATATYPE = "int";

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
	std::string layer_include_template_path = template_folder + "/" + LAYER_TEMPLATE_INCLUDE_DIR;
	std::string layer_src_template_path = template_folder + "/" + LAYER_TEMPLATE_SRC_DIR;

	// Create the Layer and Weight builders
	weight_generator = new WeightGenerator(network_param_template_path, true);
	layer_generator = new LayerGenerator(layer_include_template_path, layer_src_template_path, PARAMETER_DATATYPE, INDEX_DATATYPE);
	nn_generator = new NNGenerator(neural_network_header, neural_network_source, layer_generator); //Finish this

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
	// Pull all weights from the neural network and add it to the weight code generator
	// for (weight in neural_net)

	for(it=neural_net->begin(); it != neural_net->end(); it++)
	{
    if(it->layer->layer_type != "InputLayer")
		{
			weight_generator->addWeight(it->layer->w);
			weight_generator->addWeight(it->layer->b); //Something here
		}
	}

	neural_net->reset();

	// Pull all the layers from the neural network and add it to the layer code generator
	// for (layer in neural_net)
	for(it=neural_net->begin(); it != neural_net->end(); it++)
	{
		if(it->layer->layer_type != "InputLayer")
		{
			layer_generator->addLayer(it->layer);
		}
	}

	neural_net->reset();

	// Pull the layer evaluation order from the neural network, and generate the neural net code

	for(it=neural_net->begin(); it!=neural_net->end(); it++)
	{
		if(it->layer->layer_type != "InputLayer")
		{
			//For each layer call addLayer from NNGenerator for header, init, and forward.
			nn_generator->addLayer_Header(it->layer); //it->layer may need to be different
			nn_generator->addLayer_Init(*it); //may need to pass whole layernode.
			nn_generator->addLayer_Fwd(it->layer);
		}
	}
	neural_net->reset();

}

void CodeGenerator::dump()
{
	// Write all of the code to the output directory
	weight_generator->dump(output_folder + "/" + PARAMETER_TEMPLATE_PATH + "/" + PARAMETER_FILENAME);
	// Write all of the layer header and source
	layer_generator->dumpLayerHeaders(output_folder + "/" + LAYER_TEMPLATE_INCLUDE_DIR);
	std::cout << "Here" << std::endl;
	layer_generator->dumpLayerSources(output_folder + "/" + LAYER_TEMPLATE_SRC_DIR);
	//Write out header file and source file for neural_network
	std::cout << "Here" << std::endl;
	nn_generator->dumpHeader(output_folder + "/" + PARAMETER_TEMPLATE_PATH + "/" +
HEADER_FILENAME);
	nn_generator->dumpSource(output_folder + "/" + SOURCE_TEMPLATE_PATH + "/" +
SOURCE_FILENAME);

}
