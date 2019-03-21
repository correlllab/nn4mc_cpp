#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <string>
#include <map>
#include "datastructures/NeuralNetwork.h"
#include "parser/LayerBuilder.h"
#include <vector>
#include <sstream>
#include "parser/LayerFactory.h"
#include <nlohmann/json.hpp>

using json= nlohmann::json;

class Parser{
    // Concrete class for parser obejcts. 
    public: 
            NeuralNetwork NN;     
            std::string file_format;
            std::string file_name;
            virtual int parse() = 0;
            virtual ~Parser() = default;
};


class JSONParser : public Parser{
    public:
        int parse();
        JSONParser(std::string file_name_str){
            this->file_name= file_name_str;
        }
        
};

#endif
