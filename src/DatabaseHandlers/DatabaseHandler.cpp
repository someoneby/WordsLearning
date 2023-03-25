#include <iostream>

#include "DatabaseHandler.hh"
#include "DatabaseConfig.hh"

DatabaseHandler *DatabaseHandler::m_instance = nullptr;

void DatabaseHandler::db_insert_if_absent(std::string_view sql)
{
    try
    {
        DatabaseHandler *dbInstance = getInstance();

        pqxx::work W(dbInstance->m_connection);

        W.exec(sql);

        W.commit();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}


void DatabaseHandler::db_select(std::string_view sql)
{

}












DatabaseHandler *DatabaseHandler::getInstance()
{
    if (!m_instance)
    {
        std::string connection =
            "dbname = " + DatabaseConfig::DB_NAME +
            " user = " + DatabaseConfig::DB_USER +
            " password = " + DatabaseConfig::DB_PASSWORD +
            " hostaddr = " + DatabaseConfig::DB_HOSTADDR +
            " port = " + DatabaseConfig::DB_PORT;

        m_instance = new DatabaseHandler(connection);
    }

    return m_instance;
}

DatabaseHandler::DatabaseHandler(const std::string &connection)
try : m_connection{pqxx::connection(connection)}
{
}
catch (const std::exception &e)
{
    std::cout << e.what() << std::endl;
}