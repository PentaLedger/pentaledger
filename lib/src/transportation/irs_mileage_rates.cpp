//! \brief IRS Mileage Rates
//! \file irs_mileage_rates.hpp
//!
//! \copyright
//!
//! This file is part of the ERPBeyond distribution.
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
#include "pentaledger/transportation/irs_mileage_rates.hpp"

namespace pentaledger
{
    namespace transportation
    {
        //! \brief IRS mileage rate
        //!
        //! This struct contains the mileage rates for a given type and date.
        //! Periodically, the IRS updates the mileage rates for each type.
        //! In some cases, the mileage rates have been updated mid year, 
        //! causing us to have to deal with mid-year changes.
        struct sMileageRate
        {
            time_t start_date;
            double charity;
            double business;
            double medical;
            double moving;
            double other;
        };

        struct sMileageRates irs_mileage_rate_table[] = {
            {1293840000, 56.5, 56.5, 23.5, 15.5, 16.5},
            {1322476800, 56.5, 56.5, 23.5, 15.5, 16.5},
            {1351012800, 56.5, 56.5, 23.5, 15.5, 16.5},
            {1379649600, 56.5, 56.5, 23.5, 15.5, 16.5},
            {1408185600, 56.5, 56.5, 23.5, 15.5, 16.5},
            {1436822400, 56.5, 56.5, 23.5, 15.5, 16.5},
        };

        // January 1, 2011 00:00:00 UTC is 1293840000 seconds since epoch
        const time_t JAN_1_2011 = 1293840000;

        double current_irs_mileage_rate(eMilegeType type)
        {
            static bool current = false;
            static double result = 0.0;

            if (!current)
            {
            time_t now = time(nullptr);
            for (int i = 0; i < sizeof(irs_mileage_rate_table) / sizeof(irs_mileage_rate_table[0]); i++)
            {
                if (now >= irs_mileage_rate_table[i].start_date)
                {
                    result = irs_mileage_rate_table[i].type;
                    return irs_mileage_rate_table[i].type;
                }
            }

            }
            return result;
        }

        double irs_mileage_rate(eMilegeType type, time_t date)
        {
            time_t now = time(nullptr);
            for (int i = 0; i < sizeof(irs_mileage_rate_table) / sizeof(irs_mileage_rate_table[0]); i++)
            {
                if (date >= irs_mileage_rate_table[i].start_date)
                {
                    return irs_mileage_rate_table[i].type;
                }
            }
            return 0.0;
        }
    }
}