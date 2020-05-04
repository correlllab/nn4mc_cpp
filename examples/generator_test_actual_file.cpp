#include <iostream>
#include <vector>
#include <cstdlib>
#include "parser/h5_parser.h"
#include "generator/code_generator.h"

int main()
{

    HDF5Parser P("../data/weights.best.hdf5");

    P.parse();

    NeuralNetwork* NN = P.get_neural_network();

    NeuralNetwork::iterator it;

    NN->reset();

    CodeGenerator* code_gen = new CodeGenerator(NN, "../templates/c_standard", "../testing_output_files/code_test");
    
    code_gen->generate();
    code_gen->dump();

    delete NN;
    return 0;
}
