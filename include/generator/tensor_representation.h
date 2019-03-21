/**
* \file tensor_representation.h
* Header file defining the class to convert Tensors to C code representation.
*
* \class TensorRepresentation
*
* \brief Class to generate C code representation of a tensor.
*
* This class is used to convert Tensor objects into C code.  Construction of
* the class allows for different representations---e.g., decimal formatting, 
* spacing, etc.
*
* \author $Author: Dana Hughes $
*
* \version $Version: 0.1 $
*
* \date $Date: 2019/02/13 $
*
* Contact: danahugh@andrew.cmu.edu
*
* Created on: Thu Feb 13 2019
*
*/

#include "datastructures/tensor.h"

#include <string>

#ifndef __TENSOR_REPRESENTATION_H__
#define __TENSOR_REPRESENTATION_H__

class TensorRepresentation
{
	private:
		std::string pad;
		std::string array_start, array_end;

	public:
		TensorRepresentation();
		TensorRepresentation(const char*, const char*);
		~TensorRepresentation();

		void addPad(unsigned int);
		std::string getString(Tensor<double>*);
};

#endif
