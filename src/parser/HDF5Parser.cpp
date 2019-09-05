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

    this->BuilderMap["Conv1D"]= new Conv1DFactory();
    this->BuilderMap["Conv2D"]= new Conv2DFactory();
    this->BuilderMap["Flatten"]= new FlattenFactory();
    this->BuilderMap["Dense"]= new DenseFactory();
    this->BuilderMap["MaxPooling1D"]= new MaxPooling1DFactory();
    this->BuilderMap["MaxPooling2D"]= new MaxPooling2DFactory();
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
      herr_t idx=  H5Lvisit(group.getId(), H5_INDEX_NAME, H5_ITER_INC,  weights_callback, (void*)&od_weights);
      this->layerMap= od_weights.LM;

}

NeuralNetwork* HDF5Parser::constructNeuralNetwork(){
    NeuralNetwork* NN = new NeuralNetwork();
    Layer* l= new InputLayer("input_1");
    NN->addLayer(l);
    for (auto it = this->layerMap.begin(); it!=this->layerMap.end(); it++){  
        NN->addLayer(it->second); // adding layers
        NN->addEdge(l, it->second);
        l= it->second;
    }

    cout<< "PARSER: Neural Network Nodes and Edges Built!"<<endl;
    return NN;
}

void HDF5Parser::callLayerBuilders(){
        int i=0; 
        for (auto it: this->model_config["config"]["layers"].items()){
            //cout<< it.key() << " | " << it.value() << endl;
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
}

json HDF5Parser::parseModelConfig(){
      
    // TODO: Also parse the size of this attribute so I don't have to hard code 
      H5File filefile = H5File( this->file_name, H5F_ACC_RDONLY );
      Group what = Group(filefile.openGroup("/"));
      Attribute attr= Attribute(what.openAttribute("model_config"));
      DataType type = DataType (attr.getDataType());
      char* test= new char[1000000]; 
      attr.read(type, &test);
      std::string str(test);
           
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
      ss << str;

      json j_filtered = json::parse(ss, cb);

      delete []test; // valgrind told me that test is not allocated at this point
      
      return j_filtered;
}


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
                
                Tensor<double> T(tensor_dims); //assuming float
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
                                T(i) = (double)rbuf[i];
                            }

                        break;
                        }
                    case 2:
                        {
                            for (int i=0; i<tensor_dims[0]; i++){
                                for (int j=0; j<tensor_dims[1]; j++){
                                    int idx= tensor_dims[1]*i+j;
                                    T(i, j) = (double)rbuf[idx];
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
                                        T(i, j, k)= (double)rbuf[idx];
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
                Weight wb(layer_id, tensor_dims);
                wb.values= &T;
                
                if (s.compare("kernel:0")){ // it's a weight
                    od->LM[layer_id]->w = &wb;

                } else{ // it's a bias
                    od->LM[layer_id]->b = &wb;
                }

                ret= H5Dclose(dset); 
        }

    H5Gclose(group);

    return 0;
 }
