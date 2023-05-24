#include <iostream>

#include "DatabaseHandler.hh"
#include "DatabaseConfig.hh"

DatabaseHandler::DatabaseHandler() try : m_connection{DatabaseHandler::getConnectionString()} {}
catch (const std::exception ex) {
		std::cout << ex.what() << std::endl;
}

DatabaseHandler::~DatabaseHandler() {
	m_connection.close();
}

std::string DatabaseHandler::db_select(const ParsedRequest &request) const
{
	try
	{
		pqxx::nontransaction nontransaction(m_connection);

		std::string sqlRequest = makeSqlRequest(request);
		if (sqlRequest.empty())
		{
			return "";
		}

		pqxx::result result(nontransaction.exec(sqlRequest));

		return parseResult(result);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

std::string DatabaseHandler::makeSqlRequest(const ParsedRequest &request) const
{
	if (!request.isValid())
	{
		return "";
	}

	std::string boundaryTableName, nativeWordId, translatedWordId;
	if (request.nativeLanguage < request.learningLanguage)
	{
		boundaryTableName = request.nativeLanguage + "And" + request.learningLanguage;
		nativeWordId = "wordIdLeft";
		translatedWordId = "wordIdRight";
	}
	else
	{
		boundaryTableName = request.learningLanguage + "And" + request.nativeLanguage;
		nativeWordId = "wordIdRight";
		translatedWordId = "wordIdLeft";
	}

	std::string topics;
	for (auto theme = request.themes.begin(); theme != request.themes.end(); theme++)
	{
		if (theme != request.themes.begin())
		{
			topics += " OR ";
		}

		topics += "l1.\"Topic\" LIKE \'%" + *theme + "%\'";
	}

	std::string sql_request = "SELECT l1.\"Word\", l2.\"Word\" FROM public.\"" + request.nativeLanguage + "\" l1 " +
							  "JOIN public.\"" + boundaryTableName + "\" bounds ON l1.\"id\" = bounds.\"" + nativeWordId + "\" " +
							  "JOIN public.\"" + request.learningLanguage + "\" l2 ON l2.\"id\" = bounds.\"" + translatedWordId + "\" " +
							  "WHERE " + topics + ";";

	return sql_request;
}

std::string DatabaseHandler::parseResult(const pqxx::result& result) const {
	std::string parsedResult;
	for (auto res : result) {
		for (auto str : res) {
			parsedResult += str.c_str();
			parsedResult += ";";
		}
	}
	return parsedResult;
}

std::string DatabaseHandler::getConnectionString() {
	static std::string connection =
		"dbname = " + DatabaseConfig::DB_NAME +
		" user = " + DatabaseConfig::DB_USER +
		" password = " + DatabaseConfig::DB_PASSWORD +
		" hostaddr = " + DatabaseConfig::DB_HOSTADDR +
		" port = " + DatabaseConfig::DB_PORT;
	return connection;
}