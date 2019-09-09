/**
* \file code_generator.h
* Header file defining the code generator neural networks.
*
* \class CodeGenerator
*
* \brief Code generator for entire neural networks.
*
* This class is used to generate neural network code for the microcontroller code.
*
* \author $Author: Dana Hughes $
*
* \version $Version: 0.1 $
*
* \date $Date: 2019/03/13 $
*
* Contact: danahugh@andrew.cmu.edu
*
* Created on: Sun Mar 13 2019
*
*/

#include "generator/neural_network_generator.h"
#include "generator/layer_generator.h"
#include "generator/weight_generator.h"
#include "datastructures/NeuralNetwork.h"

#include <string>

#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__


class CodeGenerator
{
	static std::string LAYER_TEMPLATE_INCLUDE_DIR;
	static std::string LAYER_TEMPLATE_SRC_DIR;
	static std::string PARAMETER_TEMPLATE_PATH;
	static std::string SOURCE_TEMPLATE_PATH;
	static std::string PARAMETER_FILENAME;
	static std::string HEADER_FILENAME;
	static std::string SOURCE_FILENAME;
	static std::string PARAMETER_DATATYPE;
	static std::string LAYER_OUTPUT_DATATYPE;
	static std::string INDEX_DATATYPE;
    static std::string ACTIVATION_DATATYPE;
	
    private:
		std::string template_folder;
		std::string output_folder;
		
		std::string network_file;;

		// Code generators for weights and individual layers
		WeightGenerator* weight_generator;
		LayerGenerator* layer_generator;
		NNGenerator* nn_generator;

		NeuralNetwork* neural_net;

	public:
		CodeGenerator(NeuralNetwork*, std::string, std::string);
		~CodeGenerator();

		void generate();
		void dump();
};


#endif
