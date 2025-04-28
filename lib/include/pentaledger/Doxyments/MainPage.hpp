/*! \mainpage

Welcome to PentaLedger

This page should have a brief description of what the component or
entity being documented does.  Additionally, links to design
information, requirements traceability, and revision history
should be provided along with any other information that might
be useful to a developer, QA person, or product engineer.

PentaLedger is a ledger system for the PentaLedger project.

Topics:
- \subpage design
- \subpage requirements
- \subpage history

Questions, comments, concerns, or dissenting opinions should be directed 
to joe.turner@infinity-surge.com

  \section Categories
 Click on the link(s) below on the description of some of the code:

 - \ref designpatterns


 \tableofcontents

 \section Requirements

 - Doxygen 1.8.0+ (for markdown support) and GraphViz.
 - GNU GCC toolchain
 - Git (obviously)
 - CPPUNIT (for unit tests)

\section make Building and Installing

 \code
 $ mkdir build
 $ cmake ..
 $ make; make install
 \endcode

 \section Generating Documentation

 This project uses doxygen to generate the documentation.  To generate
 this documentation, you must have doxygen installed.  Simple execute doxygen:
 \code
 $ make doc
 \endcode

 \section Running Unit Tests

 You can run unit tests (if cppunit is installed on your development workstation):

 \code
 $ ctest -V
 \endcode
*/
