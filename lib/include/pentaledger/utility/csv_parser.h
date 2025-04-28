// SPDX-License-Identifier: GPL-2.0-only
//! \file csv_parser.h
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
#ifndef _CSV_PARSER_H_
#define _CSV_PARSER_H_

#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <optional>

namespace pentaledger {
namespace utility {

/**
 * @brief CSV Parser class for reading and processing CSV files
 * 
 * This class provides functionality to parse CSV files with various options:
 * - Custom delimiters
 * - Quote handling
 * - Header row support
 * - Error handling
 * - Memory-efficient streaming
 */
class CSVParser {
public:
    /**
     * @brief Construct a new CSVParser object
     * 
     * @param filename Path to the CSV file
     * @param delimiter Character used as field delimiter (default: ',')
     * @param quote Character used for quoting fields (default: '"')
     * @param hasHeader Whether the file has a header row (default: true)
     */
    CSVParser(const std::string& filename, 
              char delimiter = ',', 
              char quote = '"',
              bool hasHeader = true);

    /**
     * @brief Destroy the CSVParser object
     */
    ~CSVParser();

    /**
     * @brief Get the header row if available
     * 
     * @return std::optional<std::vector<std::string>> Header row if exists
     */
    std::optional<std::vector<std::string>> getHeader() const;

    /**
     * @brief Read the next row from the CSV file
     * 
     * @return std::optional<std::vector<std::string>> Next row if available
     */
    std::optional<std::vector<std::string>> readRow();

    /**
     * @brief Check if there are more rows to read
     * 
     * @return true if more rows are available
     * @return false if end of file reached
     */
    bool hasMoreRows() const;

    /**
     * @brief Get the current row number
     * 
     * @return size_t Current row number (1-based)
     */
    size_t getCurrentRowNumber() const;

    /**
     * @brief Reset the parser to the beginning of the file
     */
    void reset();

private:
    std::string filename_;
    char delimiter_;
    char quote_;
    bool hasHeader_;
    std::unique_ptr<std::ifstream> file_;
    std::vector<std::string> header_;
    size_t currentRow_;
    bool headerRead_;

    // Helper methods
    std::vector<std::string> parseLine(const std::string& line);
    std::string parseField(std::string::const_iterator& it, 
                         std::string::const_iterator end);
    void readHeader();
};

} // namespace utility
} // namespace pentaledger

#endif 