#include "parser/HDF5Parser.h"

int main(){
    NeuralNetwork * NN; 
    HDF5Parser P("../data/weights.best.hdf5");
    P.parse();
    NN = P.constructNeuralNetwork();
    NN->BFS();
    return 0;
}
