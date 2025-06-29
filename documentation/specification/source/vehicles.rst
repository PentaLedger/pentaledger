Vehicles and Vehicle Expenses
#############################

The purpose of this module is to provide accurate tracking and 
categorization of vehicle mileage for personal, investent and business purposes, 
supporting compliant and optimized tax reporting, reimbursable mileage 
tracking, and performance insights for vehicles. This feature will 
aid users in keeping IRS-compliant mileage logs, simplifying tax 
preparation, and understanding vehicle efficiency trends.

Background
==========

Tracking mileage for tax deductions and/or employer reimbursement 
can be a major hassle.  However, not doing this properly can have 
significant financial impacts. 

A mileage log is required whether you take the standard mileage deduction 
or actual expenses deduction.

While the vast majority of mileage logs simply track mileage 
with the assumption that you self-employed and only have one business,
the reality for many of us is far more complex.

The PentaLedger vehicle mileage and expense module is designed to:

* Maintain a log of business use of a personal vehicle and 
  properly calculate the percentages of business use versus personal
  use.

* Attribute and categorize mileage for other deductable tax purposes,
  such as charity, gambling, investment, and medical mileage.

* Attribute and categorize mileage for reimbursed mileage driven
  for a W-2 employer.

* Attribute and categorize mileage for different self-employed 
  businesses (i.e., Schedule C), where appropriate.

* Attribute and categorize mileage for different investments
  (i.e., Schedule E) where appropriate.

* Record fuel stops and automatically calculate fuel mileage (Miles per Gallon),
  which can be used as a measure of vehicle performance over time.

Terms and abbreviations
-----------------------

- The Department of Transportation (DOT) is the agency that regulates commercial 
  motor vehicles.
- The Federal Motor Carrier Safety Administration (FMCSA) also regulates commercial
  motor vehicles.

Scope
=====

In Scope
--------

* Logging of mileage by purpose and business context (e.g., self-employment, investments, W-2 reimbursement).
* Categorization of mileage for tax-deductible purposes (business, medical, charitable, etc.).
* Tracking fuel purchases and automatically calculating miles per gallon (MPG).
* Reporting on business vs. personal use percentages.
* Supporting multiple vehicles and associating them with different business entities or uses.
* Exportable and auditable logs for IRS substantiation.

Out of Scope
------------

The following features are out of scope for this release:

* Calculate IFTA taxes.
* Record GPS coordinates during logging (records must be manually entered).
* Manage a fleet of vehicles 
* Manage work orders or inventory of consumable maintenance materials (filters, oil, parts)
* Fuel stop planning
* Calculate Fuel tax credit(s)
* Marine vessels and aircraft
* Real-time GPS tracking (initial version will rely on manual entry).
* Integration with third-party mileage tracking apps (may be future roadmap).
* Automatic detection of trip purpose (manual classification required initially).
* Calculating depreciation for business use of a vehicle.

User Stories
============

* As a self-employed contractor, I want to log my business trips separately from personal trips so that I can maximize my Schedule C deductions.
* As a landlord, I want to log trips to properties and assign them to specific units so that I can properly categorize Schedule E mileage.
* As a W-2 employee, I want to track reimbursed mileage so that I can cross-check reimbursements or deduct unreimbursed expenses.
* As a taxpayer, I want to record charitable and medical trips so that I can deduct them where allowed.
* As a user, I want to monitor fuel efficiency so that I can detect maintenance issues or inefficiencies.

Use Cases
=========

Personally Owned Vehicle, Multiple Reimbursements
-------------------------------------------------------------
Joe works a regular job for Big Company, Inc.  In addition, Joe has
several side hustles, as well as rental real estate.  Joe also
is the sole shareholder and owner of an Limited Liability Corporation,
which has elected to be taxed as an S Corporation.

The application must track mileage for each vehicle, and allow Joe to:

* calculate the expected expense reimbursement from Big Company, Inc.
* calculate the percentage of business use for tax reporting
* track mileage used in side hustles (for schedule C or reimburement)
* track mileage used in rental real estate (for schedule E)
* track mileage used in S Corporation 
* track mileage used in other investments (for schedule E)

Requirements
============

IRS Mileage Log Requirements
----------------------------

Regardless of whether the user decides to utilize the standard
mileage method or actual expenses method, a vehicle mileage log is
required to substanciate automotive deductions.

**Odometer readings.** Odometer reading must be logged for the beginning and the end 
of each year, and when you start using a new vehicle.  These odometer readings
are used to calculate the total miles driven during the year.  Knowing the 
total mileage driven in a calendar year enables us to be able to calculate the
percentage of business and personal use.

There are no requirements for how you track your mileage, except that you have to 
record the mileage of each trip. That means either:

* recording the odometer at the beginning and end of the trip, or
* tracking/recording your trips differently, for instance using a GPS device or a mileage tracking mobile application.

Vehicle Information Record
--------------------------

Per FMCSA/DOT regulations (part 393), records for trailers and/or vehicles must contain at 
minimum:

-	Company number (unit number), also may be called a fleet number
-	Make, model, year
-	Serial Number (VIN number if applicable)
-	Tire size
-	Owner (if leased)

