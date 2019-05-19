#include "datastructures/weights.h"
#include "datastructures/tensor.h"
// #include "../../include/datastructures/weights.h"
// #include "../../include/datastructures/tensor.h"

Weight::Weight(std::string id, std::vector<unsigned int> shape)
{
	identifier = id;
	values = new Tensor<double>(shape);
}

Weight::~Weight()
{
//	delete values;
}

Tensor<double>* Weight::get_weight_tensor()
{
	return values;
}
