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

    HDF5Parser P("../data/nn_regression_att2.hdf5");
    P.parse();
    NeuralNetwork* NN = P.get_neural_network();

    NeuralNetwork::iterator it;

    std::cout << "  Neural Network: " << std::endl;

    for(it = NN->begin(); it != NN->end(); it++)
    {
      std::cout << it->layer->layer_type << std::endl;
    }

      NN->reset();

    std::cout << "Making the Code Generator object" << std::endl;
    CodeGenerator* code_gen = new CodeGenerator(NN, "../templates/esp32", "../gareth");
    std::cout << "Generating Layer and Weight stuff" << std::endl;
    code_gen->generate();
    std::cout << "Dumping the code" << std::endl;
    code_gen->dump();

    delete NN;
    return 0;
}
