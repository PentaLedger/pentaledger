// SPDX-License-Identifier: GPL-2.0-only
//! \file PayClassification.hpp
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
#ifndef _EMPLOYEE_FILING_STATUS_HPP_
#define _EMPLOYEE_FILING_STATUS_HPP_

/** @addtogroup Payroll  My group B description
  *  @{ */


namespace pentaledger
{
    namespace accounting
    {
        namespace payroll
        {

            //! \brief Tax Return Filing Status
            //!
            //!  The employee's anticipated filing status. This will
            //! determine the standard deduction and tax rates used to
            //! compute the employee's withholding.
            enum eFilingStatus
            {
                //! \brief Single Tax Filing Status
                eSINGLE,
                //! \brief Married Filing Status, filing seperately
                eMARRIED_FILING_SEPERATELY,
                //! \brief Married Filing Status, filing jointly
                //
                // Married Filing Jointly or Qualifying Widow(er)
                eMARRIED_FILING_JOINTLY,
                //! \brief Head of Household Filing Status
                eHEAD_OF_HOUSEHOLD
            };

        } // payroll
    }     // accounting
} // infinity

  /** @} */

#endif
