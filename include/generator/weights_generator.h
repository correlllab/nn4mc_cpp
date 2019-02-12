/************
* weights_generator.h
*
* WeightGenerator
*
* Class for generating weights using a template file.
*/

#include <string>
#include <list>
#include "datastructures/weights.h"

#ifndef __WEIGHTS_GENERATOR_H__
#define __WEIGHTS_GENERATOR_H__

class WeightsGenerator
{
	private:

		std::string TEMPLATE_BEGIN_DELIMITER =	"<%BEGIN_TEMPLATE>";
		std::string TEMPLATE_END_DELIMITER =	"<%END_TEMPLATE>";
		std::string DATATYPE_DELIMITER =		"<%WEIGHT_DATATYPE>";
		std::string NAME_DELIMITER =			"<%WEIGHT_NAME>";
		std::string INDEX_DELIMITER	=			"<%WEIGHT_INDEX>";
		std::string DATA_DELIMITER =			"<%WEIGHT_REPRESENTATION>";

		std::string weight_template;
		std::string template_header;
		std::string template_contents;
		std::string template_footer;

		std::list<std::string> contents;

		std::string weight_datatype = std::string("float");


	public:
		WeightsGenerator(std::string);
		~WeightsGenerator();

		void addWeight(Weight);
		void dump(std::string);
};

#endif