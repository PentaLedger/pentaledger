// SPDX-License-Identifier: GPL-2.0-only
//! \file environment_test.cpp
//! \author Joe Turner <joe.turner@infinity-surge.com>
//!
//! \copyright
//! Copyright (c) 2023 Joe Turner.
//!
//! This program is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, version 2.
//!
//! This program is distributed in the hope that it will be useful, but
//! WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//! General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <gtest/gtest.h>
#include <pentaledger/utility/Environment.hpp>
#include <string>

using namespace pentaledger::utility;

class EnvironmentTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Save original environment variables that we'll modify
        originalTestVar = Environment<std::string>::get("TEST_VAR");
        originalHome = Environment<std::string>::get("HOME");
    }

    void TearDown() override {
        // Restore original environment variables
        if (!originalTestVar.empty()) {
            Environment<std::string>::set("TEST_VAR", originalTestVar);
        } else {
            Environment<std::string>::erase("TEST_VAR");
        }
    }

    std::string originalTestVar;
    std::string originalHome;
};

// Test getting environment variables
TEST_F(EnvironmentTest, GetEnvironmentVariable) {
    // Test with existing variable
    const char* path = "PATH";
    std::string pathValue = Environment<std::string>::get(path);
    EXPECT_FALSE(pathValue.empty());

    // Test with non-existent variable
    std::string nonExistent = Environment<std::string>::get("NON_EXISTENT_VAR");
    EXPECT_TRUE(nonExistent.empty());
}

// Test setting environment variables
TEST_F(EnvironmentTest, SetEnvironmentVariable) {
    const char* key = "TEST_VAR";
    const char* value = "test_value";

    // Set new variable
    int result = Environment<std::string>::set(key, value);
    EXPECT_EQ(result, 0);

    // Verify it was set
    std::string retrieved = Environment<std::string>::get(key);
    EXPECT_EQ(retrieved, value);

    // Update existing variable
    const char* newValue = "new_test_value";
    result = Environment<std::string>::set(key, newValue);
    EXPECT_EQ(result, 0);

    // Verify update
    retrieved = Environment<std::string>::get(key);
    EXPECT_EQ(retrieved, newValue);
}

// Test checking if environment variables exist
TEST_F(EnvironmentTest, EnvironmentVariableExists) {
    // Test with existing variable
    EXPECT_TRUE(Environment<std::string>::isExists("PATH"));

    // Test with non-existent variable
    EXPECT_FALSE(Environment<std::string>::isExists("NON_EXISTENT_VAR"));

    // Test with string parameter
    std::string pathStr = "PATH";
    EXPECT_TRUE(Environment<std::string>::isExists(pathStr));
}

// Test erasing environment variables
TEST_F(EnvironmentTest, EraseEnvironmentVariable) {
    const char* key = "TEST_VAR";
    const char* value = "test_value";

    // Set a variable
    Environment<std::string>::set(key, value);
    EXPECT_TRUE(Environment<std::string>::isExists(key));

    // Erase it
    int result = Environment<std::string>::erase(key);
    EXPECT_EQ(result, 0);

    // Verify it's gone
    EXPECT_FALSE(Environment<std::string>::isExists(key));
}

// Test home path retrieval
TEST_F(EnvironmentTest, GetHomePath) {
    std::string homePath = Environment<std::string>::home_path();
    EXPECT_FALSE(homePath.empty());
    
    // On Unix-like systems, home path should start with '/'
    #ifndef _WIN32
    EXPECT_EQ(homePath[0], '/');
    #endif
}

// Test operator[] access
//! \todo: Implement operator[] access.
// TEST_F(EnvironmentTest, OperatorAccess) {
//     const char* key = "TEST_VAR";
//     const char* value = "test_value";
//     Environment<std::string> env;

//     // Set variable
//     Environment<std::string>::set(key, value);

//     // Test operator[] with const char*
//     EXPECT_EQ(env[key], value);

//     // Test operator[] with std::string
//     std::string keyStr = key;
//     EXPECT_EQ(env[keyStr], value);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 