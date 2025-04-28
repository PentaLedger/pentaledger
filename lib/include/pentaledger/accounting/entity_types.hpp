// SPDX-License-Identifier: GPL-2.0-only
//! \file account_types.hpp
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
#ifndef _ENTITY_TYPES_HPP_
#define _ENTITY_TYPES_HPP_

namespace pentaledger
{
    namespace accounting
    {

        //! \brief Entity
        //!
        enum GL_ENTITY_TYPE
        {
            //! \brief Individual
            //!
            //! Individual taxpayer who files a 1040 tax return and/or 
            //! one or more state tax returns.
            ENTITY_INDIVIDUAL,

            //! \brief Sole Proprietor 
            //!
            //! This is an entity type to seperate the accounting of an individual
            //! from their sole proprietorship, either a DBA or Single Member LLC (SMLCC)
            //! with a disregarded tax status.
            ENTITY_SOLE_PROP,

            //! \brief Limited Liability Company
            //!
            //! LLC has a board of govenors, and instead of shares, they have membership interest.
            ENTITY_LLC,

            //! \brief Corporation
            //!
            //! A corporation has a board of directors, shares of ownership
            ENTITY_CORPORATION

        };

    };

#endif
