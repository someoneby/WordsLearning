#include <gtest/gtest.h>
#include "../src/ConnectionHandler/Server.hh"
#include "lib/ClientMock.hh"
#include "lib/RequestHandlerEchoMock.hh"

TEST(Server, start)
{
	Server server;
	server.addRequestHandler(std::make_shared<RequestHandlerEchoMock>());
	
	std::thread server_th([&](){ server.start(); });

	server_th.detach();

	ClientMock clientMock;
	clientMock.startSessions();

	std::this_thread::sleep_for(std::chrono::seconds(60));

	server.stop();
}