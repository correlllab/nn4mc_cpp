#include "parser/HDF5Parser.h"

int main(){
    
    HDF5Parser P("../data/weights.best.hdf5");
    P.parse();

    P.NN.BFS(); // P.NN is the neural network with all the loaded nodes and (hopefully) correct information 

    return 0;
}
