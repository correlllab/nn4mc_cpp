#include <iostream>
#include <vector>
#include <cstdlib>
#include "parser/h5_parser.h"
#include "datastructures/tensor.h"
#include "generator/weight_generator.h"
#include "datastructures/weights.h"
#include "generator/layer_generator.h"
#include "generator/code_generator.h"

#include "datastructures/Layer.h"
#include "datastructures/NeuralNetwork.h"

int main()
{

    HDF5Parser P("../data/GRU.hdf5");

    P.parse();

    NeuralNetwork* NN = P.get_neural_network();

    NeuralNetwork::iterator it;

    NN->reset();

    CodeGenerator* code_gen = new CodeGenerator(NN, "../templates/c_standard", "../output_files/LSTM");
    
    code_gen->generate();
    code_gen->dump();

    delete NN;
    return 0;
}
