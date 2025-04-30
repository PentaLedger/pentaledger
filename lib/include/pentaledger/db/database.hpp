#pragma once

#include <string>
#include <memory>
#include <vector>
#include <libpq-fe.h>
#include "pentaledger/db/company.hpp"
#include "pentaledger/db/gambling_log.hpp"

namespace pentaledger
{

    //! \brief Namespace for database-related functionality
    //! This namespace contains classes and functions for managing database connections
    //! and operations.
    namespace db
    {
        /**
         * @brief Class for managing PostgreSQL database connections.
         *
         * This class provides functionality to connect to and interact with
         * a PostgreSQL database.
         */
        class Database
        {
        public:
            /**
             * @brief Construct a new Database object.
             *
             * @param connectionString PostgreSQL connection string
             */
            explicit Database(const std::string &connectionString);

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
            PGresult *executeQuery(const std::string &query);

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
            Company createCompany(const std::string &name, const std::string &tax_id, const std::string &parent_id = "");

            /**
             * @brief Dump all companies from the database to the console.
             */
            void dumpCompanies();

            /**
             * @brief Get all gambling log entries from the database.
             *
             * @return std::vector<GamblingLog> Vector of gambling log entries
             * @throw std::runtime_error if query fails
             */
            std::vector<GamblingLog> getGamblingLogs();

            /**
             * @brief Create a new gambling log entry in the database.
             *
             * @param date Date of the gambling activity (YYYY-MM-DD)
             * @param establishment_name Name of the gambling establishment
             * @param establishment_address Address of the gambling establishment
             * @param time_of_day Time of the gambling activity (HH:MM:SS)
             * @param wagering_type Type of wagering
             * @param location_id Location identifier
             * @param w2_winnings W2 reportable winnings
             * @param winnings Total winnings
             * @param losses Total losses
             * @param notes Additional notes
             * @return GamblingLog The created gambling log entry with its ID and timestamps
             * @throw std::runtime_error if creation fails
             */
            GamblingLog createGamblingLog(
                const std::string& date,
                const std::string& establishment_name,
                const std::string& establishment_address,
                const std::string& time_of_day,
                const std::string& wagering_type,
                const std::string& location_id,
                double w2_winnings,
                double winnings,
                double losses,
                const std::string& notes = ""
            );

            /**
             * @brief Dump all gambling log entries to the console.
             */
            void dumpGamblingLogs();

        private:
            std::string connectionString_;
            PGconn *connection_;
            bool isConnected_;
        };
    }
}