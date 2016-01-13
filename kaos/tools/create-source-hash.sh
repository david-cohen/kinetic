#! /bin/bash
# Copyright (c) [2016] Western Digital Technologies, Inc. All rights reserved.
# The source hash is created by hashing the hashes of the Makefile, the application
# source files (cpp files) and application include files.  The individual file hashes
# are kept in the hashes.txt file, which is deleted at the end of the operation.  The
# source hash is maintained in the SystemConfig.cpp file, so it is touched to force
# its recompile to obtain the lastest hash.

sha1sum ./Makefile > hashes.txt
sha1sum ./src/*.cpp >> hashes.txt
sha1sum ./include/*.hpp >> hashes.txt
sha1sum hashes.txt | awk '{ print $1 }'
rm hashes.txt
touch ./src/SystemConfig.cpp

