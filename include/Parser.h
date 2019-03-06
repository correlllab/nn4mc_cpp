#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <string>
#include <map>
#include "NeuralNetwork.h"
//#include "LayerBuilder.h"
#include <vector>
#include <sstream>

#define FILENAME    "../../data/weights.best.hdf5"
#define HDF5_FORMAT "hdf5"
#define JSON_FORMAT "json"

class Parser{
    // Concrete class for parser obejcts. 
    private: 
            enum layer_type  {CONV1D, CONV2D, 
                DENSE, FLATTEN, MAXPOOLING1D,               
                MAXPOOLING2D, SIMPLERNN, GRU, LSTM};

            std::string file_format;
    public:
            Parser(){
            int ParseHDF5(void);
            int ParseJSON(void);
            void Parse(void);
            }
};

void Parser::Parse(void){
    std::vector<std::string> splitString;
    std::string token;
    std::istringstream iss(FILENAME);
    while(std::getline(iss, token, '.')){
        if (!token.empty())
            splitString.push_back(token);
    }
    if (splitString[splitString.size()-1].compare(HDF5_FORMAT)){
    std::cout<<"Parser: parsing hdf5..."<<std::endl;
        ParseHDF5();              
    } else if(splitString[splitString.size()-1].compare(JSON_FORMAT)){
        std::cout<< "Parser: parsing json..."<<std::endl;
        ParseJSON();
      } 
}

//TODO:
int Parser::ParseJSON(void){
    std::cout<< "here" <<std::endl;
    return 0;
}

#endif
