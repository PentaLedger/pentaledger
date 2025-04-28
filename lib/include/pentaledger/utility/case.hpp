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
#ifndef _CASE_HPP
#define _CASE_HPP
#include <string>
#include <algorithm>

namespace pentaledger
{
    namespace utility
    {

        template <typename T>
        void toUpper(std::basic_string<T> &str)
        {
            transform(str.begin(), str.end(), str.begin(), ::toupper);
        }

        template <typename T>
        void toLower(std::basic_string<T> &str)
        {
            transform(str.begin(), str.end(), str.begin(), ::tolower);
        }

        template <typename T>
        std::string returnUpper(std::basic_string<T>  str)
        {
            transform(str.begin(), str.end(), str.begin(), ::toupper);
            return str;
        }

        template <typename T>
        std::string returnLower(std::basic_string<T> str)
        {
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            return str;
        }

    }
}

#endif