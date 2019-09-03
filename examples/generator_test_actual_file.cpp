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

    HDF5Parser P("../data/weights.best.hdf5");
    P.parse();
    NeuralNetwork* nn = P.constructNeuralNetwork();
    nn->BFS();

    std::cout << "  Neural Network: " << std::endl;
    std::cout << "  Num Layers: " << (nn->layers).size() << std::endl;
    std::cout << "  Num Ordered Layers: " << (nn->nodes_ord).size() << std::endl;
    std::cout << "  Num Input Layers: " << (nn->input).size() << std::endl;
    std::cout << "  Num Weights: " << (nn->weights).size() << std::endl;

    nn->reset();

    std::cout << "Making the Code Generator object" << std::endl;
    CodeGenerator* code_gen = new CodeGenerator(nn, "../templates/esp32", "../example_out");
    std::cout << "Generating Layer and Weight stuff" << std::endl;
    code_gen->generate();
    std::cout << "Dumping the code" << std::endl;
    code_gen->dump();

    delete nn;
    return 0;
}
