Company Entities
================

A PentaLedger "business/company entity" is an a individual or business concern that requires 
a set of books, and pays taxes, or has other regulatory submissions required.  

+-------------+---------------------------------+----------------------------------------------+
| Enumeration | URL Pattern                     | Description                                  | 
+=============+=================================+==============================================+
| 0           | Individual or Joint Tax Payer   | A taxpayer that files a 1040 tax form.       |  
+-------------+---------------------------------+----------------------------------------------+
| 1           | Sole Proprietorship             | Wholy owned business by an individual,       | 
|             |                                 | reported on a Schedule C tax form attached to|
|             |                                 | owner's 1040.                                |  
+-------------+---------------------------------+----------------------------------------------+
| 2           | Single Member LLC               | Wholy owned business by an individual,       |
|             |                                 | reported on a Schedule C tax form attached to|
|             |                                 | owner's 1040.                                |  
+-------------+---------------------------------+----------------------------------------------+
| 3           | Corporation                     | A corporation is a legal entity that is      |
|             |                                 | separate from its owners.                    |
+-------------+---------------------------------+----------------------------------------------+
| 4           | Partnership                     | A partnership is a legal entity that is      |
|             |                                 | separate from its owners.                    |
+-------------+---------------------------------+----------------------------------------------+
| 5           | Limited Liability Partnership   | A limited liability partnership is a legal   |
|             |                                 | entity that is separate from its owners.     |
+-------------+---------------------------------+----------------------------------------------+
| 6           | PAC                             | A Political Action Committee is a legal      |
|             |                                 | entity that is required to file FEC reports. |
+-------------+---------------------------------+----------------------------------------------+
| 7           | Non-Profit                      | A non-profit is a legal entity that is       |
|             |                                 | separate from its owners.                    |
+-------------+---------------------------------+----------------------------------------------+

Individual or Joint taxpayer
----------------------------

Sole Proprietorship
-------------------

Single Member LLC 
-----------------

Corporation
-----------
A single member LLC (SMLLC) is a disregarded entity for tax purposes, and does not provide 
any tax benefits. The income and losses "flow up" onto the owners 1040. 