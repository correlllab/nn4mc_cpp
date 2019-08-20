#include "generator/layer_generator.h"
#include "datastructures/Layer.h"
#include <fstream>
#include <string>
#include <array>
#include <stdexcept>
#include <sys/stat.h>

// Define the delimiters used
std::string LayerGenerator::WEIGHT_DATATYPE_DELIMITER =	"<%WEIGHT_DATATYPE_DELIMITER>";
std::string LayerGenerator::INDEX_DATATYPE_DELIMITER =	"<%INDEX_DATATYPE_DELIMITER>";
std::string LayerGenerator::LAYER_DATATYPE_DELIMITER = "<%LAYER_DATATYPE_DELIMITER>";
std::string LayerGenerator::START_DELIMITER = "<%BEGIN_DEFINITION_TEMPLATE>";
std::string LayerGenerator::END_DELIMITER = "<%END_DEFINITION_TEMPLATE>";
std::string LayerGenerator::START_CALL_DELIMITER = "<%BEGIN_CALL_TEMPLATE>";
std::string LayerGenerator::END_CALL_DELIMITER = "<%END_CALL_TEMPLATE>";
std::string LayerGenerator::START_INITIALIZE_DELIMITER = "<%BEGIN_INITIALIZE_TEMPLATE>";
std::string LayerGenerator::END_INITIALIZE_DELIMITER = "<%END_INITIALIZE_TEMPLATE>";



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
							   std::string weight_datatype, std::string index_datatype)
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


/*******************
* loadTemplate(std::string template_path)
*
* Load the template file from the provided path.
*/
std::string LayerGenerator::loadTemplate(std::string template_path)
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

	return layer_template;
}



/*******************
* processTemplate(std::string template, std::string layer_datatype)
*
* Pull out and process the template
*/
std::string LayerGenerator::processTemplate(std::string layer_template, std::string layer_datatype)
{
	// Extract the template from where the definition begins and ends
	size_t start_position = layer_template.find(START_DELIMITER);
	size_t end_position = layer_template.find(END_DELIMITER);

	// TODO: Do the delimiters actually exist?

	start_position += START_DELIMITER.length();

	layer_template = layer_template.substr(start_position, end_position-start_position);

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
		layer_template.replace(delimiter_position, INDEX_DATATYPE_DELIMITER.length(), index_datatype_string);
		delimiter_position = layer_template.find(INDEX_DATATYPE_DELIMITER);
	}

	delimiter_position = layer_template.find(LAYER_DATATYPE_DELIMITER);

	while(delimiter_position != std::string::npos)
	{
		layer_template.replace(delimiter_position, LAYER_DATATYPE_DELIMITER.length(), layer_datatype);
		delimiter_position = layer_template.find(LAYER_DATATYPE_DELIMITER);
	}


	return layer_template;
}



/*******************
* getFunctionString(std::string layer_template, std::string start_delimiter, std::string end_delimiter)
*
*
*/
std::string LayerGenerator::getFunctionString(std::string layer_template, std::string start_delimiter, std::string end_delimiter)
{
	// Extract the template from where the call begins and ends
	size_t start_position = layer_template.find(start_delimiter);
	size_t end_position = layer_template.find(end_delimiter);

	// TODO : Do the delimiters actually exist?

	start_position += start_delimiter.length();

	layer_template = layer_template.substr(start_position, end_position-start_position);

	return layer_template;
}


/*******************
* getInitString(std::string layer_template)
*
*
*/
std::string LayerGenerator::getInitString(std::string layer_template)
{
	return getFunctionString(layer_template, START_INITIALIZE_DELIMITER, END_INITIALIZE_DELIMITER);
}



/*******************
* getCallString(std::string layer_template)
*
*
*/
std::string LayerGenerator::getCallString(std::string layer_template)
{
	// Extract the template from where the call begins and ends
	size_t start_position = layer_template.find(START_CALL_DELIMITER);
	size_t end_position = layer_template.find(END_CALL_DELIMITER);

	// TODO: Do the delimiters actually exist?

	start_position += START_CALL_DELIMITER.length();

	layer_template = layer_template.substr(start_position, end_position-start_position);

	return layer_template;
}


/*******************
* addLayer(Layer layer, std::string layer_type)
*
* Generic code associate with all types of layers
*/
void LayerGenerator::addLayer(Layer* layer, std::string layer_type, std::string layer_datatype)
{
	// Create strings for the path to the header and src template files
	std::string include_path = include_template_path + "/" + layer_type + ".h.template";
	std::string src_path = src_template_path + "/" + layer_type + ".cpp.template";

	// Load the templates
	std::string include_template = loadTemplate(include_path);
	std::string src_template = loadTemplate(src_path);

	// Check if this layer type has been included in the set of template files to process
	std::map<std::string, std::string>::iterator iter = include_files.find(layer_type);
	if(iter == include_files.end())
	{
		std::string include_contents = processTemplate(include_template, layer_datatype);
		include_files.insert( std::pair<std::string, std::string>(layer_type, include_contents));
	}

	iter = src_files.find(layer_type);
	if(iter == src_files.end())
	{
		std::string src_contents = processTemplate(src_template, layer_datatype);
		src_files.insert(std::pair<std::string, std::string>(layer_type, src_contents));

		// Pull out the code needed to initialize and call functions for this type of layer
		std::string initString = getInitString(src_template);
		std::string callString = getCallString(src_template);

		init_calls.insert(std::pair<std::string, std::string>(layer_type, initString));
		fwd_calls.insert(std::pair<std::string, std::string>(layer_type, callString));

	}

	// Store the layer for later use
	layers.push_back(layer);
}


/*******************
* addLayer(Layer layer)
*
* Add the layer to the list of layers to create.
*/
void LayerGenerator::addLayer(Layer* layer)
{
	addLayer(layer, layer->layer_type, "float");
}



/*******************
* dump(std::string directory, std::map<std::string,std::string> file_map, std::string extension)
*
*
*
* Arguments:
*   directory - path to the directory to write code to\
*   file_map -  mapping of file name to contents
*   extension - file extension for each file being written
*/
void LayerGenerator::dump(std::string directory, std::map<std::string,std::string> file_map, std::string extension)
{
	std::cout << "Here" << std::endl;
	// Loop through the include files and dump into the provided directory with appropriate paths
	std::map<std::string, std::string>::iterator iter;
	for(iter = file_map.begin(); iter != file_map.end(); iter++)
	{
    // FIXME: These paths compatible with MacOS and Linux not Windows
    // use boost library to make compatible
		std::cout << "Here" << std::endl;
		std::cout << directory << std::endl;
    std::string path = directory;
		std::cout << path << std::endl;
    // TODO: boost/filesystem
    // if layer/ does not exist create it
    //if (mkdir(directory.append("/layers/")) != 0){
    //    std::cout << "not created" <<std::endl;
    //} else std::cout <<"created" <<std::endl;


		path.append("/");
		path.append(iter->first);
    path.append(extension);

    //std::cout << path << std::endl;

    // Load the template from the provided path
		std::ofstream output_file;
    output_file.open(path, std::ios::out);

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
	std::cout << "Dumping headers" << std::endl;
	dump(layer_header_directory, include_files, ".h");
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
	dump(layer_src_directory, src_files, ".cpp");
}
