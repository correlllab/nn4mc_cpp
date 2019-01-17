#!/usr/bin/env python3

from keras.models import load_model
from keras.preprocessing import image
import numpy as np

sample= np.ones((50, 2))
sample= np.reshape(sample, (1, 50, 2))
model= load_model('../data/weights.best.hdf5')

model.compile(optimizer='rmsprop', loss= 'mse')

prediction = model.predict(sample)
print(prediction)

