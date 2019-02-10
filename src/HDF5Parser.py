#!/usr/bin/env python3

#Python Prototype of teh full functioning of HDF5Parser.cpp
#Sarah Aguasvivas Manzano

#This code is open source but you gotta pay 15$ per use.
#J.K.

import h5py
import numpy as np

def print_attrs(name, obj):
    print(name)
    for key, val in obj.attrs.items():
        print(key, val)


if __name__=="__main__":
    filename= '../data/weights.best.hdf5'
    f= h5py.File(filename, 'r')
    f.visititems(print_attrs)
