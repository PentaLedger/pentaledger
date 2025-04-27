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

} // namespace pentaledger 