// SPDX-License-Identifier: GPL-2.0-only
//! \file cash_runway.hpp
//! \author Joe Turner <joe.turner@infinity-surge.com>
//!
//! \copyright
//! Copyright (c) 2024 Joe Turner.
//!
//! This program is free software; you can redistribute it and/or
//! modify it under the terms of the GNU General Public License
//! as published by the Free Software Foundation; either version 2
//! of the License, or (at your option) any later version.
//! 
//! This program is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//! 
//! You should have received a copy of the GNU General Public License
//! along with this program; If not, see <http://www.gnu.org/licenses/>.
#ifndef _CASH_RUNWAY_HPP_
#define _CASH_RUNWAY_HPP_

//! \brief Caculate Cash Runway
//!
//! If a company isn't profitable, does it have sufficient cash
//! to pay its bills.  
//!
//! Example: Company has an annual burn rate of $2.8M, and has $10M on
//! hand.  How many years will do we have to breakeven? The company
//! has 3.5 years to breakeven, then the business will run out of money
//! or have to raise money.
template <typename T>
T cash_runway(const T cash, const T burn_rate)
{
    T runway = cash / burn_rate;
    return runway;
}

#endif