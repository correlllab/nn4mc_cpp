/*****************
* tensor.cpp
*
* A lightweight tensor object, used to simplify storing and accessing tensors in C++
*
*/

#include "datastructures/tensor.h"
#include <cstdarg>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>


#ifndef __TENSOR_CPP__
#define __TENSOR_CPP__

BadIndexBoundsException::BadIndexBoundsException(unsigned int dim_num, unsigned int idx_bound, unsigned int idx)
{
	dimension_number = dim_num;
	index_bound = idx_bound;
	index = idx;
}

const char* BadIndexBoundsException::what() const throw()
{
	// Create the message, indicating which dimension, and bounds
	std::string errorMessage("Bad Index: Index Out of Bounds\n");
	errorMessage += "  Out of Bounds in Dimension ";
	errorMessage += std::to_string(dimension_number);
	errorMessage += "\n";
	errorMessage += "  Index Bound is ";
	errorMessage += std::to_string(index_bound);
	errorMessage += "\n";
	errorMessage += "  Index given is ";
	errorMessage += std::to_string(index);

	return errorMessage.c_str();
}




#endif
