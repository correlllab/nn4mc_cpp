#include "generator/neural_network_generator.h"
#include "datastructures/Layer.h"

#include <string>
#include <fstream>



std::string LayerGenerator::INIT = <%BUILD_FUNCTION>;
std::string LayerGenerator::FWD = <%FWD_FUNCTION>;


NNGenerator::NNGenerator(std::string header_path, std::string src_path)
{
	header_template_path = header_path;
	source_template_path = src_path;
	
	delimiters.insert(std::pair<std::string,std::string>("<%LAYER_NAME","identifier"));
	delimiters.insert(std::pair<std::string,std::string>("<%WEIGHT_NAME>","w->identifier"));
	delimiters.insert(std::pair<std::string,std::string>("<%BIAS_NAME>","b->identifier"));
	delimiters.insert(std::pair<std::string,std::string>("<%KERNEL_SIZE>",""));
	delimiters.insert(std::pair<std::string,std::string>("<%STRIDE_SIZE>","strides"));
	delimiters.insert(std::pair<std::string,std::string>("<%INPUT_CHANNELS>",""));
	delimiters.insert(std::pair<std::string,std::string>("<%OUTPUT_CHANNELS>",""));
	delimiters.insert(std::pair<std::string,std::string>("<%INPUT_SIZE>",""));
	delimiters.insert(std::pair<std::string,std::string>("<%OUTPUT_SIZE>",""));
	
	loadTemplates();
}
NNGenerator::~NNGenerator()
{

}

/**
void addMaps(std::map<std::string, std::string> init, std::map<std::string, std::string> fwd)
{
	init_calls = init;
	fwd_calls = fwd;
	
	return;
}
**/

void NNGenerator::loadTemplates() //Load the templates for the neural_network header and source.
{
	std::ifstream infile(header_template_path);
	
	if(infile.is_open())
	{
		//Stored in header string
		header.assign ( (std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()) );

		infile.close();
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
void NNGenerator::addLayer_Header(Layer* layer)
{

}
void NNGenerator::addLayer_Init(Layer* layer) //To be called for each layer from code_generator.
{
	std::map<std::string, std::string>::iterator it; 
	it = init_calls.find(layer->layer_type); //Access the map from layer_generator.
	
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
void NNGenerator::dump()
{

}