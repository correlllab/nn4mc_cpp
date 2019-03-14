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
#include "HDF5Parser.h"
// Callback functions:
extern "C" herr_t weights_callback(hid_t loc_id, const char *name, const H5L_info_t * linfo, void *opdata);
extern "C" herr_t network_callback(hid_t loc_id, const char *name, const H5L_info_t * linfo, void *opdata);

void HDF5Parser::constructBuilderMap(){

    this->BuilderMap["conv1d"]= new Conv1DFactory();
    this->BuilderMap["conv2d"]= new Conv2DFactory();
    this->BuilderMap["flatten"]= new FlattenFactory();
    this->BuilderMap["dense"]= new DenseFactory();
    this->BuilderMap["maxpooling1d"]= new MaxPooling1DFactory();
    this->BuilderMap["maxpooling2d"]= new MaxPooling2DFactory();
    this->BuilderMap["lstm"]= new LSTMFactory();
    this->BuilderMap["gru"]= new GRUFactory();
    this->BuilderMap["simplernn"]= new SimpleRNNFactory();

}

void HDF5Parser::parseNeuralNetworkArchitecture(){

    const H5std_string FILE_NAME( this->file_name );
    H5File file = H5File( FILE_NAME, H5F_ACC_RDONLY );
    Group group = Group( file.openGroup( "model_weights" ));
    
    struct opdata odnn; // local var
    // Copying existing variables from object attribute:
    odnn.BM = this->BuilderMap;
    std::copy(this->layer_ids.begin(), this->layer_ids.end(), std::back_inserter(odnn.layer_ids));
    std::copy(this->layer_edges.begin(), this->layer_edges.end(), std::back_inserter(odnn.layer_edges));
    std::copy(this->layerBuilderVector.begin(), this->layerBuilderVector.end(), std::back_inserter(odnn.lBV));
    
    // This is what calls the callback function:
    herr_t rat= H5Literate(group.getId(), H5_INDEX_NAME, H5_ITER_INC, NULL, network_callback, (void*)&odnn);
    // My vector of factories if layerBuilderVector()    
    std::copy(odnn.lBV.begin(), odnn.lBV.end(), std::back_inserter(this->layerBuilderVector));
    std::copy(odnn.layer_edges.begin(), odnn.layer_edges.end(), std::back_inserter(this->layer_edges));
    std::copy(odnn.layer_ids.begin(), odnn.layer_ids.end(), std::back_inserter(this->layer_ids));

    for (int i=0; i<this->layerBuilderVector.size(); ++i) {
          cout<< this->layer_ids[i]<<endl;
    }
}
void HDF5Parser::callLayerBuilders(){
        int i=0; 
        for (auto it: this->model_config["config"]["layers"].items()){
            //cout<< it.key() << " | " << it.value() << endl;
            this->layerBuilderVector[i]->create()->create_from_json(it.value(), it.value()["config"]["name"]); 
            //cout << endl;
            i++;
        }
   
}

void HDF5Parser::buildEdges(){
    // Vector of factories is layerBuilderVector
    // Assuming Sequential:
    for (int i=0; i< this->layerBuilderVector.size()-1; ++i){
       this->layer_edges.push_back(std::make_pair(this->layer_ids[i], this->layer_ids[i+1])); 
    }

    for (int i=0; i<this->layer_edges.size(); ++i){
        cout<< this->layer_edges[i].first << " "<< this->layer_edges[i].second <<endl;
    }
}

json HDF5Parser::parseModelConfig(){
      // TODO: Also parse the size of this attribute so I don't have to hard code 
      char* test= new char[1000000]; 
      cout<< "Attributes:"<<endl;
      H5File *filefile = new H5File( this->file_name, H5F_ACC_RDONLY );
      Group *what = new Group(filefile->openGroup("/"));
      Attribute *attr= new Attribute(what->openAttribute("model_config"));
      DataType *type = new DataType (attr-> getDataType());
      attr->read(*type, &test);
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
      ss<< str;

      json j_filtered= json::parse(ss, cb);
      std::cout<<j_filtered["class_name"]<<endl;

      delete type;
      delete attr;
      delete what;
      delete filefile;
      return j_filtered;
}


