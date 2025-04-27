/**
 * \file LeapYear_tst.cpp
 *
 * Copyright (c) 2025 Joe Turner.  All rights reserved.
 * Unauthorized copying prohibited.
 */
#include "pentaledger/date/leap_year.hpp"
#include <gtest/gtest.h>

using namespace pentaledger::time;

TEST(LeapYear_tests, test_is_leap_year)
{
    // 2020 is a leap year.
    ASSERT_EQ(true, isLeapYear(2020));
}

TEST(LeapYear_tests, test_is_not_leap_year)
{
    // 2020 is a leap year.
    ASSERT_EQ(false, isLeapYear(2021));
}

