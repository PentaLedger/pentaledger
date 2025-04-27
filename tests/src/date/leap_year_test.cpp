// SPDX-License-Identifier: GPL-2.0-only
//! \file leap_year_test.cpp
//! \brief Test cases for leap year calculations
//!
//! \author Joe Turner <joe.turner@infinity-surge.com>
//!
//! \copyright
//! Copyright (c) 2025 Joe Turner.

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

