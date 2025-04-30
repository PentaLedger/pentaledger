#pragma once

#include <string>

namespace pentaledger {
namespace db {

/**
 * @brief Represents a company in the system.
 * 
 * This structure maps to the companies table in the database.
 * Companies can form a hierarchy through the parent_id field.
 */
struct Company {
    std::string id;         ///< Unique identifier (UUID)
    std::string name;       ///< Company name
    std::string tax_id;     ///< Company tax identification number
    std::string parent_id;  ///< UUID of the parent company (optional)
    std::string created_at; ///< Timestamp when the record was created
    std::string updated_at; ///< Timestamp when the record was last updated
};

} // namespace db
} // namespace pentaledger 