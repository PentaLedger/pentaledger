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
        /** @addtogroup MILEAGE_RATES
     
        @{ */

        // Define the static mileage rates for different categories and periods
        const MileageRates IRS_MILEAGE_RATES[] = {
            // Business mileage rates
            { 1704067200, MILEAGE_BUSINESS, 0.655 }, // 2024-01-01
            { 1704067200, MILEAGE_MEDICAL, 0.655 }, // 2024-01-01
            { 1704067200, MILEAGE_PERSONAL, 0.655 }, // 2024-01-01

            // Previous business mileage rates
            { 1672531200, MILEAGE_BUSINESS, 0.585 }, // 2023-01-01
            { 1672531200, MILEAGE_MEDICAL, 0.585 }, // 2023-01-01
            { 1672531200, MILEAGE_PERSONAL, 0.585 }, // 2023-01-01

            // Additional rates can be added here as needed
        };

        const size_t IRS_MILEAGE_RATES_COUNT = sizeof(IRS_MILEAGE_RATES) / sizeof(MileageRates);

        double getMileageRate(time_t date, eMileageCatgories category)
        {
            for (size_t i = 0; i < IRS_MILEAGE_RATES_COUNT; ++i)
            {
                if (IRS_MILEAGE_RATES[i].category == category && 
                    IRS_MILEAGE_RATES[i].start <= date)
                {
                    return IRS_MILEAGE_RATES[i].rate_per_mile;
                }
            }
            // If no rate is found for the given date and category, return 0.0
            return 0.0;
        }
        /** @} */
    }
}