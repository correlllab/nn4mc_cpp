#!/bin/bash

echo "Installing dependencies for nn4mc"
echo 'export NN4MC_HOME="$PWD"' >> ~/.bashrc
echo 'export PATH=$PATH:/usr/include/hdf5/serial' >> ~/.bashrc
echo 'export PATH=$PATH:/usr/share/doc/' >> ~/.bashrc
source ~/.bashrc
wget http://h5cpp.org/download/hdf5-1.10.4.tar.gz
tar -xvzf tar -xvzf hdf5-1.10.4.tar.gz
cd hdf5-1.10.4 && ./configure --prefix=/usr/local && make -j2 && sudo make install
wget http://h5cpp.org/download/h5cpp_1.10.4.1_amd64.deb
sudo dpkg -i h5cpp_1.10.4.1_amd64.deb
cd /usr/lib/x86_64-linux-gnu
sudo ln -s libhdf5_serial.so.8.0.2 libhdf5.so
sudo ln -s libhdf5_serial_hl.so.8.0.2 libhdf5_hl.so
sudo apt-get install libboost-all-dev
cd $NN4MC_HOME/lib
git clone https://github.com/nlohmann/json nlohmann_json
cd $NN4MC_HOME

