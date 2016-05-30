#!/bin/bash
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

declare -a ignoreErrorsList=(
    # Not going to adhere to the indenting of 1 space for the public, private, and protected declarations
    "public: should be indented +1 space" 
    "private: should be indented +1 space" 
    "protected: should be indented +1 space"
    # cpplint incorrectly complains about this for do-while loops, so it's disabled
    "Empty loop bodies should use {} or continue"
    # Not following the rule for else related braces
    "An else should appear on the same line as the preceding }"
    "If an else has a brace on one side, it should have it on both"
    # Not following the rule that references will only be used for const variables
    "Is this a non-const reference? If so, make const or use a pointer:"
    # Ignore rule regarding file name (it doesn't like the protoc generated file name)
    "not a valid file name"
    # Don't report the total error found since some have been ignored
    "Total errors found"
)

declare -a pathList=(
    "$1/include/*.hpp"
    "$1/src/*.cpp"
    "$1/test/*.cpp"
)


for path in "${pathList[@]}"
do
    while read -r line; do
        suppress="false"
        for error in "${ignoreErrorsList[@]}"
        do
            if [[ $line == *"$error"* ]]; then
                suppress="true"
            fi
        done
    
        if [[ $suppress == "false" ]]; then
            echo "$line"
        fi
    done < <(exec dependencies/styleguide/cpplint/cpplint.py --extensions=cpp --linelength=150 --filter=-build/c++11 $path 2>&1)
done

exit 0
