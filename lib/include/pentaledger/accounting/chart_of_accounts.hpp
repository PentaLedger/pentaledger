//! \file chart_of_accounts.hpp
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
#ifndef _CHART_OF_ACCOUNTS_HPP_
#define _CHART_OF_ACCOUNTS_HPP_

namespace pentaledger
{
    namespace accounting
    {

                //! \brief Chart of Accounts Record Structure
        //!
        //! A chart of account is a unique list of accounts used to track
        //! financial transactions. 
        //! 
        //! There are five basic account types: asset, liability, income, expense, and equity. 
        //! Accounts are used to track:
        //!
        //! - money coming in (income and revenue); and
        //! - money going out (expenses); and
        //! - what is owed; and 
        //! - value of assets; and 
        //! - equity in the business.
        //!
        struct CHART_ACCOUNT_RECORD
        {
            //! \brief Unique ID for record
            //! Unique identifier for this record.
            uint32_t ID;

            //! \brief Account Number
            //!
            //! User defined account number.  The name must be unique.
            //! Examples include: 1.233.23, 10000, 1-20-3232
            std::string AccountNumber;

            //! \brief Account Name
            //! This is the human readable name of the account, as will be
            //! seen by the user and on reports.
            std::string Name;

            //! \brief Parenet reference id
            //!
            //! If this is a subaccount, this is the id of the parent account.
            uint32_t ParentId;

            //! \brief Description
            //! User entered description for the account.
            std::string Description;

            //! \brief Active
            //! This value defines whether or not this account in inactive.
            //! If this account is inactive, it might be hidden for most
            //! display purposes and cannot be posted to.
            bool Active;

            //! \brief SubAccount status
            //!
            //! This boolean flag is true if this is a subaccount.  If this
            //! is a subaccount, parent 
            bool SubAccount;

            //! \brief Account Type / Classification
            //!
            //! ASSET, EQUITY, LIABILTY, etc.
            uint32_t Classification;

            //! \brief Current Balance
            //! DECIMAL(19,4)

            //         CurrentBalance
            //             CurrentBalanceWithSubaccounts

            //                 //! \brief Last update time
            //                 //!
            //                 time_t LastUpdateTime;
            // Classification //!< revenue, income, etc.

            //     //! \brief Subaccount
            //     //! If this is true, this is a subaccount of another account.
            //     SubAccount;

            //! FullyQualifiedName: String, filterable, sortable, default is derived
            //! from Name and ParentRef Fully qualified name of the entity.
            //! The fully qualified name prepends the topmost parent, followed
            //! by each sub element separated by colons. Takes the form of
            //! Parent:Account1:SubAccount1:SubAccount2. Typically returned
            //! from an existing object and not input on a new object.
            //! Constraints:Limited to 5 levels.
            std::string account_type;
        };


        //! \brief Create a new chart account
        //!
        //! Create a new account to be inserted in the chart of accounts.
        //! The account number must be unique and cannot exist in the 
        //! database.
        //!
        //! \param rec      Pointer to structure populated with the data
        //!                 to insert into the chart of accounts.
        //!
        //! \returns
        //! This function will return the new ID for the new chart account
        //! if the call succeeds.  If the call fails, the return value will
        //! be negative.
        int create_account(const struct CHART_ACCOUNT_RECORD *rec);

        int delete_account(int id);

        int update_record(const struct CHART_ACCOUNT_RECORD *rec);

        int get_record(struct CHART_ACCOUNT_RECORD *rec);
    }
}

// create
// delete
// obtain walk through the structure
// update

#endif
