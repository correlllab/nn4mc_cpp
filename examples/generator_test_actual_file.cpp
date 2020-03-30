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

    HDF5Parser P("../data/LSTM.hdf5");

    P.parse();

    NeuralNetwork* NN = P.get_neural_network();

    NeuralNetwork::iterator it;

    for(it = NN->begin(); it != NN->end(); it++)
    {
      std::cout << it->layer->layer_type << std::endl;
    }

    NN->reset();

    CodeGenerator* code_gen = new CodeGenerator(NN, "../templates/c_standard", "../LSTM");
    
    code_gen->generate();
    code_gen->dump();

    delete NN;
    return 0;
}
