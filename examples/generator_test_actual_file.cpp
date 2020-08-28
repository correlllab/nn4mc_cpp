/*
 *
 * 	NN4MC Main Code:
 *
 *   This code takes in the user inputs and generates 
 *   	the neural network code through command terminal 
 *   	inputs.
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include "parser/h5_parser.h"
#include "datastructures/tensor.h"
#include "generator/weight_generator.h"
#include "datastructures/weights.h"
#include "generator/layer_generator.h"
#include "generator/code_generator.h"
#include "datastructures/Layer.h"
#include "datastructures/NeuralNetwork.h"
#include <boost/program_options.hpp>
#include <exception>
#include <string>

using namespace boost::program_options;


void print_help_options(options_description opt){
	std::cout << opt << std::endl;
}


int main(int argc, const char *argv[])
{
    // Parsing arguments:
    try{
        options_description options{"Options"};
        options.add_options()
            ("help,h", "Help screen")
            ("h5file,h5", value<std::string>(), "name of the hdf5 file") 
            ("target,f", value<std::string>(), "name of the target folder the code will be offloaded")
            ("verbose,v",value<bool>()->default_value(true), "print neural network configuration json")
	;
        variables_map vm;
        store(parse_command_line(argc, argv, options), vm);
        notify(vm);

        if (vm.count("help") || vm.count("h")){
       		print_help_options(options); 
	} else if (vm.count("h5file") || vm.count("h5")){

	    HDF5Parser P(vm["h5file"].as<std::string>());

	    P.parse();

	    NeuralNetwork* NN = P.get_neural_network();

	    NeuralNetwork::iterator it;

	    NN->reset();

	    CodeGenerator* code_gen = new CodeGenerator(NN, "../templates/c_standard", vm["target"].as<std::string>());
	    
	    code_gen->generate();
	    
	    code_gen->dump();

	    delete NN;
	    delete code_gen;
	}
    }
    catch (std::exception& ex){
   	std::cerr << ex.what() << "\n"; 
    }    
    return 0;
}
