#include <iostream>
#include "hdf5/include/hdf5.h" 
#include "hdf5/include/H5Cpp.h" 
//#include "../include/datastructures/tensor.h"
//#include "../include/NeuralNetwork.h"
#include <string>

using namespace H5;

const H5std_string FILE_NAME("../data/weights.best.hdf5");
const H5std_string DATASET_NAME("IntArray");
const int NX_SUB = 3;
const int NY_SUB = 4;
const int NX = 7;
const int NY = 7;
const int NZ = 3;
const int RANK_OUT = 3;

int main(){
    std::cout<<"here"<<std::endl;
        int i, j, k;
        int data_out[NX][NY][NZ];
        
        for (j=0; j < NX; j++){
            for (i=0; i<NY; i++){ 
                for (k=0; k< NZ; k++){
                  data_out[j][i][k] = 0;
                }
            } 
        }

    
    return 0;
}
