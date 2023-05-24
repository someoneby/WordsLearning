#include <time.h>

#include "RequestHandler.hh"

RequestHandler::RequestHandler(std::unique_ptr<IDatabaseHandler> databaseHandler) : m_databaseHandler{ std::move(databaseHandler) } {}

std::string RequestHandler::handleRequest(const ParsedRequest& request) const {
    auto rawResult = m_databaseHandler->db_select(request);

	auto result = parseResult(rawResult);

	mixResult(result);

	return makeAnswer(result);
}

std::vector<WordPair> RequestHandler::parseResult(std::string rawResult) const {
	std::vector<WordPair> results;
	std::string word1, word2;
	while (!rawResult.empty()) {
		word1 = rawResult.substr(0, rawResult.find(";")); //TODO make constant string ";"
		rawResult.erase(0, rawResult.find(";") + 1);
		word2 = rawResult.substr(0, rawResult.find(";"));
		rawResult.erase(0, rawResult.find(";") + 1);

		results.push_back({ word1, word2 });
	}

	return results;
}

void RequestHandler::mixResult(std::vector<WordPair>& pairs) const {
	for (auto& pair : pairs) {
		int64_t random = (*takeUniqueRandomSet(pairs.size(), {}).begin());
		std::swap(pair, pairs.at(random));
	}
}

std::string RequestHandler::makeAnswer(const std::vector<WordPair>& pairs) const {
	std::string result = "test words: ";
	
	for (auto i = 0; i < pairs.size(); ++i) {
		result += pairs.at(i).nativeWord;
		result += ",";
		result += pairs.at(i).translatedWord;

		auto randoms = takeUniqueRandomSet(pairs.size(), { i }, 3); //TODO make constant in config
		for (auto rand : randoms) {
			result += ",";
			result += pairs.at(rand).translatedWord;
		}

		if (i < pairs.size() - 1) {
			result += ";";
		}
	}

	result += ";";

	return result;
}

std::set<int64_t> RequestHandler::takeUniqueRandomSet(int64_t maxValue, std::set<int64_t> exclude, int64_t howMany) const {
#ifndef DEBUG
	srand(time(nullptr));
#endif // !DEBUG

	std::set<int64_t> result;
	int64_t random;

	for (int i = 0; i < howMany; ++i) {
		do {
			random = rand() % maxValue;
		} while (exclude.find(random) != exclude.end() || result.find(random) != result.end());

		result.insert(random);
	}

	return result;
}