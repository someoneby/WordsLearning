#pragma once

#include <pqxx/pqxx>
#include <string>

struct DatabaseHandler
{
    static void db_insert_if_absent(std::string_view sql);
    static void db_select(std::string_view sql);

private:
    DatabaseHandler(const std::string &connection);

    static DatabaseHandler *getInstance();

    static DatabaseHandler *m_instance;

    pqxx::connection m_connection;
};