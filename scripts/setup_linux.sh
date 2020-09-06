#!/bin/bash
echo "Installing dependencies for nn4mc"
sudo apt-get update # updating sudo apt-get 
sudo apt-get install libhdf5-serial-dev # installing hdf5
sudo apt-get install libboost-all-dev # installing boost library
cd lib
git clone https://github.com/nlohmann/json nlohmann_json # cloning nlohmann json wrapper
cd ..
sudo apt install cmake # just in case they don't have it; won't install if they have it
sudo apt-get install build-essential  
#sudo apt-get install manpages-dev
mkdir build && cd build
cmake ..
make






