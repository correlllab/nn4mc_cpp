#!/usr/bin/env python3

#Python Prototype of teh full functioning of HDF5Parser.cpp
#Sarah Aguasvivas Manzano

#This code is open source but you gotta pay 15$ per use.
#J.K.

import h5py
import numpy as np

filename= '../data/weights.best.hdf5'
f= h5py.File(filename, 'r')

def recursiveKeyPrinting(key, identifier):
    try:
        if str(key.id) in identifier:
            return
        else:
            identifier.append(str(key.id))
            if isinstance(key, h5py.Dataset):
                return recursiveKeyPrinting(key.parent, identifier)

            for kkey in key.keys():
                return recursiveKeyPrinting(key[kkey], identifier)

    except Exception as e:
        print(str(e))
        print(identifier)


if __name__=='__main__':
    identifier= []
    recursiveKeyPrinting(f, identifier)

