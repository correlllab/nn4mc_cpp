#!/bin/bash

echo "Installing dependencies for nn4mc"
echo 'export NN4MC_HOME="$PWD"' >> ~/.bashrc
#sudo ln -s libhdf5_serial.so.8.0.2 libhdf5.so
#sudo ln -s libhdf5_serial_hl.so.8.0.2 libhdf5_hl.so
sudo apt-get install libhdf5-dev
sudo apt-get install libboost-all-dev
cd $NN4MC_HOME/lib
git clone https://github.com/nlohmann/json nlohmann_json
cd $NN4MC_HOME

