#! /bin/bash

#TODO: Make this file distribution agnostic
#TODO: Error handling in case libgflags(or any package) is not installed

sudo apt-get update
sudo apt-get -y install make
sudo apt-get --yes --force-yes install g++
sudo apt-get --yes --force-yes install wget
sudo apt-get --yes --force-yes install git
sudo apt-get --yes --force-yes install yagiuda
sudo apt-get --yes --force-yes install cppcheck
sudo apt-get --yes --force-yes install doxygen

# glags - a library that handles command line flags processing. You can compile rocksdb library even if you don't have gflags installed.
sudo apt-get --yes --force-yes install libgflags-dev
sudo apt-get --yes --force-yes install libsnappy-dev
sudo apt-get --yes --force-yes install zlib1g-dev
sudo apt-get --yes --force-yes install libbz2-dev
