// SPDX-License-Identifier: GPL-2.0-or-later
//! \file account_types.hpp
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
#ifndef _ACCOUNT_TYPES_HPP_
#define _ACCOUNT_TYPES_HPP_

namespace pentaledger
{
    //! \brief Accounting namespace
    //!
    //! This namespace contains all of the accounting related code for the PentaLedger project.
    //!
    namespace accounting
    {

        //! \brief Account Type
        //! 
        enum eAccountType
        {
            //! \brief Asset account
            //!
            //! Asset accounts record assets owned by your company. These accounts
            //! are debited if assets enter the company and are credited if assets
            //! leave the company.
            //!
            //! Some examples of asset accounts include:
            //!
            //! - Accounts receivable
            //! - Cash
            //! - Inventory
            //! - Investments
            //!
            ASSET_ACCOUNT, 

            //! \brief Liability account
            //!
            //! This account type records all of your company’s liabilities (the
            //! company’s debts). Whenever your company incurs more debt, these
            //! accounts are credited to increase liabilities. If your company
            //! makes a payment toward its debt, the liability account is debited.
            //!
            //! The following are examples of liability accounts:
            //!
            //! - Accounts payable
            //! - Notes payable
            //! - Accrued expenses
            //! - Customer deposits
            LIABILITY_ACCOUNT,

            //! \brief Equity account
            //!
            //! Stockholders’ equity can also refer to shareholders’ or owner’s equity.
            //! You can calculate the equity of your company by subtracting the company’s
            //! liabilities from its assets.
            //!
            //! Examples:
            //!
            //! - Common stock
            //! - Retained earnings
            //! - Treasury stock
            EQUITY_ACCOUNT,

            //! \brief Revenue account
            //!
            //! Revenue refers to the assets that your company has earned through its
            //! business activities, such as revenue earned by delivering a service. For
            //! example, if you own a plumbing company and have delivered a plumbing
            //! service to a customer, the service revenue account will be credited
            //! since revenue accounts increase on the credit side.
            //!
            //! Examples:
            //!
            //! - Sales
            //! - Service fee revenues
            REVENUE_ACCOUNT,

            //! \brief Expense account
            //!
            //! Expense accounts represent the expenses that your company has incurred.
            //! This generally includes all money spent on business activities with
            //! the hopes of generating a profit.
            //!
            //! Examples:
            //!
            //! - Salaries
            //! - Rent
            //! - Advertising
            //! - Cost of goods sold
            EXPENSE_ACCOUNT,

            //! Non-operating revenues and gains (Investment Income, Gain on Disposal of Truck)
            NON_OPERATING_REVENUES_AND_GAINS,

            //! Non-operating expenses and losses (Interest Expense, Loss on Disposal of Equipment
            NON_OPERATING_EXPENSES_AND_LOSSES,
        };

    }
}
#endif



