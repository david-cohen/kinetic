#!/bin/bash
# Copyright (c) 2014-2016 Western Digital Corporation or its affiliates <copyrightagent@wdc.com>
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

#TODO: Make package installation distribution agnostic

function install {
    packageName=$1
    sudo apt-get --yes --force-yes install $packageName
    
    if [ "$?" -ne 0 ]; then
        echo "Failed to successfully install $packageName"
        exit 1
    fi
}

sudo apt-get update
install make
install g++
install wget
install git
install yagiuda
install cppcheck
install doxygen
install libgflags-dev
install libsnappy-dev
install zlib1g-dev
install libbz2-dev

exit 0
