//! \file LeapYear.hpp
//! \author Joe Turner <joe@agavemountain.com>
//!
//! \copyright
//! Copyright (c) 2023 Joe Turner.
//!
//! This program is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, version 3.
//!
//! This program is distributed in the hope that it will be useful, but
//! WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//! General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with this program. If not, see <http://www.gnu.org/licenses/>.
#ifndef _LEAPYEAR_HPP_
#define _LEAPYEAR_HPP_

namespace pentaledger
{
    namespace time
    {

        //! \brief Check if supplied year is leap year. 
        //!
        //! \param year  Year to check if it is a leap year.
        //!
        //! \returns
        //! \retval true    This is a leap year
        //! \retval false   This is not a leap yaer.
        inline bool isLeapYear(int year)
        {
            bool result = false;
            
            if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
            {
                result = true;
            }

            return result;
        }

    }
}

#endif
