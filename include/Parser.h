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
            enum class layer_type  {CONV1D, CONV2D, 
                DENSE, FLATTEN, MAXPOOLING1D,               
                MAXPOOLING2D, SIMPLERNN, GRU, LSTM};

            std::string file_format;
            std::map<layer_type, LayerBuilder> builderMap;                    

    public:
            Parser(){
                builderMap layer_type={
                    {layer_type::CONV1D, Conv1DBuilder},
                    {layer_type::CONV2D, Conv2DBuilder},
                    {layer_type::DENSE, DenseBuilder},
                    {layer_type::FLATTEN, FlattenBuilder},
                    {layer_type::MAXPOOLING1D, MaxPooling1DBuilder},
                    {layer_type::MAXPOOLING2D, Maxpooling2DBuilder},
                    {layer_type::SIMPLERNN, SimpleRNNBuilder},
                    {layer_type::GRU, GRUBuilder},
                    {layer_type::LSTM, LSTMBuilder}
                }  
            
            std::vector<std::string> splitString;
            std::string token;
            while(std::getline(FILENAME, token, '.')){
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
        NeuralNetwork NN;
         
        HDF5Parser(){
            ParseHDF5(NeuralNetwork NN);
        };

};

class JSONParser : public Parser{
    public:
        NeuralNetwork NN;

        JSONParser(){
            ParserJSON(NeuralNetwork NN);
        };
};

#endif
