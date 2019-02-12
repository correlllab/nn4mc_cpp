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
	Weight w1 = Weight("conv1_weight", std::vector<unsigned int>({2,3,4}));
	Weight w2 = Weight("conv1_biad", std::vector<unsigned int>({4}));

	Tensor<double> v1 = *(w1.values);
	Tensor<double> v2 = *(w2.values);

	// Populate with random doubles
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<4; k++)
			{
				v1(i,j,k) = (double)rand() / RAND_MAX;
			}
		}
	}

	for(int i=0; i<4; i++)
	{
		v2(i) = (double)rand() / RAND_MAX;
	}

	// Now create a weight generator object
	WeightsGenerator generator = WeightsGenerator("../templates/esp32/header/neural_network_params.h.template");
	generator.addWeight(w1);
//	generator.addWeight(w2);
//	generator.dump("demo_neural_net_weights.h");
}
