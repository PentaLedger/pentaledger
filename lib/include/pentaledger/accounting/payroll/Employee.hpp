
//! \file Employee.hpp
//! \author Joe Turner <joe@agavemountain.com>
//!
//! \copyright
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

#ifndef _EMPLOYEE_HPP_
#define _EMPLOYEE_HPP_

namespace ioi
{
    namespace accounting
    {

        namespace payroll
        {

            //! \brief Tax Return Filing Status.
            //! The employee's anticipated filing status. This will
            //! determine the standard deduction and tax rates used to
            //! compute the employee's withholding.
            enum eFilingStatus
            {
                //! \brief Single Tax Filing Status
                eSINGLE,

                //! \brief Married Filing Status, filing seperately.
                //! Married filing separately is a tax status for married couples
                //! who choose to record their respective incomes, exemptions,
                //! and deductions on separate tax returns.
                eMARRIED_FILING_SEPERATELY,

                //! \brief Married Filing Status, filing jointly.
                // Married Filing Jointly or Qualifying Widow(er)
                eMARRIED_FILING_JOINTLY,

                //! \brief Head of Household Filing Status
                //! Head of household is a filing status on tax returns used by
                //! unmarried taxpayers who support and house a qualifying person.
                //! Taxpayers may file tax returns as head of household (HOH) if
                //! they are unmarried and pay more than half the cost of supporting
                //! and housing a qualifying person.
                eHEAD_OF_HOUSEHOLD
            };

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
        };
    };
};

#endif