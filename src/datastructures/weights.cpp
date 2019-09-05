#include "datastructures/weights.h"
#include "datastructures/tensor.h"

Weight::Weight(std::string id, std::vector<unsigned int> shape)
{
	identifier = id;
	values = new Tensor<double>(shape);
}

Weight::~Weight()
{
	//delete values; //Changed by Cooper 
    // deleting this causes parser to break
}

Tensor<double>* Weight::get_weight_tensor()
{
	return values;
}
