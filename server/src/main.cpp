#include "pentaledger_server.hpp"
#include <iostream>
#include <csignal>

namespace {
    pentaledger::PentaLedgerServer* server = nullptr;

    void signalHandler(int signal) {
        if (server) {
            std::cout << "Received signal " << signal << ". Shutting down server..." << std::endl;
            server->stop();
        }
    }
}

int main(int argc, char* argv[]) {
    try {
        // Create and initialize server
        pentaledger::PentaLedgerServer srv;
        server = &srv;
        
        // Register signal handlers
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);
        
        // Initialize server with config file if provided
        if (argc > 1) {
            srv.initialize(argv[1]);
        } else {
            srv.initialize();
        }
        
        // Start server
        srv.start();
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
} 