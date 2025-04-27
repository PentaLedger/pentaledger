#include <iostream>
#include "pentaledger/pentaledger.hpp"

int main(int argc, char* argv[]) {
    pentaledger::PentaLedger ledger;
    std::cout << "PentaLedger Version: " << ledger.getVersion() << std::endl;
    return 0;
} 