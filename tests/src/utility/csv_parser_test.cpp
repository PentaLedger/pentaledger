// SPDX-License-Identifier: GPL-2.0-only
//! \file csv_parser_test.cpp
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
#include <pentaledger/utility/csv_parser.h>
#include <fstream>
#include <filesystem>

using namespace pentaledger::utility;

class CSVParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test CSV files
        createTestFiles();
    }

    void TearDown() override {
        // Clean up test files
        std::filesystem::remove("test_basic.csv");
        std::filesystem::remove("test_quotes.csv");
        std::filesystem::remove("test_no_header.csv");
        std::filesystem::remove("test_empty.csv");
        std::filesystem::remove("test_custom_delimiter.csv");
    }

    void createTestFiles() {
        // Basic CSV with header
        {
            std::ofstream file("test_basic.csv");
            file << "Name,Age,City\n"
                 << "John,30,New York\n"
                 << "Alice,25,Los Angeles\n"
                 << "Bob,35,Chicago\n";
        }

        // CSV with quoted fields
        {
            std::ofstream file("test_quotes.csv");
            file << "Name,Description,Value\n"
                 << "John,\"Software Engineer, Senior\",100000\n"
                 << "Alice,\"Data Scientist, Lead\",120000\n"
                 << "Bob,\"Project Manager\",90000\n";
        }

        // CSV without header
        {
            std::ofstream file("test_no_header.csv");
            file << "John,30,New York\n"
                 << "Alice,25,Los Angeles\n"
                 << "Bob,35,Chicago\n";
        }

        // Empty CSV
        {
            std::ofstream file("test_empty.csv");
        }

        // CSV with custom delimiter
        {
            std::ofstream file("test_custom_delimiter.csv");
            file << "Name|Age|City\n"
                 << "John|30|New York\n"
                 << "Alice|25|Los Angeles\n"
                 << "Bob|35|Chicago\n";
        }
    }
};

// Test basic CSV parsing
TEST_F(CSVParserTest, BasicParsing) {
    CSVParser parser("test_basic.csv");
    
    // Check header
    auto header = parser.getHeader();
    ASSERT_TRUE(header.has_value());
    ASSERT_EQ(header->size(), 3);
    EXPECT_EQ((*header)[0], "Name");
    EXPECT_EQ((*header)[1], "Age");
    EXPECT_EQ((*header)[2], "City");

    // Check first row
    auto row1 = parser.readRow();
    ASSERT_TRUE(row1.has_value());
    ASSERT_EQ(row1->size(), 3);
    EXPECT_EQ((*row1)[0], "John");
    EXPECT_EQ((*row1)[1], "30");
    EXPECT_EQ((*row1)[2], "New York");

    // Check second row
    auto row2 = parser.readRow();
    ASSERT_TRUE(row2.has_value());
    ASSERT_EQ(row2->size(), 3);
    EXPECT_EQ((*row2)[0], "Alice");
    EXPECT_EQ((*row2)[1], "25");
    EXPECT_EQ((*row2)[2], "Los Angeles");

    // Check third row
    auto row3 = parser.readRow();
    ASSERT_TRUE(row3.has_value());
    ASSERT_EQ(row3->size(), 3);
    EXPECT_EQ((*row3)[0], "Bob");
    EXPECT_EQ((*row3)[1], "35");
    EXPECT_EQ((*row3)[2], "Chicago");

    // Check end of file
    EXPECT_FALSE(parser.readRow().has_value());
}

// Test quoted fields
TEST_F(CSVParserTest, QuotedFields) {
    CSVParser parser("test_quotes.csv");
    
    // Check header
    auto header = parser.getHeader();
    ASSERT_TRUE(header.has_value());
    ASSERT_EQ(header->size(), 3);

    // Check first row with quoted field containing delimiter
    auto row1 = parser.readRow();
    ASSERT_TRUE(row1.has_value());
    ASSERT_EQ(row1->size(), 3);
    EXPECT_EQ((*row1)[0], "John");
    EXPECT_EQ((*row1)[1], "Software Engineer, Senior");
    EXPECT_EQ((*row1)[2], "100000");
}

// Test CSV without header
TEST_F(CSVParserTest, NoHeader) {
    CSVParser parser("test_no_header.csv", ',', '"', false);
    
    // Check that there's no header
    auto header = parser.getHeader();
    EXPECT_FALSE(header.has_value());

    // Check first row
    auto row1 = parser.readRow();
    ASSERT_TRUE(row1.has_value());
    ASSERT_EQ(row1->size(), 3);
    EXPECT_EQ((*row1)[0], "John");
}

// Test empty CSV
TEST_F(CSVParserTest, EmptyFile) {
    CSVParser parser("test_empty.csv");
    
    // Check that there's no header
    auto header = parser.getHeader();
    EXPECT_FALSE(header.has_value());

    // Check that there are no rows
    EXPECT_FALSE(parser.readRow().has_value());
    EXPECT_FALSE(parser.hasMoreRows());
}

// Test custom delimiter
TEST_F(CSVParserTest, CustomDelimiter) {
    CSVParser parser("test_custom_delimiter.csv", '|');
    
    // Check header
    auto header = parser.getHeader();
    ASSERT_TRUE(header.has_value());
    ASSERT_EQ(header->size(), 3);

    // Check first row
    auto row1 = parser.readRow();
    ASSERT_TRUE(row1.has_value());
    ASSERT_EQ(row1->size(), 3);
    EXPECT_EQ((*row1)[0], "John");
    EXPECT_EQ((*row1)[1], "30");
    EXPECT_EQ((*row1)[2], "New York");
}

// Test reset functionality
TEST_F(CSVParserTest, Reset) {
    CSVParser parser("test_basic.csv");
    
    // Read first row
    auto row1 = parser.readRow();
    ASSERT_TRUE(row1.has_value());
    EXPECT_EQ((*row1)[0], "John");

    // Reset and read first row again
    parser.reset();
    row1 = parser.readRow();
    ASSERT_TRUE(row1.has_value());
    EXPECT_EQ((*row1)[0], "John");
}

// Test row counting
TEST_F(CSVParserTest, RowCounting) {
    CSVParser parser("test_basic.csv");
    
    EXPECT_EQ(parser.getCurrentRowNumber(), 0);
    parser.readRow();
    EXPECT_EQ(parser.getCurrentRowNumber(), 1);
    parser.readRow();
    EXPECT_EQ(parser.getCurrentRowNumber(), 2);
    parser.readRow();
    EXPECT_EQ(parser.getCurrentRowNumber(), 3);
}

// Test file not found
TEST_F(CSVParserTest, FileNotFound) {
    EXPECT_THROW(CSVParser("nonexistent.csv"), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 