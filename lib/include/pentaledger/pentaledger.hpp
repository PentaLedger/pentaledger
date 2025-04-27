#pragma once

#include <string>

namespace pentaledger {

class PentaLedger {
public:
    PentaLedger();
    ~PentaLedger();

    std::string getVersion() const;
    void setVersion(const std::string& version);

private:
    std::string version_;
};

} // namespace pentaledger 