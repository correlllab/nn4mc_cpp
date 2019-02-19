#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <string>
#include <map>
#include "NeuralNetwork.h"
#include "LayerBuilder.h"
#include <vector>

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
            std::map<layer_type, LayerBuilder*> builderMap;                    
            NeuralNetwork NN();
    public:
            Parser(){
/*
                builderMap.insert(std::make_pair(layer_type.CONV1D, new Conv1DBuilder()));
                builderMap.insert(std::make_pair(layer_type.CONV2D, new Conv2DBuilder()));
                builderMap.insert(std::make_pair(layer_type.DENSE, new DenseBuilder()));
                builderMap.insert(std::make_pair(layer_type.FLATTEN, new FlattenBuilder()));
                builderMap.insert(std::make_pair(layer_type.MAXPOOLING1D, new MaxPooling1DBuilder()));
                builderMap.insert(std::make_pair(layer_type.MAXPOOLING2D, new MaxPooling2DBuilder()));
                builderMap.insert(std::make_pair(layer_type.SIMPLERNN, new SimpleRNNBuilder()));
                builderMap.insert(std::make_pair(layer_type.GRU, new GRUBuilder()));
                builderMap.insert(std::make_pair(layer_type.LSTM, new LSTMBuilder()));
 */           
            std::vector<std::string> splitString;
            std::string token;
            istringstream iss(FILENAME);
            while(std::getline(iss, token, '.')){
                if (!token.empty())
                    splitString.push_back(token);
            }
            if (splitString[splitString.size()-1].compare(HDF5_FORMAT)){
                HDF5Parser();              
            } else if(splitString[splitString.size()-1].compare(JSON_FORMAT)){
                JSONParser();
              } 
            }; 
};


class HDF5Parser : public Parser {
   
    public:
         
        HDF5Parser(){
            void ParseHDF5(NeuralNetwork );
        };

};

class JSONParser : public Parser{
    public:

        JSONParser(){
            void ParserJSON(NeuralNetwork );
        };
};

#endif
