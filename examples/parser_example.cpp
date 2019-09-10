#include "parser/HDF5Parser.h"

int main(){
    HDF5Parser P("../data/weights.best.hdf5");
    NeuralNetwork * NN; 
    std::cout <<"____PARSER_EXAMPLE_:: HERE_____"<< std::endl;
    P.parse();
    NN = P.get_neural_network();
    NN->BFS();
    return 0;
}
