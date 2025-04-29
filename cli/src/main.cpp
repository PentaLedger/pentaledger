/**
 * @file main.cpp
 * @brief Main entry point for the PentaLedger command-line utility.
 */

#include <iostream>
#include <iomanip>
#include "pentaledger/pentaledger.hpp"
#include "pentaledger/database.hpp"
#include "pentaledger/utility/Environment.hpp"

/**
 * @brief Lists all companies from the database.
 * 
 * @param db The database connection to use
 */
void listCompanies(pentaledger::Database& db) {
    try {
        auto companies = db.getCompanies();
        
        if (companies.empty()) {
            std::cout << "No companies found in the database." << std::endl;
            return;
        }

        // Print header
        std::cout << std::left << std::setw(36) << "ID"
                  << std::setw(30) << "Name"
                  << std::setw(20) << "Tax ID"
                  << std::setw(30) << "Created At"
                  << std::setw(30) << "Updated At" << std::endl;
        
        std::cout << std::string(146, '-') << std::endl;

        // Print each company
        for (const auto& company : companies) {
            std::cout << std::left << std::setw(36) << company.id
                      << std::setw(30) << company.name
                      << std::setw(20) << company.tax_id
                      << std::setw(30) << company.created_at
                      << std::setw(30) << company.updated_at << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error listing companies: " << e.what() << std::endl;
    }
}

/**
 * @brief Main function for the PentaLedger CLI.
 * 
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments
 * @return int Exit code (0 for success)
 */
int main(int argc, char* argv[]) {
    pentaledger::PentaLedger ledger;
    std::cout << "PentaLedger Version: " << ledger.getVersion() << std::endl;

    // Get database URL from environment variable
    std::string db_url = pentaledger::utility::Environment<std::string>::get("DATABASE_URL");
    std::string path = pentaledger::utility::Environment<std::string>::get("PATH");
    std::cout << "Database URL: " << db_url << std::endl;
    if (db_url.empty()) {
        std::cerr << "Error: DATABASE_URL environment variable is not set" << std::endl;
        return 1;
    }

    // Initialize database connection
    pentaledger::Database db(db_url);
    if (!db.connect()) {
        std::cerr << "Failed to connect to database: " << db.getLastError() << std::endl;
        return 1;
    }

    // List companies
    listCompanies(db);

    return 0;
} 