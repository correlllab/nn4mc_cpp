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
};

class HDF5Parser : public Parser{
    public: 
        int parse();
        json model_config;
        HDF5Parser(std::string file_name_str){
            this->file_name= file_name_str;
        }
        json parseModelConfig();
        void buildNN();
};

class JSONParser : public Parser{
    public:
        int parse();
        JSONParser(std::string file_name_str){
            this->file_name= file_name_str;
        }
        
};

#endif
