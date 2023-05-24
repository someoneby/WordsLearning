#include <gtest/gtest.h>

#include "../src/RequestHandler/RequestHandler.hh"

#include "lib/DatabaseHandlerMock.hh""

TEST(Request_handler, test) {
	std::string expected{ "test words: screen,экран,телефон,стол,кот;lion,лев,телефон,компьютер,кот;\
phone,телефон,экран,компьютер,стол;computer,компьютер,телефон,стол,кот;table,стол,экран,компьютер,кот;cat,кот,экран,лев,стол;" };
	
	ParsedRequest request;
	RequestHandler rh(std::make_unique<DatabaseHandlerMock>());
	auto answer = rh.handleRequest(request);

	ASSERT_EQ(expected, answer);
}