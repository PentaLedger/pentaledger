// SPDX-License-Identifier: GPL-2.0-or-later
//! \file main.cpp
//! \author Joe Turner <joe.turner@infinity-surge.com>
//!
//! \copyright
//! Copyright (c) 2025 Joe Turner.
//!
//! This program is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, version 2.
//!
//! This program is distributed in the hope that it will be useful, but
//! WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//! General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with this program. If not, see <http://www.gnu.org/licenses/>.
#include <iostream>
#include <iomanip>
#include "pentaledger/pentaledger.hpp"
#include "pentaledger/db/database.hpp"
#include "pentaledger/utility/Environment.hpp"
#include <CLI/CLI.hpp>

using namespace pentaledger::db;

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

    // Gambling log command
    auto gambling_cmd = app.add_subcommand("gambling", "Manage gambling logs");
    
    // Gambling list subcommand
    auto gambling_list_cmd = gambling_cmd->add_subcommand("list", "List all gambling log entries");
    gambling_list_cmd->callback([&]() {
        db.dumpGamblingLogs();
    });

    // Gambling create subcommand
    auto gambling_create_cmd = gambling_cmd->add_subcommand("create", "Create a new gambling log entry");
    std::string date, establishment_name, establishment_address, time_of_day, wagering_type, location_id, notes;
    double w2_winnings, winnings, losses;
    
    gambling_create_cmd->add_option("--date,-d", date, "Date (YYYY-MM-DD)")->required();
    gambling_create_cmd->add_option("--establishment,-e", establishment_name, "Establishment name")->required();
    gambling_create_cmd->add_option("--address,-a", establishment_address, "Establishment address")->required();
    gambling_create_cmd->add_option("--time,-t", time_of_day, "Time of day (HH:MM:SS)")->required();
    gambling_create_cmd->add_option("--type,-y", wagering_type, "Wagering type")->required();
    gambling_create_cmd->add_option("--location,-l", location_id, "Location ID")->required();
    gambling_create_cmd->add_option("--w2,-w", w2_winnings, "W2 winnings")->required();
    gambling_create_cmd->add_option("--winnings,-g", winnings, "Total winnings")->required();
    gambling_create_cmd->add_option("--losses,-s", losses, "Total losses")->required();
    gambling_create_cmd->add_option("--notes,-n", notes, "Additional notes");
    
    gambling_create_cmd->callback([&]() {
        try {
            auto log = db.createGamblingLog(
                date,
                establishment_name,
                establishment_address,
                time_of_day,
                wagering_type,
                location_id,
                w2_winnings,
                winnings,
                losses,
                notes
            );
            
            std::cout << "Gambling log entry created successfully:" << std::endl;
            std::cout << "  ID: " << log.id << std::endl;
            std::cout << "  Date: " << log.date << std::endl;
            std::cout << "  Time: " << log.time_of_day << std::endl;
            std::cout << "  Establishment: " << log.establishment_name << std::endl;
            std::cout << "  Address: " << log.establishment_address << std::endl;
            std::cout << "  Wagering Type: " << log.wagering_type << std::endl;
            std::cout << "  Location ID: " << log.location_id << std::endl;
            std::cout << "  W2 Winnings: $" << std::fixed << std::setprecision(2) << log.w2_winnings << std::endl;
            std::cout << "  Winnings: $" << std::fixed << std::setprecision(2) << log.winnings << std::endl;
            std::cout << "  Losses: $" << std::fixed << std::setprecision(2) << log.losses << std::endl;
            std::cout << "  Net: $" << std::fixed << std::setprecision(2) << (log.winnings - log.losses) << std::endl;
            if (!log.notes.empty()) {
                std::cout << "  Notes: " << log.notes << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error creating gambling log entry: " << e.what() << std::endl;
            exit(1);
        }
    });

    // Gambling summary subcommand
    auto gambling_summary_cmd = gambling_cmd->add_subcommand("summary", "Show summary of gambling wins and losses");
    gambling_summary_cmd->callback([&]() {
        try {
            auto logs = db.getGamblingLogs();
            double total_w2_winnings = 0.0;
            double total_winnings = 0.0;
            double total_losses = 0.0;
            
            for (const auto& log : logs) {
                total_w2_winnings += log.w2_winnings;
                total_winnings += log.winnings;
                total_losses += log.losses;
            }
            
            double net_result = total_winnings - total_losses;
            
            std::cout << "\nGambling Summary:" << std::endl;
            std::cout << "=================" << std::endl;
            std::cout << "Total W2 Winnings: $" << std::fixed << std::setprecision(2) << total_w2_winnings << std::endl;
            std::cout << "Total Winnings:    $" << std::fixed << std::setprecision(2) << total_winnings << std::endl;
            std::cout << "Total Losses:      $" << std::fixed << std::setprecision(2) << total_losses << std::endl;
            std::cout << "Net Result:        $" << std::fixed << std::setprecision(2) << net_result << std::endl;
            std::cout << "Number of Sessions: " << logs.size() << std::endl;
            
            if (net_result > 0) {
                std::cout << "\nOverall Result: You are up $" << std::fixed << std::setprecision(2) << net_result << std::endl;
            } else if (net_result < 0) {
                std::cout << "\nOverall Result: You are down $" << std::fixed << std::setprecision(2) << -net_result << std::endl;
            } else {
                std::cout << "\nOverall Result: You broke even" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error getting gambling summary: " << e.what() << std::endl;
            exit(1);
        }
    });

    // Don't require a subcommand
    if (argc == 1) {
        std::cout << "Welcome to PentaLedger CLI!" << std::endl;
        std::cout << "Use one of the following commands:" << std::endl << std::endl;
        std::cout << app.help() << std::endl;
    }

    // Parse command line arguments
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }

    return 0;
} 