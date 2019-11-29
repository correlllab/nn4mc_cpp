
#include "activation_func.h"
#include <math.h>

float sigmoid(float input)
{
  input = exp(input)/(exp(input) + 1);

  return input;
}

float softplus(float input)
{
  input = log(exp(input)) + 1);

  return input;
}

float softsign(float input)
{
  input = input / (abs(input) + 1);

  return input;
}

float hard_sigmoid(float input)
{
  if (input < -2.5){
      input = 0.0;
  } else if (input > 2.5){
      input = 1.0;
  } else{
      input = 0.2*h[i] + 0.5;
  }

  return input;
}

float exponential(float input)
{
  input = (float)expf((float)input);

  return input
}

float relu(float input)
{
  input = max(input, 0.0);

  return input;
}

float hyper_tan(float input)
{
  input = tanh(input);

  return input;
}

float softmax(float input, int output_shape)
{
  float sum_exp = 0.0;
  for (int i=0; i<output_shape; i++){
      sum_exp+= expf(input);
  }
  for (int i=0; i<output_shape;i++){
      float calc = expf(input) / sum_exp;
      if isnan(calc){
          input = 1.0;
      } else input = (float)(expf(input) / sum_exp);
  }

  return input;
}

float activate(float input, int output_shape, char type)
{
  if (type == 0x00)
    return softmax(input, output_shape);

  /* else if (type == 0x02)
    return elu(); */

  /* else if (type == 0x03)
    return selu(); */

  else if (type == 0x04)
    return softplus(input);

  else if (type == 0x05)
    return softsign(input);

  else if (type == 0x06)
    return relu(input);

  else if (type == 0x07)
    return hyper_tan(input);

  else if (type == 0x08)
    return sigmoid(input);

  else if (type == 0x09)
    return hard_sigmoid(input);

  else if (type == 0xA)
    return exponential(input);

  /* else if (type == 0xC)
    return custom(input); */

  return input;
}
