#include "parser/HDF5Parser.h"

int main(){
    HDF5Parser P("../data/weights.best.hdf5");
    NeuralNetwork * NN; 
    P.parse();
    NN = P.constructNeuralNetwork();
    NN->BFS();
    return 0;
}
