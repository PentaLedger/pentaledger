Vehicles and Vehicle Expenses
#############################

Background
==========

Tracking mileage for tax deductions and/or employer reimbursement 
can be a major hassle.  However, not doing this properly can have 
significant financial impacts. 

A mileage log is required whether you take the standard mileage deduction 
or actual expenses.

While the vast majority of mileage logs simply track mileage 
with the assumption that you self-employed and only have one business,
the reality for many of us is farm more complex.

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

The following features are out of scope for this release:

* Calculate IFTA taxes.
* Record GPS coordinates during logging (records must be manually entered).
* Manage a fleet of vehicles 
* Manage work orders or inventory of consumable maintenance materials (filters, oil, parts)
* Fuel stop planning
* Calculate Fuel tax credit(s)
* Marine vessels and aircraft

Vehicle Information Record
==========================

Per FMCSA/DOT regulations (part 393), records for trailers and/or vehicles must contain at 
minimum:

-	Company number (unit number), also may be called a fleet number
-	Make, model, year
-	Serial Number (VIN number if applicable)
-	Tire size
-	Owner (if leased)

The vehicle record must contain the above information.

Mileage Log
-----------

Regardless of whether the user decides to utilize the standard
mileage method or actual expenses method, a vehicle mileage log is
required to substanciate automotive deductions.

Business vs. Personal Use
=========================

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


IRS Mileage Log Requirements
============================

**Odometer readings.** Odometer reading must be logged for the beginning and the end 
of each year, and when you start using a new vehicle.  These odometer readings
are used to calculate the total miles driven during the year.  Knowing the 
total mileage driven in a calendar year enables us to be able to calculate the
percentage of business and personal use.

There are no requirements for how you track your mileage, except that you have to 
record the mileage of each trip. That means either

* recording the odometer at the beginning and end of the trip, or
* tracking/recording your trips differently, for instance using a GPS device or a mileage tracking mobile application.





Scenario 1: Personally Owned Vehicle, Multiple Reimbursements
-------------------------------------------------------------
Joe works a regular job for Big Company, Inc.  In addition, Joe has
several side hustles, as well as rental real estate.  Joe also
is the sole shareholder and owner of an Limited Liability Corporation,
which has elected to be taxed as an S Corporation.

Most mileage logs are focused on business vs personal. 

Scenario 2: Commercial Motor Vehicle
------------------------------------
tbd.

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

Vehicles
--------

.. code-block::

       pentaledger vehicle list
       VID YEAR MAKE         
       1   2019 FORD F-250

Fuel Stops
==========

Fuel stop is where you stop to refuel your fuel tank.  It may or many not
be associated with a Trip ID. 

There are several methods.  
- I want to accumulate all of the expenses taken during a trip, to 
  caculate how much .
- I want to accumuluate all fuel stops and average MPG, to determine if
  any repairs or corrective actions are necessary. 

I am an individual and simply want to determine how expensive it is
to operate my vehicle(s).

I am an individudal that works a W2 wage earning, and am due reimbursement 
for mileage.

I am a small business owner that must track mileage for one or more 
busineses and/or investement properties.

.. code-block::

       pentaledger vehicle log