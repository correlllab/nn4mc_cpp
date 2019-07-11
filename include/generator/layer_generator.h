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
#include <vector>

#include "datastructures/Layer.h"

#ifndef __LAYER_GENERATOR_H__
#define __LAYER_GENERATOR_H__


class LayerGenerator
{
	private:
		// Delimiters
		static std::string WEIGHT_DATATYPE_DELIMITER;
		static std::string INDEX_DATATYPE_DELIMITER;
		static std::string LAYER_DATATYPE_DELIMITER;
		static std::string START_DELIMITER;
		static std::string END_DELIMITER;
		static std::string START_CALL_DELIMITER;
		static std::string END_CALL_DELIMITER;
		static std::string START_INITIALIZE_DELIMITER;
		static std::string END_INITIALIZE_DELIMITER;


		// Location of templates
		std::string include_template_path;
		std::string src_template_path;

		// Datatypes to replace in template files
		std::string weight_datatype_string;
		std::string index_datatype_string;

		// Types of layers to actually include in the generated files
		std::map<std::string, std::string> include_files;
		std::map<std::string, std::string> src_files;
		std::map<std::string, std::string> init_calls;
		std::map<std::string, std::string> fwd_calls;

		// Storage for the layers
		std::vector<Layer*> layers;

		// Loading template files
		std::string loadTemplate(std::string);

		// Processing template files
		std::string getFunctionString(std::string, std::string, std::string);
		std::string getInitString(std::string);
		std::string getCallString(std::string);
		std::string processTemplate(std::string, std::string);


		void dump(std::string, std::map<std::string,std::string>, std::string);
		void addLayer(Layer*, std::string, std::string);


	public:

		LayerGenerator(std::string, std::string, std::string, std::string);//const char*, const char*);
		~LayerGenerator();

		void addLayer(Layer*);
		void dumpLayerHeaders(std::string);
		void dumpLayerSources(std::string);
		
		std::string getMapInit(std::string type)
		{
			std::map<std::string, std::string>::iterator it = init_calls.find(type);
			
			if(it != init_calls.end())
				return *it;
				
			else
				return "";
		}
		std::string getMapFwd(std::string type)
		{
			std::map<std::string, std::string>::iterator it = fwd_calls.find(type);
			
			if(it != fwd_calls.end())
				return *it;
				
			else
				return "";
		}
};





#endif
