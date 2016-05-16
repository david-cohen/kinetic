/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc.
 *
 * This code is CONFIDENTIAL and a TRADE SECRET of Western Digital Technologies, Inc. and its
 * affiliates ("WD").  This code is protected under copyright laws as an unpublished work of WD.
 * Notice is for informational purposes only and does not imply publication.
 *
 * The receipt or possession of this code does not convey any rights to reproduce or disclose its
 * contents, or to manufacture, use, or sell anything that it may describe, in whole or in part,
 * without the specific written consent of WD.  Any reproduction or distribution of this code
 * without the express written consent of WD is strictly prohibited, is a violation of the copyright
 * laws, and may subject you to criminal prosecution.
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
