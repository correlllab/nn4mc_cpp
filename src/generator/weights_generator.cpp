#include "generator/weights_generator.h"

#include <iostream>
#include <fstream>
#include <string>

WeightsGenerator::WeightsGenerator(std::string template_path)
{
	// Load the template from the provided path
	std::ifstream template_file(template_path, std::ios::in);

	// If it's open, load the text
	if(template_file.is_open())
	{
		weight_template.assign ( (std::istreambuf_iterator<char>(template_file)), (std::istreambuf_iterator<char>()) );

		// Split the weight template into the template header, contents and footer
		// Get the header
		size_t begin_position = weight_template.find(TEMPLATE_BEGIN_DELIMITER);
		if(begin_position == std::string::npos)		{ /* What to do if the delimiter isn't found */ }
		template_header = weight_template.substr(0, begin_position);
		weight_template.erase(0, begin_position + TEMPLATE_BEGIN_DELIMITER.length());

		// Get the template
		size_t end_position = weight_template.find(TEMPLATE_END_DELIMITER);
		if(end_position == std::string::npos)		{ /* What to do if the delimiter isn't found */ }
		template_contents = weight_template.substr(0, end_position);
		weight_template.erase(0, end_position + TEMPLATE_END_DELIMITER.length());

		// Get the footer
		template_footer = std::string(weight_template);
	}
	else		// File did not open!
	{

	}
}

WeightsGenerator::~WeightsGenerator()
{

}

void WeightsGenerator::addWeight(Weight weight)
{
	// Pull out the weight's tensor for simplicity
	Tensor<double> values = *(weight.values);

	// Make a copy of the content template
	std::string content(template_contents);

	// Replace the datatype delimiter with the defined datatype
	size_t datatype_position = content.find(DATATYPE_DELIMITER);
	if(datatype_position != std::string::npos)
	{
		content.replace(datatype_position, datatype_position+DATATYPE_DELIMITER.length(), weight_datatype);
	}

	// Replace the data name delimiter with this weight's id
	size_t data_name_position = content.find(NAME_DELIMITER);
	if(data_name_position != std::string::npos)
	{
		content.replace(data_name_position, data_name_position+NAME_DELIMITER.length(), weight.identifier);
	}

	// Figure out what the index should look like, and then place in the delimiter
	size_t index_position = content.find(INDEX_DELIMITER);
	if(index_position != std::string::npos)
	{
		// Calculate what the index should look like
		std::string index_string;
		for(int i=0; i<values.shape.size(); i++)
		{
//			index_string += "[" + std::to_string(values.shape[i]) + "]";
		}
		content.replace(index_position, index_position+INDEX_DELIMITER.length(), index_string);
	}

	// Finally, generate the contents of the tensor
	size_t data_position = content.find(DATA_DELIMITER);
	if(data_position != std::string::npos)
	{
		content.replace(data_position, data_position+DATA_DELIMITER.length(), values.to_string());
	}

	// And push this into the contents
	contents.push_back(content);

}

void WeightsGenerator::dump(std::string filename)
{

}