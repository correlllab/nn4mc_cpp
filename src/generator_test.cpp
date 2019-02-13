#include <iostream>
#include <vector>
#include <cstdlib>

#include "datastructures/tensor.h"
#include "generator/weights_generator.h"
#include "datastructures/weights.h"

/** SIMPLE EXAMPLE
**/
int main(int argc, char** argv)
{
	// Make two weights to add to the generator
	Weight* w1 = new Weight("conv1_weight", std::vector<unsigned int>({2,3,4}));
	Weight* w2 = new Weight("conv1_bias", std::vector<unsigned int>({4}));

	Tensor<double>* v1 = w1->get_weight_tensor();
	Tensor<double>* v2 = w2->get_weight_tensor();

	std::cout << "Populating tensors" << std::endl;
	// Populate with random doubles
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<4; k++)
			{
				(*v1)(i,j,k) = (double)rand() / RAND_MAX;
			}
		}
	}

	for(int i=0; i<4; i++)
	{

		(*v2)(i) = (double)rand() / RAND_MAX;
	}


	std::cout << "Printing tensors" << std::endl;
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<4; k++)
			{
				std::cout << (*v1)(i,j,k) << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for(int i=0; i<4; i++)
	{
		std::cout << (*v2)(i) << " ";
	}
	std::cout << std::endl;

	std::cout << "Done is printing" << std::endl;
	// Now create a weight generator object
	WeightsGenerator generator = WeightsGenerator("../templates/esp32/header/neural_network_params.h.template");

	std::cout << "Write weight 1" << std::endl;
	generator.addWeight(w1);
	std::cout << "Write weight 2" << std::endl;
	generator.addWeight(w2);
	std::cout << "Dumping" << std::endl;
	generator.dump("demo_neural_net_weights.h");
}
