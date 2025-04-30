/**
 * @file main.cpp
 * @brief Main entry point for the PentaLedger command-line utility.
 */

#include <iostream>
#include <iomanip>
#include "pentaledger/pentaledger.hpp"
#include "pentaledger/db/database.hpp"
#include "pentaledger/utility/Environment.hpp"
#include <CLI/CLI.hpp>

using namespace pentaledger::db;

void createCompany(Database& db) {
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
    CLI::App app{"PentaLedger - A modern ledger system"};
    
    // Version command
    app.add_flag_callback("--version", [&ledger]() {
        std::cout << "PentaLedger Version: " << ledger.getVersion() << std::endl;
        exit(0);
    }, "Show version information");

    // Don't require a subcommand
    app.require_subcommand(0);

    // Add callback for when no subcommand is provided
    app.callback([&app]() {
        std::cout << "Welcome to PentaLedger CLI!" << std::endl;
        std::cout << "Use one of the following commands:" << std::endl << std::endl;
        std::cout << app.help() << std::endl;
    });
    
    std::string db_url = pentaledger::utility::Environment<std::string>::get("DATABASE_URL");
    if (db_url.empty()) {
        std::cerr << "Error: DATABASE_URL environment variable is not set" << std::endl;
        exit(1);
    }

    Database db(db_url);
    if (!db.connect()) {
        std::cerr << "Failed to connect to database: " << db.getLastError() << std::endl;
        exit(1);
    }

    // Company command
    auto company_cmd = app.add_subcommand("company", "Manage companies");
    
    // Company list subcommand
    auto list_cmd = company_cmd->add_subcommand("list", "List all companies");
    list_cmd->callback([&]() {
        db.dumpCompanies();
    });

    // Company create subcommand
    auto create_cmd = company_cmd->add_subcommand("create", "Create a new company");
    std::string name, tax_id, parent_id;
    create_cmd->add_option("--name,-n", name, "Company name")->required();
    create_cmd->add_option("--tax-id,-t", tax_id, "Tax identification number")->required();
    create_cmd->add_option("--parent-id,-p", parent_id, "Parent company ID (optional)");
    create_cmd->callback([&]() {
        try {
            auto company = db.createCompany(name, tax_id, parent_id);
            std::cout << "Company created successfully:" << std::endl;
            std::cout << "  ID: " << company.id << std::endl;
            std::cout << "  Name: " << company.name << std::endl;
            std::cout << "  Tax ID: " << company.tax_id << std::endl;
            if (!company.parent_id.empty()) {
                std::cout << "  Parent ID: " << company.parent_id << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error creating company: " << e.what() << std::endl;
            exit(1);
        }
    });

    // Parse command line arguments
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }

    return 0;
} 