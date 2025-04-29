#pragma once

#include <string>
#include <memory>
#include <vector>
#include <libpq-fe.h>
#include "pentaledger/company.hpp"

namespace pentaledger {

/**
 * @brief Class for managing PostgreSQL database connections.
 * 
 * This class provides functionality to connect to and interact with
 * a PostgreSQL database.
 */
class Database {
public:
    /**
     * @brief Construct a new Database object.
     * 
     * @param connectionString PostgreSQL connection string
     */
    explicit Database(const std::string& connectionString);

    /**
     * @brief Destroy the Database object.
     * 
     * Closes the database connection if it's open.
     */
    ~Database();

    /**
     * @brief Connect to the database.
     * 
     * @return true if connection was successful
     * @return false if connection failed
     */
    bool connect();

    /**
     * @brief Disconnect from the database.
     */
    void disconnect();

    /**
     * @brief Check if the database is connected.
     * 
     * @return true if connected
     * @return false if not connected
     */
    bool isConnected() const;

    /**
     * @brief Execute a SQL query.
     * 
     * @param query The SQL query to execute
     * @return PGresult* The result of the query
     */
    PGresult* executeQuery(const std::string& query);

    /**
     * @brief Get the last error message.
     * 
     * @return std::string The error message
     */
    std::string getLastError() const;

    /**
     * @brief Get all companies from the database.
     * 
     * @return std::vector<Company> Vector of companies
     * @throw std::runtime_error if query fails
     */
    std::vector<Company> getCompanies();

    /**
     * @brief Create a new company in the database.
     * 
     * @param name The company name
     * @param tax_id The company's tax identification number
     * @param parent_id Optional UUID of the parent company
     * @return Company The created company with its ID and timestamps
     * @throw std::runtime_error if creation fails
     */
    Company createCompany(const std::string& name, const std::string& tax_id, const std::string& parent_id = "");

    /**
     * @brief Dump all companies from the database to the console.
     */
    void dumpCompanies();

private:
    std::string connectionString_;
    PGconn* connection_;
    bool isConnected_;
};
} 