//! \brief Minnesota Computer Formula
//! \file mn_payroll.hpp
//!
//! This contains the computer formula, as specified by the State of Minnesota
//! to calculate Minnesota income taxt to withold from an employee's wages.
//! This is specified in the 
//! \file mn_witholding.hpp
//! \author Joe Turner <joe@agavemountain.com>
//!
//! \brief Calculate Minnesota Income Tax Witholding
//!
//! \copyright Copyright (c) 2020 Joe Turner; All rights reserved.
#ifndef _MN_PAYROLL_HPP_
#define _MN_PAYROLL_HPP_

namespace pentaledger
{
    namespace accounting
    {
        namespace payroll
        {
            //! \brief Minnesota Income Tax Witholding
            //!
            //! This is the Minnesota income tax witholding calculation as specified by the State of Minnesota.
            //!
            //! \todo implement
            //!
            //! \ingroup Payroll
            //!
            //! \note This is not a complete implementation.  It is intended to be used as a starting point.
            //!
        }
    }
}
//! \brief Pay Periods per year.
enum MN_PAY_PERIOD
{
    //! pay by the day
    PAY_PERIOD_DAILY = 360,
    //! you pay by the week
    PAY_PERIOD_WEEKLY = 52,
    //! you pay every two weeks
    PAY_PERIOD_TWO_WEEKS = 26,
    //! you pay twice a month
    PAY_PERIOD_BI_MONTHLY = 24,
    //! you pay once a month
    PAY_PERIOD_MONTHLY = 12
};

struct {
    //! More than
    int     floor;
    //! But not more than
    int     ceiling;
    int     subtract_this;
    double  percent;
    int     add;
};

//! \brief Minnesota witholding factor.  
//! The number of employee's witholding allowances are multiplied by $4,300
const int MN_WITHHOLDING_FACTOR    = 4300;

// Multiply the total wages from step 1 by the number of payroll periods you have in a year. The result is the employee’s annual wage.
// Multiply step 1 by:
// • 360 if you pay by the day
// • 52 if you pay by the week
// • 26 if you pay every two weeks
// • 24 if you pay twice a month
// • 12 if you pay once a month

double MNIT_Witholding_Adjustment(double a_amount, bool isMarried)
{
    double result = 0;

    if (isMarried)
    {
        if (a_amount <= 11900)
        {
            return 0;
        }
        
    }
    return result;
}

//! \brief Calculate Minnesota State income tax witholding using "Computer Formula"
//!
//! \param  a_total_wages
//! \param  a_period
//! \param  a_isMarried
//!
//! \returns
template<typename T>
T mn_calculate_witholding(T a_total_wages, enum MN_PAY_PERIOD a_period, int a_witholding_allwances, bool a_isMarried)
{
    T mn_income_tax_witholding = 0;

    //! Step 2 
    //! Multiply the total wages from step 1 by the number of payroll periods 
    //! you have in a year. The result is the employee’s annual wage.
    //!
    //! Multiply step 1 by:
    //! - 360 if you pay by the day
    //! - 52 if you pay by the week
    //! - 26 if you pay every two weeks
    //! - 24 if you pay twice a month
    //! - 12 if you pay once a month
    T annual_wage = a_total_wages * a_period;

    //! Step 3
    //! Multiply the number of the employee’s withholding allowances by $4,300
    T mn_witholding_allowance = MN_WITHHOLDING_FACTOR * a_witholding_allwances;

    //! Step 4
    //! Subtract the result in step 3 from the result in step 2
    T tmp = annual_wage - mn_witholding_allowance;

    return mn_income_tax_witholding;
}

}
}
}
#endif