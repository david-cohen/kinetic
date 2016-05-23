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
#ifndef HMAC_HPP
#define HMAC_HPP

/*
 * Include Files
 */
#include <string>

/*
 * HMAC Algorithms
 */
enum class HmacAlgorithm {
    UNKNOWN,
    SHA1,
};

/**
 * Provides a method to compute an HMAC on a block of data.
 */
class Hmac {
public:
    static std::string compute(const std::string& data, const std::string& key, HmacAlgorithm algorithm, bool prependSize = true);
};

/*
 * Constants
 */
const bool HMAC_PREPEND_SIZE(true);
const bool HMAC_DO_NOT_PREPEND_SIZE(false);

#endif
