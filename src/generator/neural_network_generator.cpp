#include "generator/neural_network_generator.h"
#include "datastructures/Layer.h"

#include <string>
#include <fstream>

#define INIT "<%BUILD_FUNCTION>";
#define FWD "<%FWD_FUNCTION>";
#define INC "<%INCLUDE>"


NNGenerator::NNGenerator(std::string header_path, std::string src_path)
{
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
		for(it = map.begin(); i != map.end(); i++)
		{
			include += '"layers/' + it->first + '.h"\n';
		}

		size_t pos = header.find(INC);
		header.replace(pos,INC.len(),include);
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
		throw std::runtime_error("Could not open file: " + src_template_path);

	return;

}



std::string NNGenerator::convertDelimiter(LayerNode* node, std::string delim)
{
	if(delim == "LAYER_NAME")
	{
		return node->layer->identifier;
	}

	else if(delim == "WEIGHT_NAME")
	{
		return node->layer->w->identifier;
	}

	else if(delim == "BIAS_NAME")
	{
		return node->layer->b->identifier;
	}

	else if(delim == "KERNEL_SIZE")
	{
		std::vector<int> kernel = node->layer->kernel_size;

		if(kernel.size() > 1)
		{
			int* data = kernel.data();

			//Assuming the vector is of size 2.
			std::string arr = "int* data = (int*) malloc(2 * sizeof(int));\n";
			arr += "data[0] = " + to_string(data[0]) + ";\n";
			arr += "data[1] = " + to_string(data[1]) + ";\n";

			std::string del = "free(data);";

			size_t pos = source.find(INIT);

			source.insert(pos-1,arr);
			source.insert(pos+INIT.len(),del);

			return;
		}

		else
			return to_string(kernel[0]);
	}

	else if(delim == "STRIDE_SIZE")
	{
		//This needs to be fixed as well, need to be able to handle a vector.

		return std::to_string(node->layer->strides);
	}

	else if(delim == "INPUT_CHANNELS")
	{
		return node->inputs.size();
	}

	else if(delim == "OUTPUT_CHANNELS")
	{
		return node->edges.size();
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

	string init = layer.layer_type + " " + layer.identifier + ";\n";

	header.insert(pos-1,init);

	return
}

void NNGenerator::addLayer_Init(LayerNode* node) //To be called for each layer from code_generator.
{
	std::map<std::string, std::string>::iterator it;
	it = init_calls.find(node->layer->layer_type); //Access the map from layer_generator.

	if(it != init_calls.end())
		std::string init_string = it->second; //Unedited initialization string.

	//Take init string and replace delimiters.
	string delim;
	int start = 0;
	int end = 0;

	size_t start = init_string.find_first_of("<%",start);
	size_t end = init_string.find_first_of(">",start);

	//Replace all delimiters in the string.
	while(size_t != string::npos)
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

	return

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
