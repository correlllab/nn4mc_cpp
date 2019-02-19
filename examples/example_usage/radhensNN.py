#!/usr/bin/env python3

from keras.models import load_model
from keras.preprocessing import image
import numpy as np
import keras.backend as K
import sys

sample= np.ones((50, 2))
sample= np.reshape(sample, (1, 50, 2))
model = load_model('../data/weights.best.hdf5')

model.compile(optimizer='rmsprop', loss= 'mse')

inp= model.input
outputs= [layer.output for layer in model.layers]
functors= [K.function([inp, K.learning_phase()], [out]) for out in outputs]

prediction = model.predict(sample)

print([func([sample, sys.argv[1]]) for func in functors])

print(prediction)

