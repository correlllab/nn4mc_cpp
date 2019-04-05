## Examples:

To run Parser.cpp:


h5c++ -std=c++11 -I../include/ -I../include/datastructures -I../lib/nlohmann_json/include ../src/parser/HDF5Parser.cpp ../src/datastructures/NeuralNetwork.cpp ../src/datastructures/tensor.cpp ../src/datastructures/weights.cpp ../src/datastructures/Layer.cpp ../src/parser/LayerBuilder.cpp parser_example.cpp

