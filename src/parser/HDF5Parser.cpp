/**
 * \file HDF5Parser.cpp
 * Code to parse hdf5 file containing neural network information
 *
 * \brief Parser for hdf5 neural network file:
 * This code is meant to declare a neural network (NeuralNetwork.h) 
 * based on the hdf5 file that was output by the training code
 *
 * \author: $Author: Sarah Aguasvivas Manzano $
 *
 * \version $Version: 0.1 $
 *
 * \date $Date: 2019/02/18 $
 *
 * Contact: saag5228@colorado.edu
 *
 * Created on: Thu Feb 07 2019
 * 
 * */
#include "parser/HDF5Parser.h"

extern "C" herr_t weights_callback(hid_t loc_id, const char *name, const H5L_info_t * linfo, void *opdata);
extern "C" herr_t network_callback(hid_t loc_id, const char *name, const H5L_info_t * linfo, void *opdata);

void HDF5Parser::constructBuilderMap(){
    this->BuilderMap["Activation"] = new ActivationFactory();
    this->BuilderMap["Conv1D"]= new Conv1DFactory();
    this->BuilderMap["Conv2D"]= new Conv2DFactory();
    this->BuilderMap["Flatten"]= new FlattenFactory();
    this->BuilderMap["Dense"]= new DenseFactory();
    this->BuilderMap["MaxPooling1D"]= new MaxPooling1DFactory();
    this->BuilderMap["MaxPooling2D"]= new MaxPooling2DFactory();
    this->BuilderMap["Dropout"] = new DropoutFactory();
    this->BuilderMap["LSTM"]= new LSTMFactory();
    this->BuilderMap["GRU"]= new GRUFactory();
    this->BuilderMap["SimpleRNN"]= new SimpleRNNFactory();

}

void HDF5Parser::parseWeights(){
       
      const H5std_string FILE_NAME( this->file_name );
      Exception::dontPrint();
      H5File file = H5File(FILE_NAME, H5F_ACC_RDONLY);
      Group group = Group(file.openGroup("model_weights"));
      struct opdataWeights od_weights;
      od_weights.LM = this->layerMap;
      H5Lvisit(group.getId(), H5_INDEX_NAME, H5_ITER_INC,  weights_callback, (void*)&od_weights);
      this->layerMap= od_weights.LM;
      std::cout << "PARSER: Weights parsed!" << std::endl;
}

NeuralNetwork* HDF5Parser::get_neural_network(){
    NeuralNetwork* NN = new NeuralNetwork();
    Layer* l = new InputLayer("input_1");
    NN->addLayer(l);
    NN->addLayer(this->layerMap.begin()->second);
    NN->addEdge(l, this->layerMap.begin()->second);
    l = this->layerMap.begin()->second;

    /*for (auto it = this->layerMap.begin(); it!=this->layerMap.end(); it++){  
        NN->addLayer(it->second); // adding layers
        NN->addEdge(l, it->second);
        l= it->second;
    }
    */
    for (std::vector<std::pair<std::string, std::string>>::iterator it= this->layer_edges.begin(); it!=this->layer_edges.end(); ++it){
        
        NN->addLayer(this->layerMap[it->second]);
        NN->addEdge(l, this->layerMap[it->second]);
        l = this->layerMap[it->second];
    }
    cout<< "PARSER: Neural network nodes and edges built!"<<endl;
    return NN;
}

void HDF5Parser::build_layer_shapes(){
    
    //Layer* prev = this->layerMap.begin()->second;

    if (nn_input_shape.size()>0 && this->layerMap.begin()->second->input_shape.size() == 0){ // for the neural networks that have input somewhere else
        this->layerMap.begin()->second->input_shape = nn_input_shape;
    }
    std::cout << this->layerMap.begin()->second->identifier << std::endl;
    this->layerMap.begin()->second->compute_output_shapes();

    std::cout << "HERE3" << std::endl;
    
    for (std::vector<std::pair<std::string, std::string>>::iterator it= this->layer_edges.begin(); it!=this->layer_edges.end(); ++it){
        std::cout << "HH" << std::endl; 
        int rank = this->layerMap[it->first]->output_shape.size();
        
        std::cout << "HERE2" << std::endl;     
        
        for (int i=0; i<rank; i++) this->layerMap[it->second]->input_shape.push_back(this->layerMap[it->first]->output_shape[i]);
        
        std::cout << "HERE3" << std::endl;
        
        this->layerMap[it->second]->compute_output_shapes();
        
        std::cout << "HERE4" << std::endl;
    }

    std::cout << "PARSER: Layer shapes built!" << std::endl;
}

