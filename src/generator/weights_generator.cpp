#include "generator/weights_generator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

		template_file.close();
	}
	else		// File did not open!
	{

	}
}

WeightsGenerator::~WeightsGenerator()
{

}

void WeightsGenerator::addWeight(Weight* weight)
{
	// Pull out the weight's tensor for simplicity
	Tensor<double> values = *(weight->get_weight_tensor());

	// Make a copy of the content template
	std::string content(template_contents);

	// Replace the datatype delimiter with the defined datatype
	size_t datatype_position = content.find(DATATYPE_DELIMITER);

	if(datatype_position != std::string::npos)
	{
		content.replace(datatype_position, DATATYPE_DELIMITER.length(), weight_datatype);
	}


	// Replace the data name delimiter with this weight's id
	size_t data_name_position = content.find(NAME_DELIMITER);

	if(data_name_position != std::string::npos)
	{
		content.replace(data_name_position, NAME_DELIMITER.length(), weight->identifier);
	}


	// Figure out what the index should look like, and then place in the delimiter
	size_t index_position = content.find(INDEX_DELIMITER);

	if(index_position != std::string::npos)
	{
		// Calculate what the index should look like
		std::string index_string;
		for(int i=0; i<values.shape.size(); i++)
		{
			index_string += "[" + std::to_string(values.shape[i]) + "]";
		}
		content.replace(index_position, INDEX_DELIMITER.length(), index_string);
	}


	// Finally, generate the contents of the tensor
	size_t data_position = content.find(DATA_DELIMITER);
	std::string tensor_string = generate_tensor_string(&values);

	// After each newline, we'd like to pad out the next line so the tensor aligns in the file
	std::string padded_tensor_string = std::string();

	// Create the padding string
	std::string pad = std::string();
	for(int i=0; i<(int) data_position; i++)
	{
		pad += " ";
	}

	// Create the padded string by finding all newlines and replace with newline and padding
	size_t newline_position = tensor_string.find("\n");

	while(newline_position != std::string::npos)
	{
		// Copy the string up to and including the newline
		padded_tensor_string += tensor_string.substr(0, newline_position+1);
		padded_tensor_string += pad;

		// Delete the line from tensor_string
		tensor_string.erase(0, newline_position+1);

		// Fine the position of the new line
		newline_position = tensor_string.find("\n");
	}

	// Add the final line to the padded tensor string
	padded_tensor_string += tensor_string;

	if(data_position != std::string::npos)
	{
		content.replace(data_position, DATA_DELIMITER.length(), padded_tensor_string);
	}

	// And push this into the contents
	contents.push_back(content);
}


std::string WeightsGenerator::generate_tensor_string(Tensor<double>* values)
{
	std::stringstream ss;	

	std::vector<unsigned int> offsets = values->offsets;
	unsigned int num_elements = values->num_elements;

	ss << "{";

	if(values->shape.size() == 1)
	{
		for(int i=0; i<num_elements-1; i++)
		{
			ss << values->data[i] << ", ";
		}
		ss << values->data[num_elements-1];
	}
	else
	{

		for(int i=0; i<num_elements; i++)
		{
			// Check if a new row needs to be started
			for(int j=0; j<offsets.size()-1; j++)
			{
				if(i%offsets[j] == 0)	ss << "{";	else 	ss << " ";
			}

			ss << values->data[i];

			// Is this the end of (any) dimension along the tensor?  Then close all possible braces
			for(int j=offsets.size()-2; j>=0; j--)
			{
				if((i+1)%offsets[j] == 0) 	 ss << "}";
			}

			// Add a comma, and if it's not an individual element, insert a newline
			if(i < num_elements-1)
			{
				ss << ",";
				if((i+1)%offsets[offsets.size()-2] == 0)
				{
					ss << "\n";
				}
			}
		}
	}

	ss << "}";

	return ss.str();
}


void WeightsGenerator::dump(std::string filename)
{
	// Load the template from the provided path
	std::ofstream output_file(filename, std::ios::out);

	// If it's open, load the text
	if(output_file.is_open())
	{
		output_file << template_header;

		for(std::list<std::string>::iterator iter=contents.begin(); iter != contents.end(); ++iter)
		{
			output_file << *iter;
		}

		output_file << template_footer;

		output_file.close();
	}
	else		// File did not open!
	{

	}
}