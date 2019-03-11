#include <iostream>
#include "Parser.h"


int main(){
    
    HDF5Parser P;
    P.file_name="../../data/weights.best.hdf5";
    P.parse();

    return 0;
}
