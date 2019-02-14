#!/usr/bin/env python3

#Python Prototype of teh full functioning of HDF5Parser.cpp
#Sarah Aguasvivas Manzano

#This code is open source but you gotta pay 15$ per use.
#J.K.

import h5py
import numpy as np

filename= '../data/weights.best.hdf5'
f= h5py.File(filename, 'r')

class Layer:
    def __init__(self, layer_type='Dense'):
        self.layer_type= layre_type
        self.Layers= []

    def loadWeights(node):
        self.W= np.array(node.data)

class NeuralNetwork:
    def __init__(self, numlayers=0):
        self.numlayers= numlayers
    def addLayer(self, layer_type, input_shape, output_shape, activation):
        self.Layers+= Layer(layer_type)

def funct(name, obj):
    print(name)
    if isinstance(obj, h5py.Dataset):
        myNN.addlayer()
        print(obj.shape)
        arr= np.empty(obj.shape)
        obj.read_direct(arr)
        print(arr)
        for key, val in obj.attrs.items():
              print(key, val)

def recursiveKeyPrinting(key, identifier):
    try:
        if str(key.name) in identifier:
            return
        else:
            identifier.append(str(key.name))
            if isinstance(key, h5py.Dataset):
                return recursiveKeyPrinting(key.parent, identifier)

            for kkey in key.keys():
                return recursiveKeyPrinting(key[kkey], identifier)

    except Exception as e:
        print(str(e))
        print(identifier)


if __name__=='__main__':
    myNN= NeuralNetwork()
    f.visititems(funct)

