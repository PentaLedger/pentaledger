Gambling
########

Since it is important to understand the underlying issues in order to build a 
complete accounting system, this document lays out the distilled essence of many hours of 
research into the tax requirements, court cases, and guidance relating to the complex tax 
issues that arise out of recreational gambiling.

All transactions within the gambling module are non-posting, meaning they will not
modify any of the general ledger transaction journals.  It exists solely to tabulate values 
to make tax preparation easier (and more accurate) when it is time.

The gambling module within the accounting system should accurately tabulate
the expenses and income due to gambling to:

- present a complete picture of the financial impact of gambling on your finances; and 
- calculate the win/loss values for your federal, state and city tax returns.

Background
==========

Gambling is a niche tax topic within the universe of tax accounting, and for good reason. 
Tax regulations don't cover all the issues, and most of the guidance must be taken
from tax court cases.  

More often than not, the stadard advice given online is misleading or flat out wrong. 
Worse, tax professionals sometimes disagree on application to taxes when dealing
with multiple tax jurisdictions.  Also, the rules as they are applied vary from casino 
to casino.  

In principle, taxes on gambling winnings and losses is simple:

- All gambing winnings, regardless if illegal or legal, must be declared as income, 
  regardless of where it was done world wide.  For recreational gamblers, this would 
  be declared on line 21 of the 1040 tax return.
- Losses can be deducted, **but only up to the amount of winnings**, on a seperate
  line on the return.

Gambling income is almost punative, in that it increases your Adjusted Gross Income (AGI)
and can inflate your income, forcing you to loose tax deductions and/or credits 
that are based on income.

Many casual recreational gamblers don't keep any records or declare their wins, usually 
because they are usually at a net loss.  The problem arises when a recreational gambler 
wins a substantial jackpot and has to scramble to learn the tax laws, sometimes in
multiple tax jurisdictions or overpay in taxes.  Others, get audited and 
find substatial pentalties awaiting them when the IRS auditor disregards their 
woefully inadiquate supporting evidence. 

Terms and abbreviations
-----------------------

A “specific wager” is the smallest unit of gambling time.  "Wagering activity" would 
be synonymous with a gambling "session."  Niether term is defined in IRS regulation,
but tax court cases.

"Gambling Establishment" is a business that provides and accepts wagers.   This is more 
generic term that includes casinos, horse tracks, sports books, etc.



Scope
=====

Currently, the gambiling module is limited to recording and tracking gambling activities
for individuals.  Groups, partnerships, or syndicates are not currently in 
scope for this release.

The following scenarios are out of scope for the this release:

- Groups, partnerships, or gambling syndicates that may or may not be formed
  as a partnership, LLC, or corporation.  Or disburse 1099s or re-allocate
  winnings and/or losses to other parties.
- Fantasy sports
- Crypto currency transactions relating to gambling
- Foreign currency transactions (gambling outside the U.S.)
- Tournament play where tournament fees must be imputed differently by U.S. laws


IRS Record Keeping Requirements
===============================

The vast majority of gamblers don't keep records of their gambling activity, and 
scramble to address tax issues from a large jackpot win to avoid paying grossly 
inflated taxes.  

The IRS requires recreational and professional gamblers to keep a contemporanious 
diary or log of gambling, with supportive evidence in the event of an 
audit.  Relying on win/loss statements from a casino is simply inadiquate in 
most cases.

A diary or similar record of your losses and winnings. Your diary should contain at 
least the following information: 

- The date and type of your specific wager or wagering activity.
- The name and address or location of the gambling establishment. 
- The names of other persons present with you at the gambling establishment.
- The amount(s) you won or lost.
- Proof of winnings and losses.

Travel Imputed as Loss
======================
While most armchair internet accountants would readily tell you that travel costs cannot be 
added to losses, or that you need to be a professional gambler to do so, this is incorrect.
Travel directly to and from the gambling establishment are allowed to be counted
in the loss[#]_.  I take this to mean airfare and/or mileage expense only to and
from the gambling establishment. 

Supporting Evidence
===================

Supporting evidence needs to be kept to substanciate deductions during an audit.

Lottery Tickets
---------------

Lottery Tickets, Keno, Scratch-Offs, and Horse Races.  The tickets themselves
are supporting evidence and should be kept.  Purchase of the ticket is counted
as a loss, and any prizes won counted as gambling income. 

W2G and 1099s
-------------

Gambling establishments are required to issue W2Gs or 1099 forms to you in variety of 
circumstances.  In some cases you can elect to have tax witheld, and in others you
are required to have tax witheld by the gambling establishment.  

It is important to note that the W2Gs received might not match your actual gambling 
activity documented in your gambling logs. 



Lorem ipsum [#]_ dolor sit amet ... [#]_

.. rubric:: Footnotes

.. [#] [Gambling Winnings and Losses (ASL) - YouTube video text script](https://www.irs.gov/newsroom/gambling-winnings-and-losses-asl-youtube-video-text-script)
.. [#] Text of the second footnote.

Gambling 

API 
===

+--------+---------------------------------+----------------------------------------------+
| METHOD | URL Pattern                     | Handler                                      | 
+========+=================================+==============================================+
| GET    | /v1/cid/gambling                |   Get summary of Gambling                    |  
+--------+---------------------------------+----------------------------------------------+
| GET    | /vi/cid/gambling/lottery        |   Get summary of lottery wins and losses     |  
+--------+---------------------------------+----------------------------------------------+

Example Reports
===============

Gambling Detail - Contains gambling summary as well as the details of gambling 
for the specified period.

Gambling Tax Summary - summary to the specified period, without details.

.. code-block::

       Gambling Tax Summary
       January 1, 20XX to December 31, 20XX

       Summary
       Gambing Income (Winnings)
          Lottery                 26.00
          Horse Racing           136.00
          Casino Table Games    1823.00
          Slot Machines          200.00
          Fantasy sports           0.00

      Gambling Losses 
          Lottery                 26.00
          Horse Racing           136.00
          Casino Table Games    1823.00
          Slot Machines          200.00
          Fantasy sports        

      Gambling Travel
        Travel Mileage          1322.32
        Travel Airfare             0.00
        Lottery                 1000.00


