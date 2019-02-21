/**
* \file tensor.h
* Header file defining the Tensor class and associated Exceptions 
*
* \class Tensor
*
* \brief Light wrapper for tensors
*
* This class is meant to be used as a wrapper for Tensors of arbitrary
* dimensionality.  It does *not* define Tensor operations.  Rather, it
* simply acts as a means to store and access values in a Tensor without
* having to deal with underlying C++ details for memory access.
*
* \author $Author: Dana Hughes $
*
* \version $Version: 0.1 $
*
* \date $Date: 2019/02/07 $
*
* Contact: danahugh@andrew.cmu.edu
*
* Created on: Thu Feb 07 2019
*
*/

#ifndef __TENSOR_H__
#define __TENSOR_H__

#include <cstdarg>
#include <cstdlib>
#include <exception>
#include <vector>
#include <string>

template <class DataType>
class Tensor
{
	private:

	public:	
		std::vector<unsigned int> offsets;
		unsigned int num_elements;

		DataType* data;

		unsigned int array_index(unsigned int, va_list);

		std::vector<unsigned int> shape;

		Tensor(std::vector<unsigned int>);
		~Tensor();

		DataType& operator()(unsigned int, ...);
		DataType operator() (unsigned int, ...) const;

		DataType value_at(unsigned int);
		std::string to_string();
};

class BadIndexBoundsException : public std::exception
{
	public:
		BadIndexBoundsException(unsigned int, unsigned int, unsigned int);
		~BadIndexBoundsException() throw();
		unsigned int dimension_number;
		unsigned int index_bound;
		unsigned int index;
		virtual const char* what() const throw();
};


/**
** NOTE:  Tensor methods are defined here, as defining them in a separate cpp file is problematic
**/


/*******************
* Tensor(std::vector<unsigned int>)
*
* The constructor takes a variable number of arguments, and populates 
* the dimensions array and offset array.
*/
template <class DataType>
Tensor<DataType>::Tensor(std::vector<unsigned int> _shape)
{
	// Copy the shape of the tensor, and create a vector for the offset
	shape = std::vector<unsigned int>(_shape);
	offsets = std::vector<unsigned int>(shape.size());

	// Now calculate the offsets for each index - this will simply
	// be the product of the dimensionality of all indices following
	// the current one
	// Also, calculate the total number of elements - this will 
	// be the product of the dimensionality of all indices
	unsigned int offset = 1;
	num_elements = 1;

	for(int idx=shape.size()-1; idx >= 0; idx--)
	{
		offsets[idx] = offset;
		offset *= shape[idx];

		num_elements *= shape[idx];
	}

	// Allocate the actual data array
	data = new DataType[num_elements];
}


/**********
* ~Tensor()
*
* The destructor simply cleans up the data allocated to storing the 
* actual tensor
*/
template <class DataType>
Tensor<DataType>::~Tensor()
{
	// Delete the allocated memory and free up the memory, and set it
	// to NULL so it won't be de-allocated again by accident (somehow)
	delete[] data;
	shape.clear();
	offsets.clear();

	data = NULL;
}


/**********
* array_index(unsigned int, ...)
*
* Converts from the tensor indexing to the 1D index used by the actual data
*/
template <class DataType>
unsigned int Tensor<DataType>::array_index(unsigned int idx_0, va_list arguments)
{
	unsigned int arg;

	// Start with the first index multiplied by the appropriate offset
	// Is the first index out of bounds?
	if(idx_0 >= shape[0])		throw BadIndexBoundsException(0, shape[0], idx_0);
	unsigned int index = offsets[0] * idx_0;

	// Iterate through the remaining index values
	for(int idx = 1; idx < shape.size(); idx++)
	{
		arg = va_arg(arguments, unsigned int);
		// Is the index out of bounds?
		if(arg >= shape[idx])		throw BadIndexBoundsException(idx, shape[idx], arg);
		index += offsets[idx] * arg;
	}

	return index;
}


/**********
* operator()(unsigned int, ...)
*
* Access the element at the given index
*/
template <class DataType>
DataType& Tensor<DataType>::operator()(unsigned int idx_0, ...)
{
	// What is the array index to access?
	va_list arguments;
	va_start(arguments, idx_0);
	unsigned int index = array_index(idx_0, arguments);
	va_end(arguments);

	return data[index];
}


/**********
* operator()(unsigned int, ...) const
*
* Access the element at the given index
*/
template <class DataType>
DataType Tensor<DataType>::operator()(unsigned int idx_0, ...) const
{
	// What is the array index to access?
	va_list arguments;
	va_start(arguments, idx_0);
	unsigned int index = array_index(idx_0, arguments);
	va_end(arguments);

	return data[index];
}

template <class DataType>
DataType Tensor<DataType>::value_at(unsigned int idx)
{
	return data[idx];
}

template <class DataType>
std::string Tensor<DataType>::to_string()
{
	std::string data_string;

	data_string += "{{{ DATA }}}";

	return data_string;
}

#endif
