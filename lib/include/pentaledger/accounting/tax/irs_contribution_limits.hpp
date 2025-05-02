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
#ifndef PENTALEDGERTAX_IRS_CONTRIBUTION_LIMITS_HPP
#define PENTALEDGERTAX_IRS_CONTRIBUTION_LIMITS_HPP

namespace pentaledger
{
    namespace accounting
    {

        enum RETIREMENT_ACCOUNT_TYPE
        {
            //! \brief Contribution limits for various retirement accounts
            //!
            //! Annual contributions to all of your accounts maintained by one employer
            //! (and any related employer) - this includes elective deferrals, employee
            //! contributions, employer matching and discretionary contributions and
            //! allocations of forfeitures, to your accounts, but not including
            //! catch-up contributions - may not exceed the lesser of 100% of your
            //! compensation or this limit.
            //!
            //! The amount of salary deferrals you can contribute to retirement plans 
            //! is your individual limit each calendar year no matter how many plans 
            //! you're in. This limit must be aggregated for these plan types:
            //! 
            //! - 401(k)
            //! - 403(b)
            //! - SIMPLE plans (SIMPLE IRA and SIMPLE 401(k) plans)
            //! - SARSEP
            OVERALL_IRA_LIMIT,
            IRA,
            ROTH_IRA,
            SIMPLE_IRA,
            SEP_IRA,
            R401K,
            OTHER
        };

        struct ContributionLimits
        {
            //! \brief Tax year for which the contribution limits apply
            int year;
            //! \brief Type of retirement account
            RETIREMENT_ACCOUNT_TYPE account_type;
            //! \brief Contribution limit for the specified account type in the given year
            double limit;
            //! \brief Catch-up contribution limit for individuals aged 50 or older
            double catch_up_limit; // For individuals aged 50 or older
        };

    }
}

#endif
