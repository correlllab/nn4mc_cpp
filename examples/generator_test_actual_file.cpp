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
#include "generator/code_generator.h"
<<<<<<< HEAD

int main()
{

    HDF5Parser P("../data/weights.best.hdf5");
=======
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
        options_description options{"NN4MC Options"};
        options.add_options()
            ("help,h", "help screen")
            ("source,s", value<std::string>(), "name of the hdf5 file") 
            ("target,t", value<std::string>(), "name of the target folder the code will be offloaded")
            ("verbose,v",value<bool>()->default_value(true), "print neural network configuration json")
	;
        variables_map vm;
        store(parse_command_line(argc, argv, options), vm);
        notify(vm);
>>>>>>> d0385ee345bd696af989129f30aeae8ab5950b1c

        if (vm.count("help") || vm.count("h")){
       		print_help_options(options); 
	} else if (vm.count("source") || vm.count("s")){
 	    HDF5Parser P(vm["source"].as<std::string>());

	    P.parse();

	    NeuralNetwork* NN = P.get_neural_network();

<<<<<<< HEAD
    NN->reset();

    CodeGenerator* code_gen = new CodeGenerator(NN, "../templates/c_standard", "../testing_output_files/code_test");
    
    code_gen->generate();
    code_gen->dump();
=======
	    NeuralNetwork::iterator it;

	    NN->reset();

	    CodeGenerator* code_gen = new CodeGenerator(NN, "../templates/c_standard", vm["target"].as<std::string>());
	    code_gen->generate();
	    code_gen->dump();
>>>>>>> d0385ee345bd696af989129f30aeae8ab5950b1c

	    delete NN;
	    delete code_gen;
	}
    }
    catch (std::exception& ex){
   	std::cerr << ex.what() << "\n"; 
    }    
    return 0;
}
