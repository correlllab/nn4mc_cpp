#!/usr/bin/env python3
import sys
import h5py
import numpy as np
from keras import backend as K
from keras.models import load_model
import keras.losses
from keras.layers import Activation

def custom_loss(y_true, y_pred):
    r_hat = y_pred[:, 1]
    r_true = y_true[:, 1]
    th_hat= y_pred[:, 0]
    th_true= y_true[:, 0]
    coseno= K.cos(th_hat-th_true)
    return K.abs(r_true**2 + r_hat**2 - 2*r_true*r_hat*coseno)

def custom_activation(x):
    return K.tanh(x)

keras.losses.custom_loss=custom_loss
keras.activations.custom_activation= custom_activation

model= load_model(sys.argv[1])

textFile= open("wr.txt", "w")
layer= int(sys.argv[2])

print(model.summary())

print("layer config:")
print(model.layers[layer].get_config())

input_size= model.layers[layer].input_shape

print("input_size: ", input_size)
first_input= model.layers[0].input_shape


try:
    weights = model.layers[layer].get_weights()[0] # weights

    print("weights shape: ", weights.shape)

    biases = model.layers[layer].get_weights()[1] # biases

    print("biases shape: ", biases.shape)

    strWeights= str(list(weights))
    strBiases= str(list(biases))

    strWeights= strWeights.replace('[', '{')
    strWeights= strWeights.replace(']', '}')
    strWeights= strWeights.replace('dtype=float32),', '')
    strWeights= strWeights.replace('array(', '')
    strWeights= strWeights.replace(', dtype=float32)', '')

    textFile.write(strWeights)
    strBiases= strBiases.replace('[', '{')
    strBiases= strBiases.replace(']', '}')

    #print(strBiases)
except:
    pass
inp= model.input
outputs = [layer.output for layer in model.layers]          # all layer outputs
functors = [K.function([inp] , [out]) for out in outputs]   # evaluation function

test = np.ones((1, 4 , 1))
layer_outs = [func([test]) for func in functors]
print("layer outputs:")
print(layer_outs[layer])

output= model.predict(test)
print(output)
print(layer_outs[-1])
