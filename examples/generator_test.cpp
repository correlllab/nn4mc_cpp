#include <iostream>
#include <vector>
#include <cstdlib>

#include "datastructures/tensor.h"
#include "generator/weight_generator.h"
#include "datastructures/weights.h"
#include "generator/layer_generator.h"
#include "generator/code_generator.h"

#include "datastructures/Layer.h"
#include "datastructures/NeuralNetwork.h"

/** SIMPLE EXAMPLE
**/
NeuralNetwork* makeNet()
{
//	Weight* w1 = new Weight("conv1_weight", std::vector<unsigned int>({2,3,4}));
//  Weight* w2 = new Weight("conv1_bias", std::vector<unsigned int>({4}));

    std::vector<unsigned int> vec1;
    std::vector<unsigned int> vec2;
    
    vec1.push_back(2);
    vec1.push_back(3);
    vec1.push_back(4);
    vec2.push_back(4);
   
    Weight* w1 = new Weight("conv1_weight", vec1);
    Weight* w2 = new Weight("conv1_bias", vec2);

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

	InputLayer* input_layer = new InputLayer("layer0");
	Conv1D* conv1d_layer = new Conv1D("layer1");
	Dense* dense_layer = new Dense("layer2");

	nn->addLayer(input_layer);
	nn->addLayer(conv1d_layer);
	nn->addLayer(dense_layer);
	nn->addEdge(input_layer, conv1d_layer);
	nn->addEdge(conv1d_layer, dense_layer);

	return nn;
}



int main(int argc, char** argv)
{
	std::cout << "Making the Neural Network" << std::endl;
	NeuralNetwork* nn = makeNet();
	nn->BFS();

	std::cout << "Neural Network: " << std::endl;
	std::cout << "  Num Layers: " << (nn->layers).size() << std::endl;
	std::cout << "  Num Ordered Layers: " << (nn->nodes_ord).size() << std::endl;
	std::cout << "  Num Input Layers: " << (nn->input).size() << std::endl;
	std::cout << "  Num Weights: " << (nn->weights).size() << std::endl;

	std::cout << "Making the Code Generator object" << std::endl;
	CodeGenerator* code_gen = new CodeGenerator(nn, "../templates/esp32", "./example_out");
	std::cout << "Generating Layer and Weight stuff" << std::endl;
	code_gen->generate();
	std::cout << "Dumping the code" << std::endl;
	code_gen->dump();

}
