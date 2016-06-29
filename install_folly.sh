#!/bin/sh

sudo apt-get install \
    automake \
    autoconf \
    autoconf-archive \
    libtool \
    libboost-all-dev \
    libevent-dev \
    libdouble-conversion-dev \
    libgoogle-glog-dev \
    libgflags-dev \
    liblz4-dev \
    liblzma-dev \
    libsnappy-dev \
    make \
    zlib1g-dev \
    binutils-dev \
    libjemalloc-dev \
    libssl-dev \
    libiberty-dev

cd ~
git clone https://github.com/facebook/folly.git
cd folly; cd folly

autoreconf -ivf
./configure
make
make check
sudo make install
