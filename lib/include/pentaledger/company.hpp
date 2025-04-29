#pragma once

#include <string>

namespace pentaledger {

/**
 * @brief Represents a company in the system.
 * 
 * This structure maps to the companies table in the database.
 */
struct Company {
    std::string id;         ///< Unique identifier (UUID)
    std::string name;       ///< Company name
    std::string tax_id;     ///< Company tax identification number
    std::string created_at; ///< Timestamp when the record was created
    std::string updated_at; ///< Timestamp when the record was last updated
};

} // namespace pentaledger 