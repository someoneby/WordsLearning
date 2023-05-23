#include "RequestHandler.hh"

RequestHandler::RequestHandler(std::unique_ptr<IDatabaseHandler> databaseHandler) : m_databaseHandler{ std::move(databaseHandler) } {}

std::string RequestHandler::handleRequest(const ParsedRequest& request) {
    auto rawResult = m_databaseHandler->db_select(request);

	//rawResult.

	auto result = parseResult(rawResult);


	return "";
}

std::vector<WordPair> RequestHandler::parseResult(pqxx::result rawResult) {
	std::vector<WordPair> results;
	for (auto rawResult : rawResult) {
		WordPair{ rawResult[0].c_str(), rawResult[1].c_str() };
	}

	return results;
}