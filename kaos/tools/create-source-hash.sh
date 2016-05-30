#! /bin/bash
# Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
#
# SPDX-License-Identifier: GPL-2.0+
# This file is part of Kinetic Advanced Object Store (KAOS).
#
# This program is free software: you may copy, redistribute and/or modify it under the terms of the
# GNU General Public License as published by the Free Software Foundation, either version 2 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with this program; if
# not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA. <http://www.gnu.org/licenses/>
#
# The source hash is created by hashing the hashes of the Makefile, the application source files
# (cpp files) and application include files.  The individual file hashes are kept in the hashes.txt
# file, which is deleted at the end of the operation.  The source hash is maintained in the
# GlobalConfig.cpp file, so it is touched to force its recompile to obtain the lastest hash.

sha1sum ./Makefile > hashes.txt
sha1sum ./src/*.cpp >> hashes.txt
sha1sum ./include/*.hpp >> hashes.txt
sha1sum hashes.txt | awk '{ print $1 }'
rm hashes.txt
touch ./src/GlobalConfig.cpp

