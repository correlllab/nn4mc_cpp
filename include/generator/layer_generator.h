/**
* \file layer_generator.h
* Header file defining the code generator for the header and cpp file for layers.
*
* \class LayerGenerator
*
* \brief Code generator for header and source files for layers.
*
* This class is used to generate a portion of the microcontroller code.
* Specifically, this code is used to generate header files containing 
* definitions of layer structures, and source files for layer creation
* and calling.
*
* \author $Author: Dana Hughes $
*
* \version $Version: 0.1 $
*
* \date $Date: 2019/03/10 $
*
* Contact: danahugh@andrew.cmu.edu
*
* Created on: Sun Mar 10 2019
*
*/

#include <string>
#include <array>
#include <map>

#include "Layer.h"

#ifndef __LAYER_GENERATOR_H__
#define __LAYER_GENERATOR_H__


class LayerGenerator
{
	private:
		// Delimiters
		static std::string WEIGHT_DATATYPE_DELIMITER;
		static std::string INDEX_DATATYPE_DELIMITER;

		// Types of layers defined, and number of defined layers
		static std::array<std::string, 9> layer_types;

		// Location of templates
		std::string include_template_path;
		std::string src_template_path;

		// Datatypes to replace in template files
		std::string weight_datatype_string;
		std::string index_datatype_string;

		// Types of layers to actually include in the generated files
		std::map<std::string, std::string> include_files;
		std::map<std::string, std::string> src_files;

		std::string processTemplate(std::string);
		void dump(std::string, std::map<std::string,std::string>);


	public:

		LayerGenerator(std::string, std::string, const char*, const char*);
		~LayerGenerator();

		void addLayer(Conv1D);
		void addLayer(Conv2D);
		void addLayer(Dense);
		void addLayer(Flatten);
		void addLayer(MaxPooling1D);
		void addLayer(MaxPooling2D);
		void addLayer(SimpleRNN);
		void addLayer(GRU);
		void addLayer(LSTM);


		void dumpLayerHeaders(std::string);
		void dumpLayerSources(std::string);
};





#endif