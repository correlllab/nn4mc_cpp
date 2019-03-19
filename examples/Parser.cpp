#include <iostream>
#include "Parser.h"
#include "HDF5Parser.h"

int main(){
    
    HDF5Parser P("../data/weights.best.hdf5");
    P.parse();
    
    // Printing list of layer_ids:
    std::cout<< "EXAMPLE: Calling list of Layer IDs"<<std::endl;
    for (int i=0; i<P.layer_ids.size(); i++){
        std::cout << P.layer_ids[i]<< std::endl;
    }
    std::cout << "EXAMPLE: Calling layer.identifier"<<std::endl;
    // Accessing layer objects
    for (int i=0; i<P.layer_ids.size(); i++){
        std::cout<< P.layerMap[P.layer_ids[i]]->identifier <<std::endl;
    } 

    // The layer ids will map to layer objects. The way to obtain the weights and biases is through an 
    //  object called WB of the Weights type. This type contains two tensor pointers: Weights (W) and biases (b)

    return 0;
}
