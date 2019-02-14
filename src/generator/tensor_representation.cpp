
#include "generator/tensor_representation.h"
#include "datastructures/tensor.h"

#include <string>
#include <sstream>
#include <vector>

/*******************
* TensorRepresentation
*/
TensorRepresentation::TensorRepresentation()
{
	// Initially assume no padding after newline
	pad = std::string("");
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