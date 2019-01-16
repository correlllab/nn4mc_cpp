#!/usr/bin/env python3

import h5py
import numpy as np
from keras.models import load_model

f= h5py.File('weights.best.hdf5', 'r')
model= load_model('weights.best.hdf5')

print(model.summary())

weights= model.layers[0].get_weights()[0] #weights
biases= model.layers[0].get_weights()[1] #biases

strWeights= str(weights)
strBiases= str(biases)

strWeights= strWeights.replace('[', '{')
strWeights= strWeights.replace(']', '}')
strWeights= strWeights.replace(' ', ',')

print(strWeights)

strBiases= strBiases.replace('[', '{')
strBiases= strBiases.replace(']', '}')
strBiases= strBiases.replace(' ', ',')
print()
print(strBiases)

print(model.layers[0])
print("Keys: %s" % f.keys())
a_group_key= list(f.keys())[0]

data= list(f[a_group_key])
print(data)

