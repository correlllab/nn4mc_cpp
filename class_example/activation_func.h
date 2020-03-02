
#ifndef __ACTIVATION_H__
#define __ACTIVATION_H__

float activate(float input, int output_shape, int type);

float sigmoid(float input);

float softplus(float input);

float softsign(float input);

float hard_sigmoid(float input);

float exponential(float input);

float relu(float input);

float hyper_tan(float input);

float softmax(float input, int output_shape);

#endif
