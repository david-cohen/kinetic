# Kinetic Advanced Object Storage (KAOS)
A Linux userspace application that performs the functions of a Kinetic Device, which is a network attached storage device that communicates using an object interface (using commands such as put, get, and delete). The Kinetic protocol was created by Seagate and is now an open source collaborative project managed through the Linux Foundation.

##Build Instructions

###Native Build on a Debian System
1.  git clone (or copy) kaos project on Debian system
2.  change directories into the kaos directory
3.  run tools/install-packages.sh (to install needed Debian packages)
4.  run make dependencies (to download and build needed libraries)
5.  run make all (to build kaos application and associated unit tests)

###Make Options
* make all - will perform a clean build of the kaos application, unit tests, documentation, and Debian package
* make check - will run google lint to check for suspicious software usage
* make clean - will delete all the kaos and unit test build artifacts
* make conform - will run astyle and covert the code to adhere to the chosen style conventions
* make dependencies - will download and build the needed libraries
* make doxygen - will create documentation from annotations in the source code
* make kaos - will build the Kinetic object storage application
* make package - will create a Debian package containing the application and supporting files
* make proto - will create protocol buffer source files from the proto config files
* make run-tests - will run the unit tests (which takes about a minute)
* make shush - this is KAOS, we don't shush here
* make test - will build the unit tests (which uses google test)

##Check-in Requirements
1.  make conform must be run with its changes applied to the files to be checked in
2.  make check must be run without any warnings being reported
3.  make all must be run without any warnings being reported
3.  make run-tests must be run with all the unit tests passing successfully
4.  The Kinetic conformance test must be run with all of its tests passing successfully
