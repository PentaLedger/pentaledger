#pragma once

#include <string>

/*! \mainpage

Welcome to PentaLedger

This page should have a brief description of what the component or
entity being documented does.  Additionally, links to design
information, requirements traceability, and revision history
should be provided along with any other information that might
be useful to a developer, QA person, or product engineer.

When producing the documentation for your component, use the
files provided in this template and make the appropriate changes
to the Doxygen configuration file ("Doxyfile"):
the following areas:
-# PROJECT_NAME tag: change COMPONENT_NAME_HERE to the name of your component
-# CHM_FILE tag: change the name from SAMPLE.CHM to be more representative of your component.
                  Be sure to keep the "..\" prefix.
-# INPUT tag: add additional directories as needed (be sure to use relative paths)


Topics:
- \subpage design
- \subpage requirements
- \subpage history

Questions, comments, concerns, or dissenting opinions should be directed 
to <YOUR NAME>, <YOUR E-MAIL>, <YOUR PHONE #>

*/

namespace pentaledger {

/**
 * @brief Main class for the PentaLedger library.
 * 
 * This class provides the core functionality for ledger management.
 * It handles version information and basic ledger operations.
 */
class PentaLedger {
public:
    /**
     * @brief Construct a new PentaLedger object.
     * 
     * Initializes the ledger with default version "0.1.0".
     */
    PentaLedger();

    /**
     * @brief Destroy the PentaLedger object.
     */
    ~PentaLedger();

    /**
     * @brief Get the current version of the ledger.
     * 
     * @return std::string The version string.
     */
    std::string getVersion() const;

    /**
     * @brief Set the version of the ledger.
     * 
     * @param version The new version string to set.
     */
    void setVersion(const std::string& version);

private:
    std::string version_; ///< Current version of the ledger
};

} // namespace pentaledger 