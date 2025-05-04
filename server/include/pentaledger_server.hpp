#pragma once

#include <drogon/HttpAppFramework.h>
#include <drogon/HttpController.h>
#include <memory>
#include <string>

namespace pentaledger {

class PentaLedgerServer {
public:
    PentaLedgerServer();
    ~PentaLedgerServer();

    // Initialize the server with configuration
    void initialize(const std::string& configFile = "config.json");
    
    // Start the server
    void start();
    
    // Stop the server
    void stop();

private:
    // Server configuration
    struct Config {
        std::string host = "0.0.0.0";
        uint16_t port = 8080;
        size_t threadNum = 4;
        std::string logLevel = "INFO";
    };

    Config config_;
    std::unique_ptr<drogon::HttpAppFramework> app_;
    
    // Load configuration from file
    void loadConfig(const std::string& configFile);
    
    // Initialize routes
    void initializeRoutes();
};

} // namespace pentaledger 