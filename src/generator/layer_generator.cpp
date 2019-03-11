#include "generator/layer_generator.h"
#include "Layer.h"

#include <fstream>
#include <string>
#include <array>
#include <stdexcept>

// Define the delimiters used
std::string LayerGenerator::WEIGHT_DATATYPE_DELIMITER =	"<%WEIGHT_DATATYPE_DELIMITER>";
std::string LayerGenerator::INDEX_DATATYPE_DELIMITER =	"<%INDEX_DATATYPE_DELIMITER>";

// Define the available layer types
std::array<std::string, 9> LayerGenerator::layer_types = { 	std::string("conv1d"),
															std::string("conv2d"),
															std::string("dense"),
															std::string("flatten"),
															std::string("maxpool1d"),
															std::string("maxpool2d"),
															std::string("simpleRNN"),
															std::string("gru"),
															std::string("lstm")
														 };

/*******************
* LayerGenerator(std::string template_header_directory, template_source_directory)
*
* Create a new object for generating C code for layer representation.  
*
* Arguments:
*   template_header_directory - Path to the files acting as a template for the layer header code.
*   template_source_directory - Path to the files acting as a template for the layer source code.
*/
LayerGenerator::LayerGenerator(std::string template_header_directory, std::string template_source_directory,
							   const char* weight_datatype, const char* index_datatype)
{
	// Where are all the template files located?
	include_template_path = template_header_directory;
	src_template_path = template_source_directory;

	// String to replace in each template file
	weight_datatype_string = weight_datatype;
	index_datatype_string = index_datatype;

}


/*******************
* ~LayerGenerator()
*
* Clean up the object.
*/
LayerGenerator::~LayerGenerator()
{

}


std::string LayerGenerator::processTemplate(std::string template_path)
{
	// The string to put the processed template into
	std::string layer_template;

	// Load the template from the provided path
	std::ifstream template_file(template_path, std::ios::in);

	// If it's open, load the text
	if(template_file.is_open())
	{
		layer_template.assign ( (std::istreambuf_iterator<char>(template_file)), (std::istreambuf_iterator<char>()) );

		template_file.close();
	}
	else		// File did not open!
	{
		throw std::runtime_error("Could not open file: " + template_path);
	}

	// Replace all the instances of the datatype templates
	size_t delimiter_position = layer_template.find(WEIGHT_DATATYPE_DELIMITER);

	while(delimiter_position != std::string::npos)
	{
		layer_template.replace(delimiter_position, WEIGHT_DATATYPE_DELIMITER.length(), weight_datatype_string);
		delimiter_position = layer_template.find(WEIGHT_DATATYPE_DELIMITER);
	}

	delimiter_position = layer_template.find(INDEX_DATATYPE_DELIMITER);

	while(delimiter_position != std::string::npos)
	{
		layer_template.replace(delimiter_position, INDEX_DATATYPE_DELIMITER.length(), weight_datatype_string);
		delimiter_position = layer_template.find(INDEX_DATATYPE_DELIMITER);
	}

	return layer_template;
}


/*******************
* addLayer(Layer layer)
*
* Add the layer to the list of layers to create.
*/
void LayerGenerator::addLayer(Conv1D layer)
{
	// Check if this layer type has been included in the set of template files to process
	std::map<std::string, std::string>::iterator iter = include_files.find("conv1d");
	if(iter == include_files.end())
	{
		std::string file_contents = processTemplate(include_template_path + "/conv1d.h.template");
		include_files.insert( std::pair<std::string, std::string>("conv1d", file_contents));	
	}

	iter = src_files.find("conv1d");
	if(iter == src_files.end())
	{
		std::string file_contents = processTemplate(src_template_path + "/conv1d.cpp.template");
		src_files.insert(std::pair<std::string, std::string>("conv1d", file_contents));
	}
}


void LayerGenerator::addLayer(Conv2D layer)
{ 

}


void LayerGenerator::addLayer(Dense layer)
{

}


void LayerGenerator::addLayer(Flatten layer)
{

}


void LayerGenerator::addLayer(MaxPooling1D layer)
{

}


void LayerGenerator::addLayer(MaxPooling2D layer)
{

}


void LayerGenerator::addLayer(SimpleRNN layer)
{

}


void LayerGenerator::addLayer(GRU layer)
{

}


void LayerGenerator::addLayer(LSTM layer)
{

}

void LayerGenerator::dump(std::string directory, std::map<std::string,std::string> file_map)
{
	// Loop through the include files and dump into the provided directory with appropriate paths
	for(std::map<std::string, std::string>::iterator iter = file_map.begin(); iter != file_map.end(); iter++)
	{
		std::string path = directory + "/" + iter->first + ".h";

		// Load the template from the provided path
		std::ofstream output_file(path, std::ios::out);

		if(output_file.is_open())
		{
			output_file << iter->second;
			output_file.close();
		}
		else		// File did not open!
		{
			throw std::runtime_error("Could not open file: " + path);
		}
	}
}

/*******************
* dumpLayerHeaders(std::string layer_header_directory)
*
* Write the actual C code for the layer headers to the specified directory.
*
* Arguments:
*   layer_header_directory - path to the directory to write layer headers to
*/
void LayerGenerator::dumpLayerHeaders(std::string layer_header_directory)
{
	dump(layer_header_directory, include_files);
}


/*******************
* dumpLayerSources(std::string layer_source_directory)
*
* Write the actual C code for the layer source directory to the specified directory.
*
* Arguments:
*   layer_source_directory - path to the directory to write layer source code to
*/
void LayerGenerator::dumpLayerSources(std::string layer_src_directory)
{
	dump(layer_src_directory, src_files);
}