void HDF5Parser::callLayerBuilders(){
        
        int i=0;
        int model_build_size = this->model_config["config"]["build_input_shape"].size();
        int model_build_size1 = this->model_config["config"]["layers"][0]["config"]["batch_input_shape"].size();

        if (model_build_size>0){
            for (int i=0; i<model_build_size-1; i++){
                nn_input_shape.push_back(this->model_config["config"]["build_input_shape"][i+1]);
            }  
        }

        if (model_build_size1>0){
            for (int i=0; i<model_build_size1 -1; i++){
                nn_input_shape.push_back(this->model_config["config"]["layers"][0]["config"]["batch_input_shape"][i+1]);
            }
        }

        for (auto it: this->model_config["config"]["layers"].items()){
            //TODO: Make the reading separate from the JSON
            this->layer_ids.push_back(it.value()["config"]["name"].get<std::string>());
            this->layerBuilderVector.push_back(this->BuilderMap[it.value()["class_name"].get<std::string>()]);
            this->layerBuilderVector[i]->create(it.value()["config"]["name"])->create_from_json(it.value(), it.value()["config"]["name"], this->layerMap); 
            i++;
        }
}

void HDF5Parser::buildEdges(){
    // Vector of factories is layerBuilderVector. Not tested yet for non-sequential model
    for (int i=0; i< this->layerBuilderVector.size()-1; ++i){
       this->layer_edges.push_back(std::make_pair(this->layer_ids[i], this->layer_ids[i+1])); 
    }

    /*for (int i=0; i<this->layer_edges.size(); i++){
        std::cout << this->layer_edges[i].first << " " << this->layer_edges[i].second << std::endl;
    }*/
}

json HDF5Parser::parseModelConfig(){
    
      H5File filefile = H5File( this->file_name, H5F_ACC_RDONLY );
      Group what = Group(filefile.openGroup("/"));
      Attribute attr= Attribute(what.openAttribute("model_config"));
      DataType type = DataType (attr.getDataType());
    
        std::string test;
        attr.read(type, test);
        
        // define parser callback
        json::parser_callback_t cb = [](int depth, json::parse_event_t event, json & parsed)
        {
            // skip object elements with key "Thumbnail"
            if (event == json::parse_event_t::key and parsed == json("Thumbnail"))
            {
                return false;
            }
            else
            {
                return true;
            }
        };
      
      std::stringstream ss;
      ss << test;
      
      json j_filtered = json::parse(ss, cb);

      //delete []test; // valgrind told me that test is not allocated at this point
      std::cout << "PARSER: Model config parsed!" << std::endl; 
      return j_filtered;
}

// PARSE FUNCTION
int HDF5Parser::parse()
{
  this->constructBuilderMap();
    
  try
   { 
      // Parse Model Config: 
      this->model_config= this->parseModelConfig();
      
      // Assign Config Builders:
      this->callLayerBuilders(); 
      
      // Parse Weights:
      std::cout << "LayerBuilders called!" << std::endl;

      // Populate the layer types:
      this->buildEdges();
      this->build_layer_shapes(); 

      std::cout << "Edges and shapes built!" << std::endl;
      this->parseWeights();
      
      std::cout<< "PARSER: Parsing complete!" <<std::endl;
    
      return 0;

   }  // end of try block

   catch( FileIException error )
   {
      return -1;
   }

   catch( DataSetIException error )
   {
      return -1;
   }

   catch( DataSpaceIException error )
   {
      return -1;
   }

   catch( AttributeIException error )
   {
      return -1;
   }
   
return 0; 
}

