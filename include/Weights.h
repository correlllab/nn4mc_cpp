#ifndef __WEIGHTS_H__
#define __WEIGHTS_H__

#include <iostream>
#include <string>
#include <vector>
#include "datastructures/tensor.h"

class Weights {
    private:
        std::vector<int> dimensionsW;
        std::vector<int> dimensionsB;
        std::string identifier;
    public:
        Weights(std::vector<int> dims, std::string id){
            // common non-abstract constructor
            this->identifier= id;
            for(int i=0; i<dims.size(); i++){
                this->dimensionsW.push_back(dims[i]);
            }
            dimensionsB.push_back(1);
            dimensionsB.push_back(dims[dims.size()-1]);

        }
};

#endif
