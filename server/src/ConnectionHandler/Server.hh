#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include <map>

#include "Session.hh"
#include "../RequestHandler/IRequestHandler.hh"

struct Server
{
	void start();
	void stop();
	void addRequestHandler(std::shared_ptr<IRequestHandler> handler);

	Server();
	~Server();
private:
	void async_accept(std::shared_ptr<Session> session, const boost::system::error_code& err);
	void acceptNewSession();
	void handleActiveSessions();

	boost::asio::io_context m_context;
	boost::asio::ip::tcp::acceptor m_acceptor;
	std::vector<std::shared_ptr<IRequestHandler>> m_requestHandlers;
	std::map<std::shared_ptr<Session>, std::time_t> m_activeSessions;
	bool m_start;
};