herr_t 
weights_callback(hid_t loc_id, const char *name, const H5L_info_t * linfo, void *opdata)
{

    hid_t group;
    hid_t status;
    H5O_info_t infobuf;
    struct opdataWeights *od = (struct opdataWeights *) opdata;
    group= H5Gopen2(loc_id, name, H5P_DEFAULT); // here group is actually a dset
    status = H5Oget_info_by_name(loc_id, name, &infobuf, H5P_DEFAULT);

    
    if (infobuf.type== H5O_TYPE_DATASET){
            
        // NEED TO PARSE EITHER WEIGHT OR BIAS 
        std::string s(name);
        std::string delimiter= "/";
        std::string layer_id;

        // Parsing matching layer id:
        size_t pos=0;
        while ((pos=s.find(delimiter)) != std::string::npos){
            layer_id= s.substr(0, pos);
            s.erase(0, pos+delimiter.length());
        }

        hid_t datatype, dataspace, rank; 
                hid_t dset = H5Dopen2(loc_id, name, H5P_DEFAULT);
                datatype= H5Dget_type(dset);
                dataspace = H5Dget_space(dset);
                rank= H5Sget_simple_extent_ndims(dataspace); 
                hsize_t dims[rank];
                H5Sget_simple_extent_dims(dataspace, dims, NULL);
                std::vector<unsigned int> tensor_dims;

                //Parsing dimensions for Tensor
                for (int i=0; i<rank; i++) {
                    tensor_dims.push_back((unsigned int)dims[i]);
                }

                Weight * wb = new Weight(layer_id, tensor_dims);
                Tensor<double>* T = wb->get_weight_tensor(); //assuming float

                float *rbuf;
                herr_t ret;
               
                // getting dimensions of flat rbuf
                // Dana TODO: Make a method that allows you to assign already flat 
                // array into tensor without having to index and given the size so
                int flat=1;
                for (int i=0; i<rank; i++){
                    flat*= dims[i];
                }

                rbuf= new float [flat];
                ret = H5Dread(dset, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, rbuf); 
                
                //flattened parsed weights are in rbuf
                //Dana TODO: Template that removes the need to do this

                switch(rank){
                    case 1:
                        {
                            for (int i=0; i<dims[0]; i++){
                                (*T)(i) = (double)rbuf[i];
                            }

                        break;
                        }
                    case 2:
                        {
                            for (int i=0; i<tensor_dims[0]; i++){
                                for (int j=0; j<tensor_dims[1]; j++){
                                    int idx= tensor_dims[1]*i+j;
                                    (*T)(i, j) = (double)rbuf[idx];
                                }
                            }
                            break;
                        }
                    case 3:
                        {
                            for (int i=0; i< tensor_dims[0]; i++){
                                for (int j=0; j<tensor_dims[1]; j++){
                                    for (int k=0; k<tensor_dims[2]; k++){
                                        int idx= tensor_dims[2]*tensor_dims[1]*i + tensor_dims[2]*j + k;
                                        (*T)(i, j, k)= (double)rbuf[idx];
                                    }
                                }
                            }

                            break;
                        }

                     case 4:
                        {
                            for (int i=0; i< tensor_dims[0]; i++){
                                for (int j=0; j<tensor_dims[1]; j++){
                                    for (int k=0; k<tensor_dims[2]; k++){
                                        for (int l=0; l<tensor_dims[3]; l++){
                                        int idx= tensor_dims[2]*tensor_dims[1]*tensor_dims[3]*i + tensor_dims[2]*tensor_dims[3]*j + k*tensor_dims[3] + l;
                                        (*T)(i, j, k, l)= (double)rbuf[idx];
                                        }
                                    }
                                }
                            }

                            break;
                        }



                    default:
                        break;
                }
                
                delete []rbuf; 

                // Create weights:
                
                if (s.compare("kernel:0")){ // it's a bias 
                    wb->identifier = wb->identifier.append("_b");
                    od->LM[layer_id]->b = wb;

                } else{ // it's a weight
                    wb->identifier=wb->identifier.append("_W");
                    od->LM[layer_id]->w = wb;
                }

                        
                ret= H5Dclose(dset); 
        }
    H5Gclose(group);
    
    return 0;
 }
