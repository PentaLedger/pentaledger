Chart of Accounts
#################

The chart of accounts is the foundation of the accounting system in PentaLedger.
This chapter explains how accounts are structured, how to manage them via the API or user interface, and how they integrate with journal entries and financial reports.

Overview
========

The chart of accounts (COA) is a structured list of account codes used to classify all financial transactions in the system.
Each account belongs to a category (e.g., asset, liability, income, expense) and supports double-entry accounting.

Features of the chart of accounts include:

- Support for hierarchical account structures (e.g., 1000 Assets → 1100 Cash → 1110 Bank of America)
- Built-in account types for general ledger enforcement
- API access for account management
- CSV export for review, compliance, and integration

API Access
==========

The PentaLedger API exposes the chart of accounts for each company via the following endpoint:

::

  GET /v1/<cid>/accounts

Where `<cid>` is the company or entity ID.

Authenticated users with appropriate permissions can:

- View the full chart of accounts
- Add, update, or archive accounts
- Export the account list in CSV format

Editing the Chart of Accounts
=============================

Users with editor or admin-level permissions can manage the chart of accounts through the web interface or API.
Editable fields include:

- **Account Number** (e.g., 1000, 2000.01)
- **Account Name** (e.g., "Cash", "Accounts Receivable", "Sales")
- **Account Type** (Asset, Liability, Equity, Revenue, Expense)
- **Parent Account** (for nested structure)
- **Tax Category** (optional, for reporting)
- **Notes** (optional descriptive text)

Some accounts may be locked from editing if they are system-defined or already contain posted transactions.

CSV Export
==========

Users may download the chart of accounts in CSV format using the web interface or API.

Each exported row includes:

- Account Number
- Account Name
- Account Type
- Parent Account (if applicable)
- Tax Category (if used)
- Active/Archived Status

This is useful for auditing, backups, or importing into spreadsheet-based reports.

Best Practices
==============

- Use consistent account number ranges to group account types:
  
  - 1000–1999: Assets
  - 2000–2999: Liabilities
  - 3000–3999: Equity
  - 4000–4999: Income
  - 5000–5999: Cost of Goods Sold
  - 6000–7999: Expenses
  - 8000–8999: Other Income/Expense

- Use sub-accounts to improve categorization but avoid excessive depth.
- Lock accounts once a fiscal period is closed to ensure ledger integrity.

Future Features
===============

Planned enhancements to the chart of accounts module include:

- Versioning and history of account structure changes
- Templates for common industry COAs
- Import wizard for onboarding existing COAs from other systems
- Validation tools for ensuring compliance with tax and GAAP rules
