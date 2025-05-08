#include <gtest/gtest.h>
#include "pentaledger/accounting/tax/NIIT.hpp"

using namespace pentaledger::accounting::tax;


// Test when MAGI is below threshold – should return 0
TEST(CalculateNIITTest, MagiBelowThreshold) {
    double result = calculateNIIT(150000.0, 10000.0, 200000.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test when MAGI equals threshold – should return 0
TEST(CalculateNIITTest, MagiEqualsThreshold) {
    double result = calculateNIIT(200000.0, 5000.0, 200000.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test when MAGI exceeds threshold but investment income is less
TEST(CalculateNIITTest, ExcessMAGIGreaterThanInvestmentIncome) {
    double result = calculateNIIT(250000.0, 10000.0, 200000.0);
    EXPECT_DOUBLE_EQ(result, 10000.0 * 0.038);
}

// Test when investment income is greater than excess MAGI
TEST(CalculateNIITTest, InvestmentIncomeGreaterThanExcessMAGI) {
    double result = calculateNIIT(210000.0, 50000.0, 200000.0);
    EXPECT_DOUBLE_EQ(result, 10000.0 * 0.038);
}

// Test with zero investment income
TEST(CalculateNIITTest, ZeroInvestmentIncome) {
    double result = calculateNIIT(300000.0, 0.0, 200000.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test with zero MAGI
TEST(CalculateNIITTest, ZeroMAGI) {
    double result = calculateNIIT(0.0, 5000.0, 200000.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}
