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

int main(int argc, const char *argv[])
{
    // Parsing arguments:
    try{
        options_description options{"Options"};
        options.add_options()
            ("help,h", "Help screen")
            ("h5file,h5", value<std::string>()->default_value("../data/weights.best.hdf5"), "name of the hdf5 file") 
            ("target,f", value<std::string>()->default_value("../output_files/"), "name of the target folder the code will be offloaded")
            ("verbose,v",value<bool>()->default_value(true), "print neural network configuration json")
	;
        variables_map vm;
        store(parse_command_line(argc, argv, options), vm);
        notify(vm);

        if (vm.count("help") || vm.count("h")){
            std::cout << options << "\n";    
        }
    }
    catch (std::exception& ex){
   	std::cerr << ex.what() << "\n"; 
    }
	 
    bool print_config = false;
    bool dump_c_code = false;     
    
    std::string h5_file_to_parse;
    std::string target_file_name;
    
    HDF5Parser P("../data/weights.best.hdf5");

    P.parse();

    NeuralNetwork* NN = P.get_neural_network();

    NeuralNetwork::iterator it;

    NN->reset();

    CodeGenerator* code_gen = new CodeGenerator(NN, "../templates/c_standard", "../output_files/Conv1");
    
    code_gen->generate();
    
    code_gen->dump();

    delete NN;
    delete code_gen;

    return 0;
}
