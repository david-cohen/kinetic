# Kinetic Advanced Object Storage (KAOS)
A Linux userspace application that performs the functions of a Kinetic Device, which is a network attached storage device that communicates using an object interface (using commands such as put, get, and delete). The Kinetic protocol was created by Seagate and is now an open source collaborative project managed through the Linux Foundation.

##Build Instructions

###Native Build on a Debian System
1.  git clone (or copy) koas project on debian system
2.  change directories into the kaos directory
3.  run tools/install_packages.sh (to install needed debian packages)
4.  run make CROSS_COMPILER=false dependancies (to download and build needed libraries)
5.  run make CROSS_COMPILER=false all (to build kaos application and asssoicated unit tests)

###Cross Compiled Build on a Debian System
1.  git clone (or copy) koas project on debian system
2.  change directories into the kaos directory
3.  run tools/install_packages.sh (to install needed debian packages)
4.  run make cross-compiler (to install the cross compiler tool chain)
5.  source ~/.bashrc (to use newly added environment variables)
6.  run make CROSS_COMPILER=true dependancies (to download and build needed libraries)
7.  run make CROSS_COMPILER=true all (to build kaos application and asssoicated unit tests)

##Make Options
* make all - will perform a clean build of the Kinetic object storage application and associated tests
* make kaos - will build the Kinetic object storage application
* make proto - will create protocol buffer source files from the proto config files
* make check - will run google lint to check for suspicious software usage
* make conform - will run cstyle and covert the code to adhere to the chosen style conventions
* make test - will build the unit tests (which uses google test)
* make run-tests - will run the unit tests (which takes about a minute)
* make clean - will delete all the kaos and unit test build artifacts
* make kaboom - this is KAOS, we don't make kaboom here
