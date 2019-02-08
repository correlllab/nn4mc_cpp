#ifndef _WEIGHTS_H__
#define _WEIGHTS_H__

#include <iostream>
#include <string>
#include <vector>
#include <Eigen/Dense>


class Weights {
    private:
        std::vector<int> dimensions;
        std::string identifier;

    public:
        Eigen::MatrixXd W;
        Eigen::VectorXd b;
        Weights(std::vector<int> dims, std::string id){ 
            // common non-abstract constructor
            this.identifier= id;
            for(int i=0; i<dims.size(); i++){
                this.dimensions.push_back(dims.at[i]);
            }
        } 
};

#endif
