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
#include "pentaledger/accounting/tax/irs_contribution_limits.hpp"
#include <unordered_map>

namespace pentaledger
{
    namespace accounting
    {
        // Static map to hold contribution limits for different account types and years
        //! \todo Update this map with the latest contribution limits as needed
        static std::unordered_map<int, std::unordered_map<RETIREMENT_ACCOUNT_TYPE, ContributionLimits>> contribution_limits_map = {
            {2025, {
                {OVERALL_IRA_LIMIT, {2025, OVERALL_IRA_LIMIT, 23500, 31000}},
                {IRA, {2025, IRA, 7000, 8000}},
                {ROTH_IRA, {2025, ROTH_IRA, 7000, 8000}},
                {SIMPLE_IRA, {2025, SIMPLE_IRA, 16500, 19500}},
                {SEP_IRA, {2025, SEP_IRA, 70000, 70000}},
                {R401K, {2025, R401K, 23500, 31000}},
                {OTHER, {2025, OTHER, 0.0, 0.0}} // Placeholder for other accounts
            }},
            {2024, {
                // The amount you can defer (including pre-tax and Roth contributions) to all your plans 
                // (not including 457(b) plans) is $23,000 in 2024
                {OVERALL_IRA_LIMIT, {2024, OVERALL_IRA_LIMIT, 23000, 30500}},
                {IRA, {2024, IRA, 7000, 8000}},
                {ROTH_IRA, {2024, ROTH_IRA, 7000, 8000}},
                {SIMPLE_IRA, {2024, SIMPLE_IRA, 16500, 19500}},
                {SEP_IRA, {2024, SEP_IRA, 69000, 69000}},
                {R401K, {2024, R401K, 23000, 30500}},
                {OTHER, {2024, OTHER, 0.0, 0.0}} // Placeholder for other accounts
            }},
            {2023, {
                {OVERALL_IRA_LIMIT, {2023, OVERALL_IRA_LIMIT, 22500, 30000}},
                {IRA, {2023, IRA, 6500, 7500}},
                {ROTH_IRA, {2023, ROTH_IRA, 6500, 7500}},
                {SIMPLE_IRA, {2023, SIMPLE_IRA, 15500, 1900}},
                {SEP_IRA, {2023, SEP_IRA, 66000, 7500}},
                {R401K, {2023, R401K, 22500, 30000}},
                {OTHER, {2023, OTHER, 0.0, 0.0}} // Placeholder for other accounts
            }},
            // Add more years as needed
        };

        ContributionLimits get_contribution_limits(int year, RETIREMENT_ACCOUNT_TYPE account_type)
        {
            if (contribution_limits_map.find(year) != contribution_limits_map.end() &&
                contribution_limits_map[year].find(account_type) != contribution_limits_map[year].end())
            {
                return contribution_limits_map[year][account_type];
            }
            else
            {
                // Return a default or error value if not found
                return {year, account_type, 0.0, 0.0};
            }
        }
    }
}