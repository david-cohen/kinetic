/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef COMMON_HPP
#define COMMON_HPP

/*
    Commonly Used Constants
*/

const uint32_t SYSTEM_BLOCK_SIZE(512);
const int32_t  STATUS_SUCCESS(0);
const int32_t  STATUS_FAILURE(-1);

#ifdef UNIT_TEST
#define DISABLE_FOR_UNIT_TEST(unitTestDisabledCode)
#else
#define DISABLE_FOR_UNIT_TEST(unitTestDisabledCode) unitTestDisabledCode
#endif

/*
    Prevents a class from have a copy or assignment constructor when placed in a classes private
    declarations (from Google's style guide).
*/

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    void operator=(const TypeName&)

#endif
