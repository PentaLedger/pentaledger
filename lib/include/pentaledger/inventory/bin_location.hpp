//! \file bin_location.hpp
//! \author Joe Turner <joe.turner@infinity-surge.com>
//!
//! \copyright
//! Copyright (c) 2023 Infinity Surge Inc.
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
#ifndef _BIN_LOCATION_HPP_
#define _BIN_LOCATION_HPP_

namespace pentaledger
{
    namespace inventory
    {

        /**
         *

        WAREHOUSE WH1
        AREA A-Z
        ROW 1-n
        BAY 1-n
        LEVEL 1-n lowest level 1
        POS/BIN
        */

        struct warehouse_bin_location
        {
            //! A-Z
            char area; //! area/zone
            //! 1-255
            char row; //! row/aisle
            //! 1-255
            char bay; //! bay
            //! 1-255
            char level; // Level from floor
            //! 1-255
            char pos; //! position/bin
        };

    }
}

#endif
