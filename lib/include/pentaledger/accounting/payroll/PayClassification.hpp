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
#ifndef _PAY_CLASSIFICATION_HPP_
#define _PAY_CLASSIFICATION_HPP_

namespace pentaledger {
namespace accounting {
namespace payroll {

       enum ePayClassification
        {
            ePAY_NONE,

            //! \brief Hourly Employee
            //! An hourly employee is paid based on an hourly amount.  Hourly employees 
            //! don't have a contract and are only paid for hours worked. The employer determines 
            //! the hours for an hourly employee each week. Hourly employees must document their 
            //! work by using a time card system or completing a timesheet, which the employer 
            //! verifies. The timekeeping method you use must be complete and accurate. 
            //!
            //! There is no federal requirement that an hourly employee must be given a specific number 
            //! of hours of work a week. Employees who work less than full-time are considered part-time, 
            //! and they may have different pay rates, benefits, and paid time off than full-time hourly 
            //! employees.
            //!
            //! Gross Pay = Annual salary / Total number of pay periods
            ePAY_HOURLY,

            //! \brief Salary Employee (Exempt)
            //! A salaried employee is paid based on an annual amount, called a salary. This salary is 
            //! divided between the pay periods (as determined by the company) for the year and based
            //! on a 2080-hour year. Some salaried employees are given an employment contract.
            //!
            //! Gross Pay = Annual salary / Total number of pay periods
            ePAY_SALARY,
        };
        
} // payroll
} // accounting
} // infinity

#endif
