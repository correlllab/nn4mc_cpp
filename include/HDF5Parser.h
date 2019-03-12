#ifndef __HDF5_PARSER_H__
#define __HDF5_PARSER_H__

#include <iostream>
#include <string>
#include <map>
#include "NeuralNetwork.h"
#include <vector>
#include <sstream>
#include "LayerFactory.h"
#include <nlohmann/json.hpp>

#else
#include <iostream>
#endif
#include <string>
#include "datastructures/tensor.h"
#include <vector>

#ifndef H5_NO_NAMESPACE
#ifndef H5_NO_STD
    using std::cout;
    using std::cerr;
    using std::endl;
#endif  // H5_NO_STD
#endif

#include "H5Cpp.h"
#include "Parser.h"
#include <iomanip>
#include <sstream>
#include "LayerBuilder.h"
#ifndef H5_NO_NAMESPACE
using namespace H5;
using json=nlohmann::json;

#endif


class HDF5Parser : public Parser{
    public: 
        int parse();
        typedef std::map<std::string, LayerFactory *> builder_map;
        std::vector<LayerBuilder*> layerBuilderVector;

        builder_map BuilderMap;
        json model_config;
        HDF5Parser(std::string file_name_str){
            this->file_name= file_name_str;
        }
        json parseModelConfig();
        void parseNeuralNetworkArchitecture();
        void constructBuilderMap();
        void buildNN();
        struct opdata{
            builder_map BuilderMap;
            std::vector<LayerBuilder*> layerBuilderVector;
        } od;
};


