#include <gtest/gtest.h>
#include "pentaledger/pentaledger.hpp"

// Test fixture for PentaLedger tests
class PentaLedgerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code before each test
    }

    void TearDown() override {
        // Cleanup code after each test
    }
};

// Test default constructor
TEST_F(PentaLedgerTest, DefaultConstructor) {
    pentaledger::PentaLedger ledger;
    EXPECT_EQ(ledger.getVersion(), "0.1.0");
}

// Test version setting
TEST_F(PentaLedgerTest, SetVersion) {
    pentaledger::PentaLedger ledger;
    const std::string newVersion = "1.0.0";
    ledger.setVersion(newVersion);
    EXPECT_EQ(ledger.getVersion(), newVersion);
}

// Test multiple version changes
TEST_F(PentaLedgerTest, MultipleVersionChanges) {
    pentaledger::PentaLedger ledger;
    
    // First change
    const std::string version1 = "1.0.0";
    ledger.setVersion(version1);
    EXPECT_EQ(ledger.getVersion(), version1);
    
    // Second change
    const std::string version2 = "2.0.0";
    ledger.setVersion(version2);
    EXPECT_EQ(ledger.getVersion(), version2);
}

// Test empty version string
TEST_F(PentaLedgerTest, EmptyVersion) {
    pentaledger::PentaLedger ledger;
    ledger.setVersion("");
    EXPECT_EQ(ledger.getVersion(), "");
}

// Test version with special characters
TEST_F(PentaLedgerTest, SpecialCharactersInVersion) {
    pentaledger::PentaLedger ledger;
    const std::string specialVersion = "1.0.0-beta+special";
    ledger.setVersion(specialVersion);
    EXPECT_EQ(ledger.getVersion(), specialVersion);
} 