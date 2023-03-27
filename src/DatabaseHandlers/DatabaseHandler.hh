#pragma once

#include <string>
#include <pqxx/pqxx>
#include <set>

#include "DatabaseEnums.hh"

struct DatabaseHandler
{
    static void db_select(Language origLanguage, Language translateLanguage, std::set<std::string> topics);

private:
    DatabaseHandler(const std::string &connection);

    static DatabaseHandler *getInstance();

    static DatabaseHandler *m_instance;

    pqxx::connection m_connection;

    static std::string makeSqlRequest(Language origLanguage, Language translateLanguage, std::set<std::string> topics);
    static std::string makeTopicsString(std::set<std::string> topics);
    static std::string getTableName(Language language);
    static std::string getTranslationTalbeName(Language origLanguage, Language translateLanguage);
};