int HDF5Parser::parse()
{
 
  this->constructBuilderMap();
  const H5std_string FILE_NAME( this->file_name );
  
  try
   {
      Exception::dontPrint();
      H5File file = H5File( FILE_NAME, H5F_ACC_RDONLY );
      Group group = Group( file.openGroup( "model_weights" ));
     
      this->parseNeuralNetworkArchitecture();
      this->buildEdges();
        
      cerr << endl << "Parsing weights:" << endl;
      herr_t idx=  H5Lvisit(group.getId(), H5_INDEX_NAME, H5_ITER_INC,  weights_callback, NULL);
      cerr << endl;
   
      //Parsing Model_Config:
      this->model_config= this->parseModelConfig();
      this->callLayerBuilders(); 

    return 0;

   }  // end of try block

   // catch failure caused by the H5File operations
   catch( FileIException error )
   {
      //error.printError();
      return -1;
   }

   // catch failure caused by the DataSet operations
   catch( DataSetIException error )
   {
      //error.printError();
      return -1;
   }

   // catch failure caused by the DataSpace operations
   catch( DataSpaceIException error )
   {
      //error.printError();
      return -1;
   }

   // catch failure caused by the Attribute operations
   catch( AttributeIException error )
   {
      //error.printError();
      return -1;
   }
return 0; 
}

herr_t
network_callback(hid_t loc_id, const char *name, const H5L_info_t *linfo, void *operator_data)
{

    // Neural Network Parsing:
    struct opdata *od = (struct opdata *) operator_data;
    
    std::string s(name);
    std::string delimiter= "_";
    std::string token;
    od->layer_ids.push_back(s);  
    size_t pos=0;
    while ((pos=s.find(delimiter)) != std::string::npos){
        token= s.substr(0, pos);
        s.erase(0, pos+delimiter.length());
    }
    od->lBV.push_back(od->BM[token]);
       // token is the layer type
    return 0;
}

herr_t 
weights_callback(hid_t loc_id, const char *name, const H5L_info_t * linfo, void *opdata)
{
    hid_t group;
    hid_t status;
    hid_t attribute;
    H5O_info_t infobuf;
    
    group= H5Gopen2(loc_id, name, H5P_DEFAULT); // here group is actually a dset
    status = H5Oget_info_by_name(loc_id, name, &infobuf, H5P_DEFAULT);

    switch(infobuf.type){
        case H5O_TYPE_GROUP:{
            cout << "Group : " << name << endl;
            break;
                            }
        case H5O_TYPE_DATASET:{

            cout<< "Dataset: " << name;
            hid_t datatype, dataspace, cclass, order, size, rank; 
            hid_t dset = H5Dopen2(loc_id, name, H5P_DEFAULT);
            datatype= H5Dget_type(dset);
            cclass = H5Tget_class(datatype); 
            size= H5Tget_size(datatype);
            dataspace = H5Dget_space(dset);
            rank= H5Sget_simple_extent_ndims(dataspace); 
            hsize_t dims[rank];
            H5Sget_simple_extent_dims(dataspace, dims, NULL);
            std::vector<unsigned int> tensor_dims;
            
            cout<<endl<< "Dimensions of the dataset:" <<endl;
            for (int i=0; i<rank; i++) {
                cout<< dims[i] << "  ";            
                tensor_dims.push_back((unsigned int)dims[i]);
            }
            cout<<endl;
             
            // TODO: handle the data type specific to the output type, 
            // not only <double>
            Tensor<float> T(tensor_dims); 
            float *rbuf;
            herr_t ret;
            int flat=1;
            for (int i=0; i<rank; i++){
                flat*= dims[i];
            }
            rbuf= new float [flat];
            ret = H5Dread(dset, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, rbuf); 
           
            //flattened parsed weights are in rbuf
            switch(rank){
                case 1:
                    {
                        for (int i=0; i<dims[0]; i++){
                            T(i) = rbuf[i];
                        }

                    break;
                    }
                case 2:
                    {
                        for (int i=0; i<tensor_dims[0]; i++){
                            for (int j=0; j<tensor_dims[1]; j++){
                                int idx= tensor_dims[1]*i+j;
                                T(i, j) = rbuf[idx];
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
                                    T(i, j, k)= rbuf[idx];
                                }
                            }
                        }

                        break;
                    }


                default:
                    break;

            }
            //link weights and biases to layer object
            cout<<endl;
              
            ret= H5Dclose(dset); 
            
            //no toki:
            break;
                              }
        case H5O_TYPE_NAMED_DATATYPE:{
            cout<< "DataType: " << name <<endl;
            break;
                }
        default:{
            cout<< "Unknown"<<endl;
            
                }       
    }
             
    H5Gclose(group);

    return 0;
 }
