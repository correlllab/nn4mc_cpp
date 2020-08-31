#!/bin/bash
echo "Installing dependencies for nn4mc"
sudo apt-get update
sudo apt-get install libhdf5-serial-deva ccache libopenmpi-dev
sudo apt-get install libboost-all-dev
cd lib
git clone https://github.com/nlohmann/json nlohmann_json
cd ..
sudo apt install cmake
sudo apt-get install build-essential
sudo apt-get install manpages-dev
sudo apt-get instalal hdf5-tools
mkdir build && cd build
cmake ..
make






