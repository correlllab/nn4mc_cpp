#include "neural_network.h"

void buildNN()
{
   
Conv1D > = buildConv1D(>, <%BIAS_NAME>, >, <%STRIDE_SIZE>, >, <%OUTPUT_CHANNELS>, >);


Dense > = buildDense(>, <%BIAS_NAME>, >, <%OUTPUT_SIZE>);

 <%BUILD_FUNCTION>
}

void fwdNN(<%WEIGHT_DATATYPE>* input, <%WEIGHT_DATATYPE>* output)
{
    <%FWD_FUNCTION>
}
