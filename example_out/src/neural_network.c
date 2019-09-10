

const float * fwdNN(const float* data)
{
  
        struct Conv1D layer1 = buildConv1D(&conv1_weight[0][0][0], conv1_bias, 5, <%STRIDE_SIZE>, 1,  <%INPUT_SHAPE_1>, 1);

        struct Dense layer2 = buildDense(&dense_weight[0][0], dense_bias, , <%OUTPUT_SIZE>, 'l');
 

   
        data = fwdConv1D(layer1, data);

        data = fwdDense(layer2, data);
 

    return data;
}
