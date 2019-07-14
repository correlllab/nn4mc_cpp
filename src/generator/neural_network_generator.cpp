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

void NNGenerator::loadTemplates()
{
	std::ifstream infile(header_template_path);
	
	if(infile.is_open())
	{
		header.assign ( (std::istreambuf_iterator<char>(infile)), (std::istreambuf_iterator<char>()) );

		infile.close();
	}
	else
		throw std::runtime_error("Could not open file: " + header_template_path);
		
	infile.open(source_template_path);
	
	if(infile.is_open())
	{
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
void NNGenerator::addLayer_Init(Layer* layer)
{
	std::map<std::string, std::string>::iterator it;
	it = init_calls.find(layer->layer_type);
	
	if(it != init_calls.end())
		std::string init_string = it->second; //Unedited initialization string.
		
	
	
}
void NNGenerator::addLayer_Fwd(Layer* layer)
{

}
void NNGenerator::dump()
{

}