#include "pentaledger_server.hpp"
#include <drogon/drogon.h>
#include <drogon/HttpAppFramework.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <json/json.h>
#include <fstream>
#include <iostream>

namespace pentaledger {

PentaLedgerServer::PentaLedgerServer() {
    // Initialize the server
    app_ = &drogon::app();
}

PentaLedgerServer::~PentaLedgerServer() = default;

void PentaLedgerServer::initialize(const std::string& configFile) {
    loadConfig(configFile);
    
    // Set server configuration
    app_->setLogPath("./");
    app_->setLogLevel(trantor::Logger::kWarn);
    app_->setThreadNum(4);
    app_->setDocumentRoot("./www");
    app_->setUploadPath("./uploads");
    app_->enableGzip(true);
    app_->enableBrotli(true);
    app_->setStaticFilesCacheTime(0);
    app_->setIdleConnectionTimeout(60);
    // Initialize routes
    initializeRoutes();
}

void PentaLedgerServer::loadConfig(const std::string& configFile) {
    try {
        std::ifstream file(configFile);
        if (!file.is_open()) {
            std::cerr << "Warning: Could not open config file " << configFile 
                      << ". Using default configuration." << std::endl;
            return;
        }

        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(file, root)) {
            std::cerr << "Error parsing config file: " << reader.getFormattedErrorMessages() 
                      << ". Using default configuration." << std::endl;
            return;
        }

        if (root.isMember("host")) config_.host = root["host"].asString();
        if (root.isMember("port")) config_.port = root["port"].asUInt();
        if (root.isMember("threadNum")) config_.threadNum = root["threadNum"].asUInt();
        if (root.isMember("logLevel")) config_.logLevel = root["logLevel"].asString();
    } catch (const std::exception& e) {
        std::cerr << "Error loading config: " << e.what() 
                  << ". Using default configuration." << std::endl;
    }

    std::cout << "host: " << config_.host << std::endl;
    std::cout << "port: " << config_.port << std::endl;
    std::cout << "threadNum: " << config_.threadNum << std::endl;
    std::cout << "logLevel: " << config_.logLevel << std::endl;
}

void PentaLedgerServer::initializeRoutes() {
    // Health check endpoint
    app_->registerHandler("/health", 
        [](const drogon::HttpRequestPtr& req,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::k200OK);
            resp->setContentTypeCode(drogon::CT_APPLICATION_JSON);
            resp->setBody("{\"status\":\"ok\"}");
            callback(resp);
        },
        {drogon::Get});

    // TODO: Add more routes for companies, vendors, etc.
}

void PentaLedgerServer::start() {
    std::cout << "Starting PentaLedger server on " << config_.host 
              << ":" << config_.port << std::endl;
    
    // Add listener with configured host and port
    app_->addListener(config_.host, config_.port);
    
    // Start the server
    app_->run();
}

void PentaLedgerServer::stop() {
    app_->quit();
}

} // namespace pentaledger 