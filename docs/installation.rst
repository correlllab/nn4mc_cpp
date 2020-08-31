Installation Guide
===================

To get setup with `nn4mc` we first need the following dependencies:

- HDF5, pickle or the preferred library depending on the source
- Boost
- g++
- cmake
- json


Get all Dependencies in One Step
--------------------------------

Go to the scripts/ folder and type:

Linux
^^^^^

::

./scripts/setup_linux_mint.sh


MacOS
^^^^^

::

./scripts/setup_macos.sh


HDF5
----

Installing HDF5 >=1.10.4 from conda
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you are a conda user, the simplest way to obtain a version of hdf5 that is stable across platforms is using conda. The command to type is:

::

     conda install -c anaconda hdf5


Installing HDF5 < 1.8.16 from HDF5 Group
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This is a more manual installation. This installation will lead a very stable Linux parsing in HDF5, but leads to some compatibility problems for MacOS. Go to this website: `HDF5 Group <https://www.hdfgroup.org/downloads/hdf5>`_ or type:

::

 wget http://h5cpp.org/download/hdf5-1.10.4.tar.gz

Untar the file as in :

::

 tar -xvzf hdf5-1.10.4.tar.gz

Configure the files as in:

::

 cd hdf5-1.10.4 && ./configure --prefix=/usr/local && make -j2 && sudo make install

Then download the deb files:

::

 wget http://h5cpp.org/download/h5cpp_1.10.4.1_amd64.deb

Then type:

::

 sudo dpkg -i h5cpp_1.10.4.1_amd64.deb

::

    cd /usr/lib/x86_64-linux-gnu

::

    sudo ln -s libhdf5_serial.so.8.0.2 libhdf5.so
    sudo ln -s libhdf5_serial_hl.so.8.0.2 libhdf5_hl.so


Installing the boost library
----------------------------

From Linux:

::

    sudo apt-get install libboost-all-dev

From MacOS:

::

    brew install boost

Installing nlohmann/json
------------------------

Go back to `nn4mc` and go to the `lib/` folder.

::

    git clone https://github.com/nlohmann/json nlohmann_json
