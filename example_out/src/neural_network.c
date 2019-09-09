#include "neural_network.h"

void buildNN()
{
    // how can we return the series of structs, volatile structs? Maybe build in fwd function
   
struct Conv1D layer1 = buildConv1D(&conv1_weight[0][0][0], conv1_bias, 5, <%STRIDE_SIZE>, ,  <%INPUT_SHAPE_1>, );

struct Dense layer2 = buildDense(&dense_weight[0][0], dense_bias, 1, <%OUTPUT_SIZE>, );
 
}

<%WEIGHT_DATATYPE> * fwdNN(<%WEIGHT_DATATYPE>* data)
{
 // <$BUILD_FUNCTION>

   
data = fwdConv1D(layer1, data);

data = fwdDense(layer2, data);
 

    return data;
}
