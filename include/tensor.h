/**
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
#include <exception>

template <class DataType, unsigned int NumDims>
class Tensor
{
	private:
		unsigned int dimensions[NumDims];
		unsigned int offsets[NumDims];
		unsigned int num_elements;
		DataType* data;

		unsigned int array_index(unsigned int, ...);

	public:
		Tensor(unsigned int, ...);
		~Tensor();

		DataType& operator()(unsigned int, ...);
		DataType operator() (unsigned int, ...) const;
};

class InvalidDimensionException : public std::exception
{

};

class BadIndexBoundsException : public std::exception
{

};

#endif