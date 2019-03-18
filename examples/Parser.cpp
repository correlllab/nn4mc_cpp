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

    // Printing map of Layers:
    for (int i=0; i<P.layer_ids.size(); i++){
        //std::cout<< P.layerBuilderVector[i].layerObject<< std::endl;
    } 

    return 0;
}
