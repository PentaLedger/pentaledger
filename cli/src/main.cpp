/**
 * @file main.cpp
 * @brief Main entry point for the PentaLedger command-line utility.
 */

#include <iostream>
#include "pentaledger/pentaledger.hpp"

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
    return 0;
} 