#pragma once

#include <string>
#include <chrono>

namespace pentaledger {
namespace db {

/**
 * @brief Represents a gambling log entry in the system.
 * 
 * This structure maps to the gambling_log table in the database.
 * It tracks gambling activities including winnings, losses, and establishment details.
 */
struct GamblingLog {
    std::string id;                 ///< Unique identifier (UUID)
    std::string date;               ///< Date of the gambling activity (YYYY-MM-DD)
    std::string establishment_name; ///< Name of the gambling establishment
    std::string establishment_address; ///< Address of the gambling establishment
    std::string time_of_day;        ///< Time of the gambling activity (HH:MM:SS)
    std::string wagering_type;      ///< Type of wagering (e.g., "Slots", "Poker", "Blackjack")
    std::string location_id;        ///< Location identifier
    double w2_winnings;             ///< W2 reportable winnings
    double winnings;                ///< Total winnings
    double losses;                  ///< Total losses
    std::string notes;              ///< Additional notes
    std::string created_at;         ///< Timestamp when the record was created
    std::string updated_at;         ///< Timestamp when the record was last updated
};

} // namespace db
} // namespace pentaledger 