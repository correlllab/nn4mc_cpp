#include "datastructures/weights.h"
#include "datastructures/tensor.h"

Weight::Weight(std::string id, std::vector<unsigned int> shape)
{
	identifier = id;
	values = new Tensor<double>(shape); 
	// SARAH: I'm not sure we need this; weights shouldn't 
	// occupy any space in mem; Tensor should
}

Weight::~Weight()
{
    delete values; //Changed by Cooper 
}

Tensor<double>* Weight::get_weight_tensor()
{
    try{
       return values;
    } catch (int e){
      std::cout << "exception n " << e <<  " while reading weight" << std::endl;
    }
}
