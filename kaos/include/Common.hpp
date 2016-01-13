/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
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
const uint32_t SYSTEM_BLOCK_SIZE(512);
const int32_t  STATUS_SUCCESS(0);
const int32_t  STATUS_FAILURE(-1);

/**
 * To String
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
 * Prevents code from being included when built for unit tests.
 */
#ifdef UNIT_TEST
#define DISABLE_FOR_UNIT_TEST(unitTestDisabledCode)
#else
#define DISABLE_FOR_UNIT_TEST(unitTestDisabledCode) unitTestDisabledCode
#endif

/*
 * Prevents a class from have a copy or assignment constructor when placed in the private
 * declaration section of a class (from Google's style guide).
 */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)

#endif
