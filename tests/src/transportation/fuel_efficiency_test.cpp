// SPDX-License-Identifier: GPL-2.0-only
//! \file fuel_efficiency_test.cpp
//! \brief Test cases for fuel efficiency calculations
//!
//! \author Joe Turner <joe.turner@infinity-surge.com>
//!
//! \copyright
//! Copyright (c) 2025 Joe Turner.
#include <gtest/gtest.h>
#include "pentaledger/transportation/fuel_efficiency.hpp"

using namespace pentaledger::transportation;
// Test fixture for fuel efficiency tests
class FuelEfficiencyTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code before each test
    }

    void TearDown() override {
        // Cleanup code after each test
    }
};

// Test calculateFuelEfficiency with valid inputs
TEST_F(FuelEfficiencyTest, CalculateValidEfficiency) {
    double distance = 100.0;  // kilometers
    double fuelUsed = 10.0;   // liters
    double expectedEfficiency = 10.0;  // km/L

    double efficiency = calculate_fuel_efficiency(distance, fuelUsed);
    EXPECT_DOUBLE_EQ(efficiency, expectedEfficiency);
}

// Test calculateFuelEfficiency with zero distance
TEST_F(FuelEfficiencyTest, CalculateZeroDistance) {
    double distance = 0.0;
    double fuelUsed = 10.0;

    EXPECT_THROW(calculate_fuel_efficiency(distance, fuelUsed), std::invalid_argument);
}

// Test calculateFuelEfficiency with zero fuel
TEST_F(FuelEfficiencyTest, CalculateZeroFuel) {
    double distance = 100.0;
    double fuelUsed = 0.0;

    EXPECT_THROW(calculate_fuel_efficiency(distance, fuelUsed), std::invalid_argument);
}

// Test calculateFuelEfficiency with negative distance
TEST_F(FuelEfficiencyTest, CalculateNegativeDistance) {
    double distance = -100.0;
    double fuelUsed = 10.0;

    EXPECT_THROW(calculate_fuel_efficiency(distance, fuelUsed), std::invalid_argument);
}

// Test calculateFuelEfficiency with negative fuel
TEST_F(FuelEfficiencyTest, CalculateNegativeFuel) {
    double distance = 100.0;
    double fuelUsed = -10.0;

    EXPECT_THROW(calculate_fuel_efficiency(distance, fuelUsed), std::invalid_argument);
}

// Test calculateFuelEfficiency with very small values
TEST_F(FuelEfficiencyTest, CalculateSmallValues) {
    double distance = 0.001;  // 1 meter
    double fuelUsed = 0.0001; // 0.1 milliliter
    double expectedEfficiency = 10.0;  // km/L

    double efficiency = calculate_fuel_efficiency(distance, fuelUsed);
    EXPECT_DOUBLE_EQ(efficiency, expectedEfficiency);
}

// Test calculateFuelEfficiency with very large values
TEST_F(FuelEfficiencyTest, CalculateLargeValues) {
    double distance = 1000000.0;  // 1 million kilometers
    double fuelUsed = 100000.0;   // 100 thousand liters
    double expectedEfficiency = 10.0;  // km/L

    double efficiency = calculate_fuel_efficiency(distance, fuelUsed);
    EXPECT_DOUBLE_EQ(efficiency, expectedEfficiency);
}

// Test calculate_fuel_required with valid inputs
TEST_F(FuelEfficiencyTest, CalculateValidFuelRequired) {
    double distance = 100.0;  // kilometers
    double efficiency = 10.0; // km/L
    double expectedFuel = 10.0;  // liters

    double fuel = calculate_fuel_required(distance, efficiency);
    EXPECT_DOUBLE_EQ(fuel, expectedFuel);
}

// Test calculate_fuel_required with zero distance
//! \todo: Add test for float and int
// TEST_F(FuelEfficiencyTest, CalculateFuelRequiredZeroDistance) {
//     double distance = 0.0;
//     double efficiency = 10.0;

//     double fuel = calculate_fuel_required(distance, efficiency);
//     EXPECT_DOUBLE_EQ(fuel, 0.0);
// }

// Test calculate_fuel_required with zero efficiency
TEST_F(FuelEfficiencyTest, CalculateFuelRequiredZeroEfficiency) {
    double distance = 100.0;
    double efficiency = 0.0;

    EXPECT_THROW(calculate_fuel_required(distance, efficiency), std::invalid_argument);
}

// Test calculate_fuel_required with negative distance
TEST_F(FuelEfficiencyTest, CalculateFuelRequiredNegativeDistance) {
    double distance = -100.0;
    double efficiency = 10.0;

    EXPECT_THROW(calculate_fuel_required(distance, efficiency), std::invalid_argument);
}

// Test calculate_fuel_required with negative efficiency
TEST_F(FuelEfficiencyTest, CalculateFuelRequiredNegativeEfficiency) {
    double distance = 100.0;
    double efficiency = -10.0;

    EXPECT_THROW(calculate_fuel_required(distance, efficiency), std::invalid_argument);
}

// Test calculate_fuel_required with very small values
TEST_F(FuelEfficiencyTest, CalculateFuelRequiredSmallValues) {
    double distance = 0.001;  // 1 meter
    double efficiency = 0.1;  // 0.1 km/L
    double expectedFuel = 0.01;  // 10 milliliters

    double fuel = calculate_fuel_required(distance, efficiency);
    EXPECT_DOUBLE_EQ(fuel, expectedFuel);
}

// Test calculate_fuel_required with very large values
TEST_F(FuelEfficiencyTest, CalculateFuelRequiredLargeValues) {
    double distance = 1000000.0;  // 1 million kilometers
    double efficiency = 100.0;    // 100 km/L
    double expectedFuel = 10000.0;  // 10 thousand liters

    double fuel = calculate_fuel_required(distance, efficiency);
    EXPECT_DOUBLE_EQ(fuel, expectedFuel);
}

// Test calculate_fuel_required with high precision
TEST_F(FuelEfficiencyTest, CalculateFuelRequiredHighPrecision) {
    double distance = 100.0;
    double efficiency = 3.141592653589793;  // π km/L
    double expectedFuel = 31.830988618379067;  // 100/π liters

    double fuel = calculate_fuel_required(distance, efficiency);
    EXPECT_NEAR(fuel, expectedFuel, 1e-14);  // Allow for small floating-point differences
} 