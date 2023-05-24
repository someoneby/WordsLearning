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
	std::string expected{ "lion;lev;cat;kot;computer;komputer;" };
	ParsedRequest request{ "English", "Russian", {"it", "animal"} };

	DatabaseHandler db;
	auto result = db.db_select(request);

	ASSERT_EQ(result, expected);
}

TEST_F(DatabaseHandlerTest, select_RU_TO_ENG)
{
	std::string expected{ "lev;lion;kot;cat;komputer;computer;" };
	ParsedRequest request{ "Russian", "English", {"it", "animal"} };

	DatabaseHandler db;
	auto result = db.db_select(request);

	ASSERT_EQ(result, expected);
}

TEST_F(DatabaseHandlerTest, select_Without_Native_Language)
{
	ParsedRequest request{ "", "English", {"it", "animal"} };
	DatabaseHandler db;
	auto result = db.db_select(request);

	ASSERT_TRUE(result.empty());
}


TEST_F(DatabaseHandlerTest, select_Without_Translated_Language)
{
	ParsedRequest request{ "English", "", {"it", "animal"} };
	DatabaseHandler db;
	auto result = db.db_select(request);

	ASSERT_TRUE(result.empty());
}

TEST_F(DatabaseHandlerTest, select_Without_Themes)
{
	ParsedRequest request{ "English", "Russian", {} };
	DatabaseHandler db;
	auto result = db.db_select(request);

	ASSERT_TRUE(result.empty());
}