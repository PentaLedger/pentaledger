// SPDX-License-Identifier: GPL-2.0-or-later
//! \file irs_contribution_limits.hpp
//! \author Joe Turner <joe.turner@infinity-surge.com>
//!
//! \copyright
//! Copyright (c) 2025 Joe Turner.
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
#include <type_traits>
#include <algorithm>

namespace pentaledger
{
    namespace accounting
    {
        namespace tax
        {
            /**
             * @brief Calculate the Net Investment Income Tax (NIIT)
             *
             * This function calculates the Net Investment Income Tax (NIIT) based on the Modified Adjusted Gross Income (MAGI),
             * investment income, and applicable thresholds and rates.
             *
             * @param magi The Modified Adjusted Gross Income
             * @param investment_income The amount of investment income
             * @param threshold The income threshold for NIIT (default: $200,000 for single filers)
             * @param niit_rate The NIIT rate (default: 3.8%)
             * @return The calculated NIIT amount
             */
            template <typename T>
            T calculateNIIT(T magi, T investment_income, T threshold = static_cast<T>(200000), T niit_rate = static_cast<T>(0.038))
            {
                static_assert(std::is_arithmetic<T>::value, "Template parameter must be a numeric type.");

                T excess_income = magi > threshold ? (magi - threshold) : static_cast<T>(0);
                T applicable_amount = std::min(excess_income, investment_income);
                return applicable_amount * niit_rate;
            }
        }
    }
}
