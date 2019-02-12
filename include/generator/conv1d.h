#ifndef __GENERATOR_CONV1D__
#define __GENERATOR_CONV1D__

#include <string>

class Conv1DGenerator
{
	private:
		Conv1D layer;

	public:
		Conv1DGenerator(Conv1D, std::string, std::string);
		~Conv1DGenerator();
};

#endif