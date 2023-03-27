#include <iostream>

#include "DatabaseHandler.hh"
#include "DatabaseConfig.hh"
#include "DatabaseEnums.hh"

DatabaseHandler *DatabaseHandler::m_instance = nullptr;

void DatabaseHandler::db_select(Language origLanguage, Language translateLanguage, std::set<std::string> topics)
{
    try
    {
        DatabaseHandler *dbInstance = getInstance();

        pqxx::nontransaction nonTransaction(dbInstance->m_connection);

        std::string sql = makeSqlRequest(origLanguage, translateLanguage, topics);

        pqxx::result res(nonTransaction.exec(sql));

        for (auto i : res)
        {
            auto word = i[0].as<std::string>();
            auto translate = i[1].as<std::string>();
            std::cout << "word: " << i[0].as<std::string>() << std::endl;
            std::cout << "translate: " << i[1].as<std::string>() << std::endl
                      << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

std::string DatabaseHandler::makeSqlRequest(Language origLanguage, Language translateLanguage, std::set<std::string> topics)
{
    // TODO make exception
    //  if(origLanguage == translateLanguage)

    std::string origWordTableName = getTableName(origLanguage);
    std::string translateWordTableName = getTableName(translateLanguage);
    std::string translationTalbeName = getTranslationTalbeName(origLanguage, translateLanguage);

    std::string origWordIdColumnName;
    std::string translateWordIdColumnName;
    if (translationTalbeName.find(origWordTableName) == 0)
    {
        origWordIdColumnName = "wordIdLeft";
        translateWordIdColumnName = "wordIdRight";
    }
    else
    {
        origWordIdColumnName = "wordIdRight";
        translateWordIdColumnName = "wordIdLeft";
    }

    std::string sql = "SELECT origWords.\"Word\", translateWords.\"Word\" FROM public.\"" + origWordTableName + "\" origWords \
    JOIN public.\"" + translationTalbeName +
                      "\" translation ON origWords.id=\"" + origWordIdColumnName + "\" \
	JOIN public.\"" + translateWordTableName +
                      "\" translateWords ON translation.\"" + translateWordIdColumnName + "\"=translateWords.\"id\"";

    if (topics.size() != 0)
    {
        sql += makeTopicsString(topics);
    }

    return sql;
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

std::string DatabaseHandler::makeTopicsString(std::set<std::string> topics)
{
    std::string topicsStr = " WHERE origWords.\"Topic\" IN (";

    for (auto topic = topics.begin(); topic != topics.end();)
    {
        topicsStr += "\'" + *topic + "\'";

        if (++topic != topics.end())
        {
            topicsStr += ",";
        }
    }

    topicsStr += ");";

    return topicsStr;
}

std::string DatabaseHandler::getTableName(Language language)
{
    switch (language)
    {
    case english:
        return "English";
    case russian:
        return "Russian";
    }

    // TODO make exception
    return "";
}

std::string DatabaseHandler::getTranslationTalbeName(Language origLanguage, Language translateLanguage)
{
    if ((origLanguage == russian && translateLanguage == english) || (origLanguage == english && translateLanguage == russian))
    {
        return "EnglishAndRussian";
    }

    // TODO make exception
    return "";
}