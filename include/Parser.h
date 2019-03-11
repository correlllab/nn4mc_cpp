#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <string>
#include <map>
#include "NeuralNetwork.h"
#include "LayerBuilder.h"
#include <vector>
#include <sstream>
#include "LayerFactory.h"
#include <nlohmann/json.hpp>

using json= nlohmann::json;

class Parser{
    // Concrete class for parser obejcts. 
    public: 
            typedef std::map<char *, LayerFactory *> builder_map;
            builder_map BuilderMap;
            std::string file_format;
            std::string file_name;
            virtual int parse() = 0;
            virtual ~Parser() = default;
           /*     this-> file_name = str1; 
                this->BuilderMap["conv1d"]= new Conv1DFactory();
                this->BuilderMap["conv2d"]= new Conv2DFactory();
                this->BuilderMap["dense"] = new DenseFactory();
                this->BuilderMap["flatten"]= new FlattenFactory();
                this->BuilderMap["maxpooling1d"]= new MaxPooling1DFactory();
                this->BuilderMap["maxpooling2d"]= new MaxPooling2DFactory();
                this->BuilderMap["simplernn"]= new SimpleRNNFactory();
                this->BuilderMap["lstm"]= new LSTMFactory();
                this->BuilderMap["gru"]= new GRUFactory();*/
};

class HDF5Parser : public Parser{
    public: 
        int parse();
        json parseModelConfig(); 
        std::string file_name;
};

class JSONParser : public Parser{
    public:
        int parse();
};

#endif
