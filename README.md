# Kinetic Advanced Object Storage (KAOS)
KAOS is a Linux userspace application that performs the functions of a Kinetic Device, which is a network attached storage device that communicates using an object interface (using commands such as put, get, and delete). The Kinetic protocol was created by Seagate and is now an open source collaborative project managed through the Linux Foundation.

## License
Please see COPYING file.

## Build Instructions

### Native Build on a Debian System
1.  Perform a git clone (or copy) of the kinetic project on a Debian system
2.  Change directories into the kinetic directory
3.  Run tools/install-packages.sh to install needed Debian packages
4.  Run make dependencies to download and build needed libraries
5.  Run make all (to build kaos application and associated unit tests)

### Make Options
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
* make shush - this is KAOS, we don't shush here (google it if this make no sense)
* make test - will build the unit tests (which uses google test)

## Running KAOS on a Debian System
In addition to the KAOS executable, several configuration files must be installed for the application to run correctly.  The best way to do that is to create a Debian package and install it.  A Debian package is created by performing a "make all" or "make package" if the application is already compiled.  The package "wdc-kinetic.deb" will be created in the kinetic/build/package directory.
*  To install the package, run "sudo dpkg --install wdc-kinetic.deb"
*  To uninstall a previously installed version of the package, run "sudo dpkg --remove wdc-kinetic"
*  To start the application, run "sudo /etc/init.d/kaos start"
*  To stop the application, run "sudo /etc/init.d/kaos stop"
*  To restart the application with default settings and an empty database, run "sudo /etc/init.d/kaos clean-restart".  This is useful prior to running the conformance test, which expects settings to have their default values.
*  KAOS events are stored in /var/log/kaos.log
*  The logging level is specified in the /etc/default/kaos configuration file

## Check-in Requirements
1.  make conform must be run with its changes applied to the files to be checked in
2.  make check must be run without any warnings being reported
3.  make all must be run without any warnings being reported
3.  make run-tests must be run with all the unit tests passing successfully
4.  The Kinetic conformance test must be run with all of its tests passing successfully
