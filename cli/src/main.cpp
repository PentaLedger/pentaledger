/**
 * @file main.cpp
 * @brief Main entry point for the PentaLedger command-line utility.
 */

#include <iostream>
#include <iomanip>
#include "pentaledger/pentaledger.hpp"
#include "pentaledger/database.hpp"
#include "pentaledger/utility/Environment.hpp"


void createCompany(pentaledger::Database& db) {
    std::string name = "Test Company";
    std::string tax_id = "1234567890";
    auto company = db.createCompany(name, tax_id);
    std::cout << "Company created: " << company.id << std::endl;
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
    db.dumpCompanies();

    // // Create a parent company
    // pentaledger::Company parent = db.createCompany("Parent Corp", "123-45-6789");

    // // Create a subsidiary
    // pentaledger::Company subsidiary = db.createCompany("Subsidiary Inc", "987-65-4321", parent.id);

    // std::cout << "Creating company..." << std::endl;
    // listCompanies(db);

    return 0;
} 