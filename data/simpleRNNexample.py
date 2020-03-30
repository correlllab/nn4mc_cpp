#!/usr/bin/env python
from __future__ import absolute_import, division, print_function, unicode_literals
import pandas as pd
import collections
import numpy as np
import matplotlib.pyplot as plt

import tensorflow as tf
from tensorflow.keras import layers

N = 1000
Tp = 800

t = np.arange(0,N)
x = np.sin(0.02*t)+2*np.random.rand(N)

df = pd.DataFrame(x)
df.head()

values=df.values
train,test = values[0:Tp,:], values[Tp:N,:]

step = 10
# add step elements into train and test
test = np.append(test,np.repeat(test[-1,],step))
train = np.append(train,np.repeat(train[-1,],step))

def convertToMatrix(data, step):
    X, Y =[], []
    for i in range(len(data)-step):
        d=i+step
        X.append(data[i:d,])
        Y.append(data[d,])
    return np.array(X), np.array(Y)

trainX,trainY = convertToMatrix(train,step)
testX, testY  = convertToMatrix(test,step)

trainX = np.reshape(trainX, (trainX.shape[0], 1, trainX.shape[1]))
testX = np.reshape(testX, (testX.shape[0], 1, testX.shape[1]))

model = tf.keras.Sequential([
            tf.keras.layers.LSTM(units=7, input_shape = (trainX.shape[1], trainX.shape[2])),
            tf.keras.layers.Dense(8, activation="relu"),
            tf.keras.layers.Dense(1)])

model.compile(loss='mean_squared_error', optimizer='rmsprop')
model.fit(trainX,trainY, epochs=100, batch_size=16, verbose=2)

print(model.summary())
print(model.layers[0].input_shape)

model.save('LSTM.hdf5')

trainPredict = model.predict(trainX)
testPredict= model.predict(testX)
predicted = np.concatenate((trainPredict,testPredict),axis=0)

trainScore = model.evaluate(trainX, trainY, verbose=0)
print(trainScore)
