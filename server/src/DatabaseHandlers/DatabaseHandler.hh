#pragma once

#include <pqxx/pqxx>
#include <string>

#include "IDatabaseHandler.hh"

struct DatabaseHandler : public IDatabaseHandler
{
    DatabaseHandler();
    ~DatabaseHandler() override;

    std::string db_select(const ParsedRequest& request) const override;

private:
    std::string makeSqlRequest(const ParsedRequest& request) const;

    std::string parseResult(const pqxx::result& result) const;

    static std::string getConnectionString();

    mutable pqxx::connection m_connection;
};