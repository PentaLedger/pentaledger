#include "pentaledger/database.hpp"
#include <stdexcept>

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

    const char* query = "SELECT id, name, tax_id, created_at, updated_at FROM companies ORDER BY name";
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
        company.created_at = PQgetvalue(result, i, 3);
        company.updated_at = PQgetvalue(result, i, 4);
        companies.push_back(company);
    }

    PQclear(result);
    return companies;
}

} // namespace pentaledger 