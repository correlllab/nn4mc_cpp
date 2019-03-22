#include <iostream>
#include "parser/Parser.h"
#include "parser/HDF5Parser.h"

int main(){
    
    HDF5Parser P("../data/weights.best.hdf5");
    P.parse();

    // Access NeuralNetwork nodes with: P.NN
    
    P.NN.BFS(); // for example


    return 0;
}
