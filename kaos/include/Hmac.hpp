/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
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
 *   HMAC
 *
 *   This class provides a method to compute an HMAC on a block of data.
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
