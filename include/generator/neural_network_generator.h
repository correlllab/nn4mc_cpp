#include "datastructures/Layer.h"
#include "datastructures/NeuralNetwork.h"
#include "layer_generator.h"

#include <string>
#include <map>


#ifndef __NEURAL_NETWORK_GENERATOR_H__
#define __NEURAL_NETWORK_GENERATOR_H__

class NNGenerator
{
    private:
      //LayerGenerator pointer
      LayerGenerator* layer_gen;

    	//Delimiters
    	static std::string INIT;
    	static std::string FWD;
    	static std::string INC;
      static std::string STRUC;

    	//Paths to header and source file for neural_network.
      std::string header_template_path;
  		std::string source_template_path;

      //Paths to activation header and source
      std::string activation_header_template_path;
      std::string activation_src_template_path;

  		//Template material to be extracted from template edited and dumped.
  		std::string header;
  		std::string source;

      //Template material extracted from activation
      std::string activation_header;
      std::string activation_source;

    	//Loads the templates using the paths into the header and source.
      void loadTemplates();

      //Takes delimiter and extracts corresponding data from layer as a string.
      //std::string convertDelimiter(LayerNode& node, std::string delimiter);

    public:

      NNGenerator(std::string, std::string, std::string, std::string, LayerGenerator*);
      ~NNGenerator();

      //void addMaps(std::map<std::string, std::string>, std::map<std::string, std::string>);

      //Adds layer to file in appropriate place and with replaced delimiters.
      void addLayer_Header(Layer*);
      void addLayer_Init(LayerNode&);
      void addLayer_Fwd(Layer*);
      void addActivation();

      //Dumps edited templates.
      void dumpHeader(std::string);
      void dumpSource(std::string);
      void dumpActivation(std::string, std::string);

};

#endif
