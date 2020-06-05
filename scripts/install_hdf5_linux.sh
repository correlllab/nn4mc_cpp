#!/bin/bash

# Script taken from https://github.com/paulromano/install-scripts/blob/master/install-hdf5
set -e

version=$1
gnuversion=6.3
intelversion=17.0.4
mpidist=mpich
mpiversion=3.2
mpidir=/opt/$mpidist/$mpiversion

# Download tarball
if [[ ! -e hdf5-${version}.tar.bz2 ]]; then
    wget https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-${version:0:4}/hdf5-${version}/src/hdf5-${version}.tar.bz2
fi

# Extract and install gcc-compiled version
tar xvf hdf5-${version}.tar.bz2
cd hdf5-${version}
CC=gcc CXX=g++ FC=gfortran ./configure \
  --prefix=/opt/hdf5/${version}-gnu-${gnuversion} \
  --enable-fortran
make -j
make install
cd ..
rm -rf hdf5-${version}

# Extract and install Intel-compiled version
rm -rf hdf5-${version}
tar xvf hdf5-${version}.tar.bz2
cd hdf5-${version}
CC=icc CXX=icpc FC=ifort ./configure \
  --prefix=/opt/hdf5/${version}-intel-${intelversion} \
  --enable-fortran
make -j
make install
cd ..
rm -rf hdf5-${version}

# Extract and install gcc-compiled version
tar xvf hdf5-${version}.tar.bz2
cd hdf5-${version}
CC=${mpidir}-gnu-${gnuversion}/bin/mpicc FC=${mpidir}-gnu-${gnuversion}/bin/mpif90 \
  ./configure \
  --prefix=/opt/phdf5/${version}-${mpidist}-${mpiversion}-gnu-${gnuversion} \
  --enable-fortran --enable-parallel
make -j
make install
cd ..
rm -rf hdf5-${version}

# Extract and install Intel-compiled version
tar xvf hdf5-${version}.tar.bz2
cd hdf5-${version}
CC=${mpidir}-intel-${intelversion}/bin/mpicc FC=${mpidir}-intel-${intelversion}/bin/mpif90 \
  ./configure \
  --prefix=/opt/phdf5/${version}-${mpidist}-${mpiversion}-intel-${intelversion} \
  --enable-fortran --enable-parallel
make -j
make install
cd ..
