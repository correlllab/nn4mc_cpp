/*
 * Neural Network Generator
 *
 * by Cooper Simpson
 *
 *
 */
#include "generator/neural_network_generator.h"
#include "generator/layer_writer.h"

#include <string>
#include <fstream>

std::string NNGenerator::INIT = "<%BUILD_FUNCTION>";
std::string NNGenerator::FWD  = "<%FWD_FUNCTION>";
std::string NNGenerator::INC = "<%INCLUDE>";
std::string NNGenerator::STRUC = "<%STRUCTS>";


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

void NNGenerator::addLayer_Header(Layer* layer)
{
	size_t pos = header.find(INC);

	std::string file = "#include \"layers/" + layer->layer_type + ".h\"\n";

	header.insert(pos,file);

	pos =  header.find(STRUC,pos);

	std::string init = layer->layer_type + " " + layer->identifier + ";\n";

	header.insert(pos,init);

}

void NNGenerator::addLayer_Init(LayerNode& node) //To be called for each layer from code_generator.
{
	std::map<std::string, std::string>::iterator it;
	it = layer_gen->init_calls.find(node.layer->layer_type); //Access the map from layer_generator.

	std::string init_string;

	if(it != layer_gen->init_calls.end())
		init_string = it->second; //Unedited initialization string.

	//Take init string and give it to LayerWriter to return edited string.
	LayerWriter* writer = LayerWriter::make_writer(node.layer, init_string);

	init_string = writer->write_init();

	//Insert initialization string into the source file.
	size_t start = source.find(INIT);

	source.insert(start-1,init_string);

}
void NNGenerator::addLayer_Fwd(Layer* layer)
{
	std::map<std::string, std::string>::iterator it;
	it = layer_gen->fwd_calls.find(layer->layer_type); //Access the map from layer_generator.

	std::string fwd_string;

	if(it != layer_gen->fwd_calls.end())
		fwd_string = it->second;

	size_t start;
	std::string name = "<%LAYER_NAME>";
	std::string input = "<%INPUT>";
	std::string output = "<%OUTPUT>";

	//fwd_string.insert(1,"input = ");

	start = fwd_string.find(name);
	fwd_string.replace(start,name.length(),layer->identifier);

	start = fwd_string.find(input);
	fwd_string.replace(start,input.length(),"input");

	//fwd_string.find(output)

	start = source.find(FWD);

	source.insert(start-1,fwd_string);
}

void NNGenerator::dumpHeader(std::string output_path)
{
	header.erase(header.find(STRUC), STRUC.length());
	header.erase(header.find(INC), INC.length());

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
	source.erase(source.find(INIT), INIT.length());
	source.erase(source.find(FWD), FWD.length());

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
