Vendors and Suppliers
#####################

The purpose of this module is to provide accurate tracking and 
categorization of vendor and supplier transactions.

Background
==========

The term *vendor* refers to an individual or entity that sells complete products
or services to your business. By contrast, a *supplier* is a person or business
that provides raw materials, parts, or machinery to manufacture goods.

In PentaLedger, the terms *vendor* and *supplier* are used interchangeably to refer 
to external entities that provide goods or services to your business. Common 
examples include:

- Utility companies
- Freelancers or contractors
- Wholesalers or distributors
- Software or service providers
- Professional services such as attorneys and accountants

The PentaLedger vendor and supplier module is designed to:

- Collect and maintain vendor contact information and tax information
- Track spending on an aggregate or per-vendor basis
- Support 1099-NEC compliance and reporting for eligible vendors

Required Information
====================

Users with sufficient permissions can create new vendor records by providing:

- **Vendor Name**
- **Contact Information** (phone, email, contact person)
- **Address**
- **Tax ID / EIN**
- **Default Expense Account**
- **Payment Terms** (e.g., Net 30)
- **1099 Classification** (if applicable)

Vendor Groups (Optional)
------------------------

Vendors may be grouped by category (e.g., utilities, office supplies, 
contractors) to support reporting and filtering.

Vendor Transactions
===================

Vendor records are linked to various transaction types:

- **Bills**: Record amounts owed for goods/services
- **Bill Payments**: Record payments made to vendors
- **Credit Memos**: Record vendor refunds or adjustments

Each transaction updates the **accounts payable** balance and associated 
**expense accounts**.

Accounts Payable Integration
============================

Vendor bills are automatically posted to the **Accounts Payable** control account.
Payments reduce the A/P balance. The system enforces double-entry accounting to ensure integrity.

Reports
=======

Reports related to vendors include:

- **Vendor Ledger**: Shows all transactions with a specific vendor
- **Aged Payables Report**: Shows outstanding balances by due date
- **1099 Summary**: Summarizes payments to eligible vendors for tax reporting
- **Expense by Vendor**: Summarizes total spending by vendor and category

Audit Trail
===========

All vendor activity is logged and traceable, including:

- Who created or modified a vendor record
- Transaction history
- Payment history

User Stories
============

- As a user, I want to add new vendors and ensure W-9 tax information is received.
- As a landlord, I want to track vendor payments for rent and generate 1099-MISC forms as needed.
- As an accountant, I want to generate an expense report by vendor for budgeting and compliance.
- As an administrator, I want to restrict who can add or modify vendor records.

1099-NEC and 1099-MISC Compliance
=================================

Form 1099-NEC (Nonemployee Compensation) or Form 1099-MISC may be required 
under U.S. tax law when you pay certain vendors for services.

When is a 1099 Required?
------------------------

You must file a **Form 1099-NEC** if all of the following apply:

1. You paid **$600 or more** during the calendar year;
2. The payment was for **services** (not goods or products);
3. The vendor is a **non-employee individual**, **partnership**, or **LLC** taxed as a sole proprietorship or partnership;
4. The payment was made in the course of your **trade or business**;
5. The vendor is **not a C corporation**, *unless* they are an attorney or medical provider.

Special Cases
-------------

- **Attorneys and law firms**: Must receive a 1099-NEC for legal services, even if incorporated.
- **Medical and healthcare providers**: Must receive a 1099-MISC for payments over $600.
- **Payments by credit card or PayPal**: Do *not* require a 1099; these are reported by the payment processor via Form 1099-K.

Not Required
------------

You typically do *not* file a 1099 for:

- Payments to C corporations (except legal or medical services)
- Payments for goods, freight, or merchandise
- Rent payments under $600
- Utility payments

Information You Must Collect
============================

To properly file a 1099, collect the following from each vendor:

- **Legal Name**
- **Business Name** (if applicable)
- **Mailing Address**
- **Taxpayer Identification Number (TIN)** — SSN, EIN, or ITIN
- **Entity Type** (e.g., individual, LLC, partnership)
- **Backup Withholding Status**

W-9 Form
--------

Vendors should complete and return **Form W-9** before payment is issued.
The form certifies their TIN and tax classification.

What to Report on the Form
==========================

.. list-table::
   :header-rows: 1
   :widths: 20 20 60

   * - **Form**
     - **Box**
     - **Description**
   * - 1099-NEC
     - Box 1
     - Nonemployee compensation
   * - 1099-MISC
     - Box 1
     - Rent (if over $600)
   * - 1099-MISC
     - Box 6
     - Medical and health care payments
   * - 1099-MISC
     - Box 10
     - Gross proceeds paid to an attorney

Filing Deadlines
================

.. list-table::
   :header-rows: 1
   :widths: 35 25

   * - **Action**
     - **Deadline**
   * - Provide Copy B to vendor
     - January 31
   * - File 1099-NEC with IRS
     - January 31
   * - File 1099-MISC (paper)
     - February 28
   * - File 1099-MISC (e-file)
     - March 31

Note: Deadlines may vary if they fall on a weekend or legal holiday.

PentaLedger Implementation Notes
================================

In PentaLedger, vendors should be marked as **1099-eligible** during creation.
The following fields should be captured for proper year-end filing:

- TIN
- 1099 type (NEC or MISC)
- Default expense account
- Total eligible payments during the year

The system will support automated generation of 1099 summaries and data exports for filing with the IRS.
