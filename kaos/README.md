# Kinetic Advanced Object Storage
A Linux userspace application that performs the functions of a Kinetic Device, which is a network attached storage device that communicates using an object interface (using commands such as put, get, and delete). The Kinetic protocol was created by Seagate and is now an open source collaborative project managed through of the Linux Foundation.

##Make Options
* make kaos - will build the object storage application
* make proto - will create protocol buffer source files from the proto config files
* make check - will run google lint to check for suspicious software usage
* make conform - will run cstyle and covert the code to adhere to the chosen style conventions
* make test - will build the unit tests (which uses google test)
* make runTests - will run the unit tests (which takes about a minute)
* make clean - will delete all the kaos and unit test build artifacts
* make kaboom - this is KAOS, we don't make kaboom here
