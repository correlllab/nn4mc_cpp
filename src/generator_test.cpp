#include <iostream>
#include <vector>
#include <cstdlib>

#include "datastructures/tensor.h"
#include "generator/weight_generator.h"
#include "datastructures/weights.h"
#include "generator/layer_generator.h"
#include "generator/code_generator.h"

#include "Layer.h"
#include "NeuralNetwork.h"

/** SIMPLE EXAMPLE
**/
NeuralNetwork* makeNet()
{
	// Make two weights to add to the generator
	Weight* w1 = new Weight("conv1_weight", std::vector<unsigned int>({2,3,4}));
	Weight* w2 = new Weight("conv1_bias", std::vector<unsigned int>({4}));

	Tensor<double>* v1 = w1->get_weight_tensor();
	Tensor<double>* v2 = w2->get_weight_tensor();

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

	NeuralNetwork* nn = new NeuralNetwork();

	Conv1D* conv1d_layer = new Conv1D("layer0");
	Dense* dense_layer = new Dense("layer1");

	nn->addLayer(conv1d_layer);
	nn->addLayer(dense_layer);
	nn->addEdge(conv1d_layer, dense_layer);

	return nn;
}



int main(int argc, char** argv)
{
	std::cout << "Making the Neural Network" << std::endl;
	NeuralNetwork* nn = makeNet();
	nn->BFS();
	std::cout << "Making the Code Generator object" << std::endl;
	CodeGenerator* code_gen = new CodeGenerator(nn, "../templates/esp32", "./example_out");
	std::cout << "Generating Layer and Weight stuff" << std::endl;
	code_gen->generate();
	std::cout << "Dumping the code" << std::endl;
	code_gen->dump();

}
