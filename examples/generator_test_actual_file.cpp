/*
 *
 * 	NN4MC Main Code:
 *
 *   This code takes in the user inputs and generates 
 *   	the neural network code through command terminal 
 *   	inputs.
 */
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

    std::string h5_file_to_parse;
    std::string target_file_name;

    bool print_config = false;
    bool dump_c_code = false;     

    HDF5Parser P("../data/weights.best.hdf5");

    P.parse();

    NeuralNetwork* NN = P.get_neural_network();

    NeuralNetwork::iterator it;

    NN->reset();

    CodeGenerator* code_gen = new CodeGenerator(NN, "../templates/c_standard", "../output_files/Conv1");
    std::cout << "good up until here" << std::endl; 
    code_gen->generate();
    std::cout << "good until code generator" << std::endl; 
    code_gen->dump();
    std::cout << "successfully dumping too" << std::endl;

    delete NN;
    delete code_gen;

    return 0;
}
