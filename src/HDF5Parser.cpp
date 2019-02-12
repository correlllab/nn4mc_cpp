#include <iostream>
#include <h5cpp/hdf5.hpp> 
#include "../include/tensor.h"
#include "../include/NeuralNetwork.h"

using namespace hdf5;

int main(){

    auto File= file::open("../data/weights.best.hdf5");
    auto RootGroup = File.root();
    auto Dataset = RootGroup.get_dataset("conv1d_1");
   
     
    
    return 0;
}
