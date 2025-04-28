//! \file case.hpp
//! \author Joe Turner <joe.turner@infinity-surge.com>
//!
//! \copyright
//! Copyright (c) 2024 Infinity Surge Inc.
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
#ifndef _TRIM_HPP_
#define _TRIM_HPP_
#include <string>

namespace pentaledger
{
    namespace utility
    {
        template <typename T>
        std::string trimLeading(const std::basic_string<T> &str, char c)
        {
            size_t pos = str.find_first_not_of(c);
            return pos != std::string::npos ? str.substr(pos, str.length()) : "";
        }

        template <typename T>
        std::string trimTrailing(const std::basic_string<T> &str, char c)
        {
            size_t pos = str.find_last_not_of(c);
            return pos != std::string::npos ? str.substr(0, pos + 1) : "";
        }

        template <typename T>
        std::string trim(const std::basic_string<T> &str, char c)
        {
            return trimTrailing(trimLeading(str, c), c);
        }

    }
}
#endif