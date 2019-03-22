#include <iostream>
#include "parser/Parser.h"
#include "parser/HDF5Parser.h"

int main(){
    
    HDF5Parser P("../data/weights.best.hdf5");
    P.parse();
    
    // Printing list of layer_ids:
    std::cout<< "EXAMPLE: Calling list of Layer IDs"<<std::endl;
    for (int i=0; i<P.layer_ids.size(); i++){
        std::cout << P.layer_ids[i]<< std::endl;
    }
    std::cout << "EXAMPLE: Calling layer.identifier"<<std::endl;

    // Access NeuralNetwork nodes with: P.NN
    
    P.NN.BFS();


    return 0;
}
