#!/bin/bash

echo "Installing dependencies for nn4mc"
sudo apt-get install libhdf5-dev
conda install -c anaconda hdf5
sudo apt-get install libboost-all-dev
cd ../lib
git clone https://github.com/nlohmann/json nlohmann_json
cd ..

