#ifndef __PARSER_H__
#define __PARSER_H__

#include <iostream>
#include <string>
#include <map>
#include "NeuralNetwork.h"
//#include "LayerBuilder.h"
#include <vector>
#include <sstream>
#include "LayerFactory.h"

#define FILENAME    "../../data/weights.best.hdf5"
#define HDF5_FORMAT "hdf5"
#define JSON_FORMAT "json"


typedef std::map<std::string, LayerFactory *> builder_map;

class Parser{
    // Concrete class for parser obejcts. 
    private: 
            builder_map BuilderMap;
            std::string file_format;
            std::string file_name;
    public:
            virtual int parse(std::string file_name) = 0;

            Parser(){
                BuilderMap["conv1d"]= new Conv1DFactory();
                BuilderMap["conv2d"]= new Conv2DFactory();
                BuilderMap["dense"] = new DenseFactory();
                BuilderMap["flatten"]= new FlattenFactory();
                BuilderMap["maxpooling1d"]= new MaxPooling1DFactory();
                BuilderMap["maxpooling2d"]= new MaxPooling2DFactory();
                BuilderMap["simplernn"]= new SimpleRNNFactory();
                BuilderMap["lstm"]= new LSTMFactory();
                BuilderMap["gru"]= new GRUFactory();
            }
};

class HDF5Parser : public Parser{
    public: 
        int parse(std::string);
};

class JSONParser : public Parser{
    public:
        int parse(std::string);
};

#endif
