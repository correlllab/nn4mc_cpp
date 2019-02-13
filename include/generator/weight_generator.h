/**
* \file weights_generator.h
* Header file defining the code generator for the header file for weights.
*
* \class WeightGenerator
*
* \brief Code generator for header files for weights.
*
* This class is used to generate a portion of the microcontroller code.
* Specifically, this code is used to generate header files containing 
* weights for each layer in the network.
*
* \author $Author: Dana Hughes $
*
* \version $Version: 0.1 $
*
* \date $Date: 2019/02/13 $
*
* Contact: danahugh@andrew.cmu.edu
*
* Created on: Thu Feb 11 2019
*
*/

#include <string>
#include <list>
#include "datastructures/weights.h"
#include "generator/tensor_representation.h"

#ifndef __WEIGHT_GENERATOR_H__
#define __WEIGHT_GENERATOR_H__

class WeightGenerator
{
	private:
		std::string TEMPLATE_BEGIN_DELIMITER =	"<%BEGIN_TEMPLATE>";
		std::string TEMPLATE_END_DELIMITER =	"<%END_TEMPLATE>";
		std::string DATATYPE_DELIMITER =		"<%WEIGHT_DATATYPE>";
		std::string NAME_DELIMITER =			"<%WEIGHT_NAME>";
		std::string INDEX_DELIMITER	=			"<%WEIGHT_INDEX>";
		std::string DATA_DELIMITER =			"<%DATA>";

		std::string weight_template;
		std::string template_header;
		std::string template_contents;
		std::string template_footer;

		std::list<std::string> contents;

		TensorRepresentation* tensorRepresentation;

		std::string weight_datatype = std::string("float");

		void replaceDelimiter(std::string*, std::string, std::string);

	public:
		WeightGenerator(std::string);
		WeightGenerator(std::string, TensorRepresentation*);
		~WeightGenerator();

		void addWeight(Weight*);
		void dump(std::string);
};

#endif