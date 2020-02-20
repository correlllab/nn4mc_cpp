#include <iostream>
#include <vector>
#include <cstdlib>
#include "parser/HDF5Parser.h"
#include "datastructures/tensor.h"
#include "generator/weight_generator.h"
#include "datastructures/weights.h"
#include "generator/layer_generator.h"
#include "generator/code_generator.h"

#include "datastructures/Layer.h"
#include "datastructures/NeuralNetwork.h"

int main()
{

    HDF5Parser P("../data/simpleRNN.hdf5");
    
    std::cout << "Parsing neural network..." << std::endl;

    P.parse();

    std::cout << "Neural Network parsed!" << std::endl;

    NeuralNetwork* NN = P.get_neural_network();
    
    std::cout << "get neural network" << std::endl;
    
    NeuralNetwork::iterator it;

    std::cout << "  Neural Network: " << std::endl;

    for(it = NN->begin(); it != NN->end(); it++)
    {
      std::cout << it->layer->layer_type << std::endl;
    }

      NN->reset();

    std::cout << "Making the Code Generator object" << std::endl;
    CodeGenerator* code_gen = new CodeGenerator(NN, "../templates/esp32", "../simpleRNN");
    std::cout << "Generating Layer and Weight stuff" << std::endl;
    code_gen->generate();
    std::cout << "Dumping the code" << std::endl;
    code_gen->dump();

    delete NN;
    return 0;
}
