
#include "generator/tensor_representation.h"
#include "datastructures/tensor.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

/*******************
* TensorRepresentation
*/
TensorRepresentation::TensorRepresentation()
{
	// Initially assume no padding after newline
	std::cout << "In default constructor" << std::endl;

	// Assume that C / C++ arrays are being used, and the dimensionality of
	// the array matches that of the tensor
	array_start = std::string("{");
	array_end = std::string("}");
}


/*******************
* TensorRepresentation
*
* char array_starter
* char array_ender
*/
TensorRepresentation::TensorRepresentation(const char* array_start_char, const char* array_end_char)
{

	pad = std::string("");

	array_start = std::string(array_start_char);
	array_end = std::string(array_end_char);
}


/*******************
* ~TensorRepresentation
*/
TensorRepresentation::~TensorRepresentation()
{

}


/*******************
* addPad(unsigned int pad_size)
*
* Indicate how much padding to add to each newline created when generating
* a string
*
* Arguments:
*   pad_size - how many spaces to add to the pad
*/
void TensorRepresentation::addPad(unsigned int pad_size)
{
	// Reset the pad and add however many spaces
	pad = std::string("");
	for(int i=0; i<pad_size; i++)
	{
		pad += " ";
	}
}

/*******************
* getString(Tensor* values)
*
* Convert the provided tensor to a string representation of a multidimensional
* array in C
*
* Arguments:
*   values - the Tensor to convert
*/
std::string TensorRepresentation::getString(Tensor<double>* values)
{
	//std::cout << "In getString - " << array_start << " " << array_end << std::endl;
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
				if(i%offsets[j] == 0)	ss << array_start;	else 	ss << " ";
			}

			ss << values->data[i];

			// Is this the end of (any) dimension along the tensor?  Then close all possible braces
			for(int j=offsets.size()-2; j>=0; j--)
			{
				if((i+1)%offsets[j] == 0) 	 ss << array_end;
			}

			// Add a comma, and if it's not an individual element, insert a newline
			// New lines should be padded out by our pad.
			if(i < num_elements-1)
			{
				ss << ",";
				if((i+1)%offsets[offsets.size()-2] == 0)
				{
					ss << "\n" << pad;
				}
			}
		}
	}

	ss << "}";
	return ss.str();
}
