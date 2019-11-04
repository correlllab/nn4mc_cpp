#include "parser/HDF5Parser.h"

int main(){
    HDF5Parser P("../data/weights.best.hdf5");
    NeuralNetwork * NN;
    std::cout <<"____PARSER_EXAMPLE_:: HERE_____"<< std::endl;
    P.parse();
    NN = P.get_neural_network();

    NeuralNetwork::iterator it;

  	for(it = NN->begin(); it != NN->end(); it++)
  	{
      std::cout << it->layer->layer_type << std::endl;
  	}

    return 0;
}
