#pragma once

#include <pqxx/pqxx>
#include <iostream>
#include <vector>

#include "IDatabaseHandler.hh"

struct DatabaseHandler : public IDatabaseHandler
{
    DatabaseHandler();
    ~DatabaseHandler() override;

    pqxx::result db_select(const ParsedRequest& request) const override;

private:
    std::string makeSqlRequest(const ParsedRequest& request) const;

    static std::string getConnectionString();

    mutable pqxx::connection m_connection;
};