#include <iostream>
#include <vector>
#include <cstdlib>

#include "datastructures/tensor.h"
#include "generator/weight_generator.h"
#include "datastructures/weights.h"
#include "generator/layer_generator.h"

#include "Layer.h"

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
	WeightGenerator* generator = new WeightGenerator("../templates/esp32/include/neural_network_params.h.template", true);

	std::cout << "Write weight 1" << std::endl;
	generator->addWeight(w1);
	std::cout << "Write weight 2" << std::endl;
	generator->addWeight(w2);
	std::cout << "Dumping" << std::endl;
	generator->dump("demo_neural_net_weights.h");

	std::cout << std::endl << "BUILDING LAYERS" << std::endl;

	LayerGenerator* layer_gen = new LayerGenerator("../templates/esp32/include/layers",
												   "../templates/esp32/src/layers",
												   "const float", "int");


	Conv1D conv1d_layer("layer0");
	Dense dense_layer("layer1");

	layer_gen->addLayer(conv1d_layer);
	layer_gen->addLayer(dense_layer);

	layer_gen->dumpLayerHeaders(".");
	layer_gen->dumpLayerSources(".");

	delete generator;
}
