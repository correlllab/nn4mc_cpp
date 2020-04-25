#include <iostream>

#include "parser/HDF5Parser.h"
#include "generator/code_generator.h"
#include "datastructures/NeuralNetwork.h"

int main()
{

    HDF5Parser P("/Users/sarahaguasvivas/Desktop/Desktop/NikolausLecture/lenet.hdf5");

    P.parse();

    NeuralNetwork* NN = P.get_neural_network();

    NeuralNetwork::iterator it;

    for(it = NN->begin(); it != NN->end(); it++)
    {
      std::cout << it->layer->layer_type << std::endl;
    }

    NN->reset();

    CodeGenerator* code_gen = new CodeGenerator(NN, "../templates/c_standard", "../simpleRNN");
    
    code_gen->generate();
    code_gen->dump();

    delete NN;
    return 0;
}
