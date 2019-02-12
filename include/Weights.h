#ifndef __WEIGHTS_H__
#define __WEIGHTS_H__

#include <iostream>
#include <string>
#include <vector>
<<<<<<< HEAD
=======
#include "datastructures/tensor.h"
#include "datastructures/tensor.cpp"
>>>>>>> origin/master


class Weights {
    private:
        std::vector<int> dimensions;
        std::string identifier;

    public:
        Weights(std::vector<int> dims, std::string id){ 
            // common non-abstract constructor
            this->identifier= id;
            for(int i=0; i<dims.size(); i++){
                this->dimensions.push_back(dims[i]);
            }
        } 
};

#endif
