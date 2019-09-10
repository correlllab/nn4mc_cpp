#include "datastructures/weights.h"
#include "datastructures/tensor.h"

Weight::Weight(std::string id, std::vector<unsigned int> shape)
{
	identifier = id;
	values = new Tensor<double>(shape); // Sarah: I'm not sure we need this; weights shouldn't occupy any space in mem; Tensor should
}

Weight::~Weight()
{
	//delete values; //Changed by Cooper 
    // this line causes parser to break
}

Tensor<double>* Weight::get_weight_tensor()
{
	return values;
}
