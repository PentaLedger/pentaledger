//! \file drivers_status.hpp
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
#ifndef _DRIVER_STATUS_HPP_
#define _DRIVER_STATUS_HPP_

namespace pentaledger
{
    namespace transportation
    {

        enum eDRIVER_STATUS
        {
            eOFF_DUTY,
            eSLEEPER_BERTH,
            eDRIVING,
            eON_DUTY,
            eOFF_DUTY_WELL_SITE,
        };

    }
}
#endif