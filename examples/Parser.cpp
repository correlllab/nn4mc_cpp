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

    return 0;
}
