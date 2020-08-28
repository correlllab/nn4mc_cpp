#include "datastructures/weights.h"
#include "datastructures/tensor.h"

Weight::Weight(std::string id, std::vector<unsigned int> shape)
{
	this->identifier = id;
	this->values = new Tensor<double>(shape); 
}

Weight::~Weight()
{
    //delete values; //Changed by Cooper 
}

Tensor<double>* Weight::get_weight_tensor()
{ 
     try{
     	return this->values;
     } catch (int e){
    	std::cout << "exception n " << e <<  " while reading weight" << std::endl; 
     }
}
