#pragma once

#include <string>

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