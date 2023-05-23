#include <gtest/gtest.h>
#include "../src/ConnectionHandler/ParsedRequest.hh"
#include "../src/DatabaseHandlers/DatabaseHandler.hh"

std::vector<std::string> parseResult(const pqxx::result& result);

struct DatabaseHandlerTest : public testing::Test {
	DatabaseHandler* db;

	void SetUp() { db = new DatabaseHandler(); }
	void TearDown() { delete db; }
};

TEST_F(DatabaseHandlerTest, select_ENG_TO_RU)
{
	std::vector<std::string> expectedResults{ "lion", "lev", "cat", "kot", "computer", "komputer"};
	ParsedRequest request{ "English", "Russian", {"it", "animal"} };

	DatabaseHandler db;
	auto results = db.db_select(request);

	std::vector<std::string> parsed_results{ parseResult(results) };

	for (auto resultIter = parsed_results.begin(), expected = expectedResults.begin(); resultIter != parsed_results.end() && expected != expectedResults.end(); ++resultIter, ++expected) {
		ASSERT_EQ(*resultIter, *expected);
	}
}

TEST_F(DatabaseHandlerTest, select_RU_TO_ENG)
{
	std::vector<std::string> expectedResults{ "lev", "lion", "kot", "cat", "komputer", "computer" };
	ParsedRequest request{ "Russian", "English", {"it", "animal"} };

	DatabaseHandler db;
	auto results = db.db_select(request);

	std::vector<std::string> parsed_results{ parseResult(results) };

	for (auto resultIter = parsed_results.begin(), expected = expectedResults.begin(); resultIter != parsed_results.end() && expected != expectedResults.end(); ++resultIter, ++expected) {
		ASSERT_EQ(*resultIter, *expected);
	}
}

TEST_F(DatabaseHandlerTest, select_Without_Native_Language)
{
	ParsedRequest request{ "", "English", {"it", "animal"} };
	DatabaseHandler db;
	auto results = db.db_select(request);

	ASSERT_TRUE(results.empty());
}


TEST_F(DatabaseHandlerTest, select_Without_Translated_Language)
{
	ParsedRequest request{ "English", "", {"it", "animal"} };
	DatabaseHandler db;
	auto results = db.db_select(request);

	ASSERT_TRUE(results.empty());
}

TEST_F(DatabaseHandlerTest, select_Without_Themes)
{
	ParsedRequest request{ "English", "Russian", {} };
	DatabaseHandler db;
	auto results = db.db_select(request);

	ASSERT_TRUE(results.empty());
}


std::vector<std::string> parseResult(const pqxx::result& result) {
	std::vector<std::string> parsed_results;
	for (auto result : result) {
		parsed_results.push_back(result[0].c_str());
		parsed_results.push_back(result[1].c_str());
	}
	
	return parsed_results;
}