#include "parser/HDF5Parser.h"

int main(){
    
    HDF5Parser P("../data/weights.best.hdf5");
    P.parse();
    P.NN.BFS();  

    return 0;
}
