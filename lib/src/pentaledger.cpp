/**
 * @file pentaledger.cpp
 * @brief Implementation of the PentaLedger class.
 */

#include "pentaledger/pentaledger.hpp"

namespace pentaledger {

PentaLedger::PentaLedger() : version_("0.1.0") {}

PentaLedger::~PentaLedger() = default;

std::string PentaLedger::getVersion() const {
    return version_;
}

void PentaLedger::setVersion(const std::string& version) {
    version_ = version;
}

} // namespace pentaledger 