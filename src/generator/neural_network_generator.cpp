/*
 * Neural Network Generator
 *
 * by Cooper Simpson
 *
 *
 */
#include "generator/neural_network_generator.h"

#include <string>
#include <fstream>

std::string NNGenerator::INIT = "<%BUILD_FUNCTION>";
std::string NNGenerator::FWD  = "<%FWD_FUNCTION>";
std::string NNGenerator::INC = "<%INCLUDE>";


NNGenerator::NNGenerator(std::string header_path, std::string src_path, LayerGenerator* lg)
{
	layer_gen = lg;

	header_template_path = header_path;
	source_template_path = src_path;

	loadTemplates();
}
NNGenerator::~NNGenerator()
{

}



void NNGenerator::loadTemplates() //Load the templates for the neural_network header and source.
{
	std::ifstream infile(header_template_path);

	if(infile.is_open())
	{
		//Stored in header string
		header.assign ( (std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()) );

		infile.close();

		std::map<std::string, std::string>::iterator it;
		std::string include;
		for(it = layer_gen->include_files.begin(); it != layer_gen->include_files.end(); it++)
		{
			include += "layers/" + it->first + ".h\n";
		}

		size_t pos = header.find(INC);
		header.replace(pos,INC.length(),include);
	}
	else
		throw std::runtime_error("Could not open file: " + header_template_path);

	infile.open(source_template_path);

	if(infile.is_open())
	{
		//Stored in source string.
		source.assign ( (std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()) );

		infile.close();
	}
	else
		throw std::runtime_error("Could not open file: " + source_template_path);


}



std::string NNGenerator::convertDelimiter(LayerNode& node, std::string delim)
{
	if(delim == "LAYER_NAME")
	{
		return node.layer->identifier;
	}

	else if(delim == "WEIGHT_NAME")
	{
		return node.layer->w->identifier;
	}

	else if(delim == "BIAS_NAME")
	{
		return node.layer->b->identifier;
	}

	else if(delim == "KERNEL_SIZE")
	{
		std::vector<int> kernel = node.layer->kernel_size;

		if(kernel.size() > 1)
		{
			int* data = kernel.data();

			//Assuming the vector is of size 2.
			std::string arr = "int* data = (int*) malloc(2 * sizeof(int));\n";
			arr += "data[0] = " + std::to_string(data[0]) + ";\n";
			arr += "data[1] = " + std::to_string(data[1]) + ";\n";

			std::string del = "free(data);";

			size_t pos = source.find(INIT);

			source.insert(pos-1,arr);
			source.insert(pos+INIT.length(),del);

		}

		else
			return std::to_string(kernel[0]);
	}

	else if(delim == "STRIDE_SIZE")
	{
		//This needs to be fixed as well, need to be able to handle a vector.

		return std::to_string(node.layer->strides);
	}

	else if(delim == "INPUT_CHANNELS")
	{
		return std::to_string(node.inputs.size());
	}

	else if(delim == "OUTPUT_CHANNELS")
	{
		return std::to_string(node.edges.size());
	}

	else if(delim == "INPUT_SIZE")
	{

	}

	else if(delim == "OUTPUT_SIZE")
	{

	}
}

void NNGenerator::addLayer_Header(Layer* layer)
{
	size_t pos =  header.find("<%STRUCTS>");

	std::string init = layer->layer_type + " " + layer->identifier + ";\n";

	header.insert(pos-1,init);

}

void NNGenerator::addLayer_Init(LayerNode& node) //To be called for each layer from code_generator.
{
	std::map<std::string, std::string>::iterator it;
	it = layer_gen->init_calls.find(node.layer->layer_type); //Access the map from layer_generator.

	std::string init_string;

	if(it != layer_gen->init_calls.end())
		init_string = it->second; //Unedited initialization string.

	//Take init string and replace delimiters.
	std::string delim;
	size_t start = 0;
	size_t end = 0;

	start = init_string.find_first_of("<%",start);
	end = init_string.find_first_of(">",start);

	//Replace all delimiters in the string.
	while(start != std::string::npos)
	{
		delim = init_string.substr(start+1,end-start-2);

		//Do stuff with the delimiter.
		delim = convertDelimiter(node, delim);

		//Replace the delimiter.
		init_string.replace(start,end-start,delim);


		//Reset start and end positions.
		start = init_string.find_first_of("<%",end);
		end = init_string.find_first_of(">", start);
	}
	init_string += '\n';

	//Insert initialization string into the source file.
	start = source.find(INIT);

	source.insert(start-1,init_string);

}
void NNGenerator::addLayer_Fwd(Layer* layer)
{

}



void NNGenerator::dumpHeader(std::string output_path)
{
	std::ofstream outfile(output_path);

	if(outfile.is_open())
	{
		outfile << header;

		outfile.close();
	}
	else		// File did not open!
	{
		throw std::runtime_error("Could not open file: " + output_path);
	}
}

void NNGenerator::dumpSource(std::string output_path)
{
	std::ofstream outfile(output_path);

	if(outfile.is_open())
	{
		outfile << source;

		outfile.close();
	}
	else		// File did not open!
	{
		throw std::runtime_error("Could not open file: " + output_path);
	}
}
