/*
 * Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 * This file is part of Kinetic Advanced Object Store (KAOS).
 *
 * This program is free software: you may copy, redistribute and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA. <http://www.gnu.org/licenses/>
 */
#pragma once
#ifndef COMMON_HPP
#define COMMON_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <string>
#include <sstream>

/*
 * Commonly Used Constants
 */
const int32_t  STATUS_SUCCESS(0);
const int32_t  STATUS_FAILURE(-1);

/**
 * Converts a variable value to a string format
 *
 * @param T         type of variable whose value is to be converted
 * @param value     value to be converted into a string
 *
 * @return the specified value in string form
 */
template<typename T>
std::string toString(T value) {
    std::stringstream stream;
    stream << value;
    return stream.str();
}

/*
 * Prevents a class from have a copy or assignment constructor when placed in the private
 * declaration section of a class (from Google's style guide).
 */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)

#endif
