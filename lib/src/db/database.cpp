#include "pentaledger/db/database.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>

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

std::vector<GamblingLog> Database::getGamblingLogs() {
    if (!isConnected()) {
        throw std::runtime_error("Database is not connected");
    }

    std::string query = "SELECT id, date, establishment_name, establishment_address, "
                       "time_of_day, wagering_type, location_id, w2_winnings, "
                       "winnings, losses, notes, created_at, updated_at "
                       "FROM gambling_log ORDER BY date DESC, time_of_day DESC";

    PGresult* result = executeQuery(query);
    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        std::string error = PQresultErrorMessage(result);
        PQclear(result);
        throw std::runtime_error("Failed to get gambling logs: " + error);
    }

    std::vector<GamblingLog> logs;
    int rows = PQntuples(result);
    for (int i = 0; i < rows; ++i) {
        GamblingLog log;
        log.id = PQgetvalue(result, i, 0);
        log.date = PQgetvalue(result, i, 1);
        log.establishment_name = PQgetvalue(result, i, 2);
        log.establishment_address = PQgetvalue(result, i, 3);
        log.time_of_day = PQgetvalue(result, i, 4);
        log.wagering_type = PQgetvalue(result, i, 5);
        log.location_id = PQgetvalue(result, i, 6);
        log.w2_winnings = std::stod(PQgetvalue(result, i, 7));
        log.winnings = std::stod(PQgetvalue(result, i, 8));
        log.losses = std::stod(PQgetvalue(result, i, 9));
        log.notes = PQgetvalue(result, i, 10);
        log.created_at = PQgetvalue(result, i, 11);
        log.updated_at = PQgetvalue(result, i, 12);
        logs.push_back(log);
    }

    PQclear(result);
    return logs;
}

GamblingLog Database::createGamblingLog(
    const std::string& date,
    const std::string& establishment_name,
    const std::string& establishment_address,
    const std::string& time_of_day,
    const std::string& wagering_type,
    const std::string& location_id,
    double w2_winnings,
    double winnings,
    double losses,
    const std::string& notes
) {
    if (!isConnected()) {
        throw std::runtime_error("Database is not connected");
    }

    const char* paramValues[10] = {
        date.c_str(),
        establishment_name.c_str(),
        establishment_address.c_str(),
        time_of_day.c_str(),
        wagering_type.c_str(),
        location_id.c_str(),
        std::to_string(w2_winnings).c_str(),
        std::to_string(winnings).c_str(),
        std::to_string(losses).c_str(),
        notes.c_str()
    };

    int paramLengths[10] = {
        static_cast<int>(date.length()),
        static_cast<int>(establishment_name.length()),
        static_cast<int>(establishment_address.length()),
        static_cast<int>(time_of_day.length()),
        static_cast<int>(wagering_type.length()),
        static_cast<int>(location_id.length()),
        static_cast<int>(std::to_string(w2_winnings).length()),
        static_cast<int>(std::to_string(winnings).length()),
        static_cast<int>(std::to_string(losses).length()),
        static_cast<int>(notes.length())
    };

    int paramFormats[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    PGresult* result = PQexecParams(
        connection_,
        "INSERT INTO gambling_log (date, establishment_name, establishment_address, "
        "time_of_day, wagering_type, location_id, w2_winnings, winnings, losses, notes) "
        "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10) "
        "RETURNING id, date, establishment_name, establishment_address, "
        "time_of_day, wagering_type, location_id, w2_winnings, "
        "winnings, losses, notes, created_at, updated_at",
        10,
        nullptr,
        paramValues,
        paramLengths,
        paramFormats,
        0
    );

    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        std::string error = PQresultErrorMessage(result);
        PQclear(result);
        throw std::runtime_error("Failed to create gambling log: " + error);
    }

    GamblingLog log;
    log.id = PQgetvalue(result, 0, 0);
    log.date = PQgetvalue(result, 0, 1);
    log.establishment_name = PQgetvalue(result, 0, 2);
    log.establishment_address = PQgetvalue(result, 0, 3);
    log.time_of_day = PQgetvalue(result, 0, 4);
    log.wagering_type = PQgetvalue(result, 0, 5);
    log.location_id = PQgetvalue(result, 0, 6);
    log.w2_winnings = std::stod(PQgetvalue(result, 0, 7));
    log.winnings = std::stod(PQgetvalue(result, 0, 8));
    log.losses = std::stod(PQgetvalue(result, 0, 9));
    log.notes = PQgetvalue(result, 0, 10);
    log.created_at = PQgetvalue(result, 0, 11);
    log.updated_at = PQgetvalue(result, 0, 12);

    PQclear(result);
    return log;
}

void Database::dumpGamblingLogs() {
    try {
        auto logs = getGamblingLogs();
        
        if (logs.empty()) {
            std::cout << "No gambling log entries found." << std::endl;
            return;
        }

        // Print header
        std::cout << std::left 
                  << std::setw(12) << "Date"
                  << std::setw(20) << "Time"
                  << std::setw(25) << "Establishment"
                  << std::setw(15) << "Wagering Type"
                  << std::setw(12) << "W2 Winnings"
                  << std::setw(12) << "Winnings"
                  << std::setw(12) << "Losses"
                  << std::setw(10) << "Net"
                  << std::endl;
        
        std::cout << std::string(118, '-') << std::endl;

        // Print each log entry
        for (const auto& log : logs) {
            double net = log.winnings - log.losses;
            std::cout << std::left 
                      << std::setw(12) << log.date
                      << std::setw(20) << log.time_of_day
                      << std::setw(25) << log.establishment_name
                      << std::setw(15) << log.wagering_type
                      << std::setw(12) << std::fixed << std::setprecision(2) << log.w2_winnings
                      << std::setw(12) << std::fixed << std::setprecision(2) << log.winnings
                      << std::setw(12) << std::fixed << std::setprecision(2) << log.losses
                      << std::setw(10) << std::fixed << std::setprecision(2) << net
                      << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error listing gambling logs: " << e.what() << std::endl;
    }
}
} // namespace pentaledger 
