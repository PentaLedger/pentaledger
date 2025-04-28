// SPDX-License-Identifier: GPL-2.0-only
//! \file GamblingType.hpp
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
#ifndef _MILEAGE_CATAGORIES_HPP_
#define _MILEAGE_CATAGORIES_HPP_

namespace pentaledger
{
    namespace gambling
    {

        //! \brief Gambling Type 
        enum eGamblingType
        {
            //! \brief Lottery
            //!
            //! Who hasn't played the lottery?  Losses are deductible against winnings,
            //! but only if you keep track.
            LOTTERY,

        };

    }
}

#endif
