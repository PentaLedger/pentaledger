// SPDX-License-Identifier: GPL-2.0-only
//! \file csv_parser.cpp
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

#include "pentaledger/utility/csv_parser.h"
#include <stdexcept>
#include <sstream>

namespace pentaledger {
namespace utility {

CSVParser::CSVParser(const std::string& filename, 
                     char delimiter, 
                     char quote,
                     bool hasHeader)
    : filename_(filename)
    , delimiter_(delimiter)
    , quote_(quote)
    , hasHeader_(hasHeader)
    , currentRow_(0)
    , headerRead_(false)
{
    file_ = std::make_unique<std::ifstream>(filename);
    if (!file_->is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    if (hasHeader_) {
        readHeader();
    }
}

CSVParser::~CSVParser() {
    if (file_) {
        file_->close();
    }
}

std::optional<std::vector<std::string>> CSVParser::getHeader() const {
    if (hasHeader_ && !header_.empty()) {
        return header_;
    }
    return std::nullopt;
}

std::optional<std::vector<std::string>> CSVParser::readRow() {
    if (!file_ || !file_->is_open()) {
        return std::nullopt;
    }

    std::string line;
    if (std::getline(*file_, line)) {
        currentRow_++;
        return parseLine(line);
    }
    return std::nullopt;
}

bool CSVParser::hasMoreRows() const {
    return file_ && file_->is_open() && !file_->eof();
}

size_t CSVParser::getCurrentRowNumber() const {
    return currentRow_;
}

void CSVParser::reset() {
    if (file_) {
        file_->close();
        file_->open(filename_);
        if (!file_->is_open()) {
            throw std::runtime_error("Failed to reopen file: " + filename_);
        }
        currentRow_ = 0;
        headerRead_ = false;
        if (hasHeader_) {
            readHeader();
        }
    }
}

void CSVParser::readHeader() {
    if (!headerRead_ && hasHeader_) {
        auto row = readRow();
        if (row) {
            header_ = *row;
            headerRead_ = true;
        }
    }
}

std::vector<std::string> CSVParser::parseLine(const std::string& line) {
    std::vector<std::string> fields;
    auto it = line.begin();
    auto end = line.end();

    while (it != end) {
        fields.push_back(parseField(it, end));
        if (it != end && *it == delimiter_) {
            ++it;
        }
    }

    return fields;
}

std::string CSVParser::parseField(std::string::const_iterator& it, 
                                std::string::const_iterator end) {
    std::string field;
    bool inQuotes = false;

    // Skip leading whitespace
    while (it != end && (*it == ' ' || *it == '\t')) {
        ++it;
    }

    if (it == end) {
        return field;
    }

    // Check if field is quoted
    if (*it == quote_) {
        inQuotes = true;
        ++it;
    }

    while (it != end) {
        if (inQuotes) {
            if (*it == quote_) {
                ++it;
                // Check for escaped quote (double quote)
                if (it != end && *it == quote_) {
                    field += quote_;
                    ++it;
                } else {
                    inQuotes = false;
                    break;
                }
            } else {
                field += *it;
                ++it;
            }
        } else {
            if (*it == delimiter_ || *it == '\n' || *it == '\r') {
                break;
            }
            field += *it;
            ++it;
        }
    }

    // Skip trailing whitespace
    while (it != end && (*it == ' ' || *it == '\t')) {
        ++it;
    }

    return field;
}

} // namespace utility
} // namespace pentaledger 