The vehicle record must contain the above information.

Fuel Stops
----------

Fuel stop is where you stop to refuel your fuel tank.  Using odometer readings
and fuel stop data, the fuel consumption can be calculated.  This can be used
to track fuel efficiency over time.

Business vs. Personal Use
-------------------------

Whether you take the standard deduction or the actual expense method, you must
calculate the percentage of business use for the vehicle.  The question 
arises when a personal vehicle is used various endevors which may or may
not be reimbursable or deductable.

Therefore, for the purposes of calculating the percentage of business use of
a personal (or company owned) vehicle, the following broad categorization will
be applied.

+------------+------------------------------------------------------+----------+----------+
| TYPE       | Description                                          | Business | Personal |
+============+======================================================+==========+==========+
| PERSONAL   | Personal Mileage is never deductable or reimbursable |   No     |   **YES**|
+------------+------------------------------------------------------+----------+----------+
| CHAIRITY   | Mileage for charitable purposes                      |   No     |   **YES**|
+------------+------------------------------------------------------+----------+----------+
| MOVING     | Mileage for moving                                   |   No     |   **YES**|
+------------+------------------------------------------------------+----------+----------+
| INVESTMENT | Mileage for investment (Sched. E)                    | **YES**  |   NO     |
+------------+------------------------------------------------------+----------+----------+
| GAMBLING   | Mileage to from Gambling Establishment               |   No     |   **YES**|
+------------+------------------------------------------------------+----------+----------+
| MEDICAL    | Mileage for medical appointments, lab work, etc.     |   No     |   **YES**|
+------------+------------------------------------------------------+----------+----------+
| REIMBURSED | Mileage that will be reimbursed to you, as an        | **YES**  |   NO     |
|            | employee.                                            |          |          |
+------------+------------------------------------------------------+----------+----------+

Data Model
==========

Reports
=======
* Vehicle usage summary by category
* MPG over time (graph)
* IRS audit-ready trip log
* Annual deduction summary by vehicle, purpose, and business

Vehicles
--------

.. code-block::

       pentaledger vehicle list
       VID YEAR MAKE         
       1   2019 FORD F-250

Mileage Summary
---------------
.. code-block::

       Mileage Summary (1/1/2025 - 1/30/2025)
       2019 FORD F-250 (VIN 12345678901234567)

       DATE     START   END   MILEAGE TYPE     PURPOSE                      Rate  Amount
       1/1/2025  10000  10500  0      ODOMETER Odometer check               0.70
       1/2/2025  10500  11000  500    BUSINESS Business trip to client site 0.70  $350.00
                                      Business - Big Company, Inc.
       1/3/2025  11000  11500  500    PERSONAL Personal trip to Home Depot  0.70  $350.00
                                      Personal 
       1/4/2025  11500  12000  500    PEROSNAL Gambling trip to Casino      0.70  $350.00
                                      Gambling
        ...

       Mileage Summary:
       Business
         Big Company, Inc:    $350.00 (x% business)
         Uber:                $100.00 (x% business)
         Lyft:                $50.00 (x% business)
         ...
       Personal 
         Gambling:            $350.00 (100% personal)
         ...
       Total:                $1050.00

Fuel Summary
------------
.. code-block::

       Fuel Summary
       2019 FORD F-250 (VIN 12345678901234567)

       DATE     MILEAGE   PURPOSE            FUEL TYPE   GALLONS PRICE TOTAL
       1/1/2025  10000  Love's Travel Center  Gasoline   10.00      $2.50   $25.00
       1/3/2025  10500  Flying J              Gasoline   15.00      $3.00   $45.00

      Summary:
      Miles Driven: 10000
      MPG: 25
      Fuel Cost: $70.00
      ...

UX/UI Considerations
===================

TBD.

Compliance
==========

TBD.


Future Enhancements (Post-MVP)
==============================

Commercial Vehicles
------------------- 

Maintenance record keeping. 
 
- subject rented greater of 30 days
- owned or leased vehicles.

CMV Maintenance of Commercial Motor Vehicles (CMVs), as well
as owner park 396 requires, subject to audit.

part 396.3 basic identifying for power units and trailers (unit numbers) 
Identification of the vehicles (including company number or unit number)
make, vin, year and tire size.
If not owned by company, it shall contain the name of the company/entity that 
furnishing the vehicle.

Up to date periodic inspection reports
Annual vehicle inspection (396 appendix A) (current and last periodic inspection report for
last report [14 month retention]).
Inspector qualifcations. Retained during inspections + 1 year.
Passenger carriers, records of tests contected on emergency door lights,
push out doors, etc.

Regulatory obligation - preventative maintenance program.
- Means to indicate of the nature and due date of the mainteance operation (PM schedule)
- Record of all such inspection or maintenance, repair orders, invoices, etc.
- Retension 12 months after generated.

DVIRs - property or passenger 396.11.  Driver inspects and prepares DVIRs, 
sign and submit to operating MC.  If repairs, DVIR must be signed off by
mechanic.  Retention - 3mo after they are generated.










