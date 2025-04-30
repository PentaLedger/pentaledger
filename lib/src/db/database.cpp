#include "pentaledger/db/database.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace pentaledger::db;

namespace pentaledger {

Database::Database(const std::string& connectionString)
    : connectionString_(connectionString)
    , connection_(nullptr)
    , isConnected_(false)
{
}

Database::~Database() {
    disconnect();
}

bool Database::connect() {
    if (isConnected_) {
        return true;
    }

    connection_ = PQconnectdb(connectionString_.c_str());
    if (PQstatus(connection_) != CONNECTION_OK) {
        isConnected_ = false;
        return false;
    }

    isConnected_ = true;
    return true;
}

void Database::disconnect() {
    if (connection_) {
        PQfinish(connection_);
        connection_ = nullptr;
    }
    isConnected_ = false;
}

bool Database::isConnected() const {
    return isConnected_;
}

PGresult* Database::executeQuery(const std::string& query) {
    if (!isConnected_) {
        throw std::runtime_error("Database is not connected");
    }

    PGresult* result = PQexec(connection_, query.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK && 
        PQresultStatus(result) != PGRES_TUPLES_OK) {
        PQclear(result);
        throw std::runtime_error(getLastError());
    }

    return result;
}

std::string Database::getLastError() const {
    if (connection_) {
        return PQerrorMessage(connection_);
    }
    return "No database connection";
}

std::vector<Company> Database::getCompanies() {
    if (!isConnected_) {
        throw std::runtime_error("Database is not connected");
    }

    const char* query = "SELECT id, name, tax_id, parent_id, created_at, updated_at FROM companies ORDER BY name";
    PGresult* result = executeQuery(query);
    
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        PQclear(result);
        throw std::runtime_error("Failed to execute query: " + getLastError());
    }

    std::vector<Company> companies;
    int rows = PQntuples(result);
    
    for (int i = 0; i < rows; i++) {
        Company company;
        company.id = PQgetvalue(result, i, 0);
        company.name = PQgetvalue(result, i, 1);
        company.tax_id = PQgetvalue(result, i, 2);
        company.parent_id = PQgetvalue(result, i, 3);
        company.created_at = PQgetvalue(result, i, 4);
        company.updated_at = PQgetvalue(result, i, 5);
        companies.push_back(company);
    }

    PQclear(result);
    return companies;
}

Company Database::createCompany(const std::string& name, const std::string& tax_id, const std::string& parent_id) {
    if (!isConnected_) {
        throw std::runtime_error("Database is not connected");
    }

    // Prepare the query with parameters
    const char* query;
    const char* values[3];
    int lengths[3];
    int formats[3] = { 0, 0, 0 }; // 0 = text format
    int nParams;

    if (parent_id.empty()) {
        query = "INSERT INTO companies (name, tax_id) VALUES ($1, $2) RETURNING id, name, tax_id, parent_id, created_at, updated_at";
        values[0] = name.c_str();
        values[1] = tax_id.c_str();
        lengths[0] = static_cast<int>(name.length());
        lengths[1] = static_cast<int>(tax_id.length());
        nParams = 2;
    } else {
        query = "INSERT INTO companies (name, tax_id, parent_id) VALUES ($1, $2, $3) RETURNING id, name, tax_id, parent_id, created_at, updated_at";
        values[0] = name.c_str();
        values[1] = tax_id.c_str();
        values[2] = parent_id.c_str();
        lengths[0] = static_cast<int>(name.length());
        lengths[1] = static_cast<int>(tax_id.length());
        lengths[2] = static_cast<int>(parent_id.length());
        nParams = 3;
    }

    // Execute the parameterized query
    PGresult* result = PQexecParams(connection_, query, nParams, nullptr, values, lengths, formats, 0);
    
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        PQclear(result);
        throw std::runtime_error("Failed to create company: " + getLastError());
    }

    // Create and populate the company object
    Company company;
    company.id = PQgetvalue(result, 0, 0);
    company.name = name;
    company.tax_id = tax_id;
    company.parent_id = parent_id;
    company.created_at = PQgetvalue(result, 0, 4);
    company.updated_at = PQgetvalue(result, 0, 5);

    PQclear(result);
    return company;
}

void Database::dumpCompanies() {

    try {
        auto companies = getCompanies();
        // Print header
        std::cout << std::left << std::setw(40) << "ID"
                  << std::setw(30) << "Name"
                  << std::setw(20) << "Tax ID"
                  << std::setw(40) << "Parent ID"
                  << std::setw(30) << "Updated At" << std::endl;

        std::cout << std::string(146, '-') << std::endl;

        if (companies.empty()) {
            std::cout << "No companies found in the database." << std::endl;
            return;
        }

        // Print each company
        for (const auto& company : companies) {
            std::cout << std::left << std::setw(40) << company.id
                      << std::setw(30) << company.name
                      << std::setw(20) << company.tax_id
                      << std::setw(40) << company.parent_id
                      << std::setw(30) << company.updated_at << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error dumping companies: " << e.what() << std::endl;
    }
}
} // namespace pentaledger 
