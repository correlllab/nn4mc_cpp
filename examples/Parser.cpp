#include <iostream>
#include "Parser.h"
#include "HDF5Parser.h"

int main(){
    
    HDF5Parser P("../data/weights.best.hdf5");
    P.parse();
    
    // Printing list of layer_ids:
    for (int i=0; i<P.layer_ids.size(); i++){
        std::cout << P.layer_ids[i]<< std::endl;
    }

    // Accessing layer objects
    for (int i=0; i<P.layer_ids.size(); i++){
        std::cout<< P.layerMap[P.layer_ids[i]]->identifier <<std::endl;
    } 

    return 0;
}
