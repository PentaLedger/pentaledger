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
#ifndef _INCOME_TYPES_
#define _INCOME_TYPES_

namespace pentaledger
{
    namespace accounting
    {
        namespace tax
        {
            /**
             * @brief Enumeration for different types of income.
             * In U.S. federal tax law, income is typically 
             * classified into three broad categories — active (or earned), 
             * passive, and portfolio (or investment) income — and each 
             * category has different tax treatments.
             */
            enum class INCOME_TYPE
            {
                //! This is income generated from your labor or active participation in a business.
                //! Examples:
                //!
                //! - Wages, salaries, tips
                //! - Bonuses, commissions
                //! - Net earnings from self-employment
                //! - Income from materially participating in a trade or business
                //!
                //! Tax Treatment:
                //!
                //! - Subject to ordinary income tax rates (10% to 37% as of 2025)
                //! 
                //! Subject to payroll taxes:
                //! 
                //!   - Social Security (6.2% employee + 6.2% employer or 12.4% if self-employed up to the wage base)
                //!   - Medicare (1.45% employee + 1.45% employer or 2.9% if self-employed)
                //!   - Additional Medicare tax of 0.9% on wages above $200,000 (single) / $250,000 (MFJ)
                INCOME_ACTIVE,

                //! This is income from a trade or business in which you do not materially participate, 
                //! or from rental activities (with some exceptions).
                //! Examples:
                //!
                //! - Rental income (unless you’re a real estate professional)
                //! - Limited partnership income
                //! - Businesses in which you’re not actively involved
                //!
                //! Tax Treatment:
                //!
                //! - Taxed at ordinary income rates
                //! - Not subject to payroll taxes
                //!
                //! Passive Activity Loss (PAL) limitations:
                //!   - Losses can usually only offset other passive income unless you meet special rules
                //!     (e.g., up to $25,000 offset for active rental participants with AGI below $100,000)
                //!   - May be subject to Net Investment Income Tax (NIIT) of 3.8% if income exceeds $200,000 (single) / $250,000 (MFJ)
                //!
                //!   - Passive activity losses can only offset passive activity income
                //!   - Passive activity losses cannot offset active income
                //!   - Passive activity losses can be carried forward to future years
                INCOME_PASSIVE,

                //! Income derived from investments in financial instruments.
                //! Examples:
                //! - Interest
                //! - Dividends
                //! - Capital gains
                //! - Royalties (in some cases)
                //! - Annuities
                //!
                //! Tax Treatment:
                //! Interest income → taxed at ordinary rates
                //! Qualified dividends → taxed at capital gains rates (0%, 15%, or 20%)
                //! Capital gains:
                //!   Short-term (held ≤ 1 year) → taxed at ordinary rates
                //!   Long-term (held > 1 year) → taxed at 0%, 15%, or 20%, depending on income
                //!   May be subject to NIIT (3.8%) if above the threshold
                INCOME_PORTFOLIO,
            };
        }
    }
}

#endif // _INCOME_TYPES_