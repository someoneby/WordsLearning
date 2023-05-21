#include "Server.hh"

void Server::start()
{
	if(m_start) 
		return;

	m_start = true;

	std::thread th([this]() {
		while (true) {
			std::cout << "\nActive sessions:";
			for(auto sessionPair : m_activeSessions) {
				std::cout << sessionPair.first << " " << sessionPair.second << "\n";
			}
			std::cout << "\n\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		});
	th.detach();

	acceptNewSession();

	m_context.run(); //TODO make it concurrent
}

void Server::stop() {
	m_start = false;
}

void Server::addRequestHandler(std::shared_ptr<IRequestHandler> handler) {
	m_requestHandlers.push_back(handler);
}

Server::Server() : m_context{ boost::asio::io_context() },
m_acceptor{ m_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 7777) },
m_start{ false } {}

Server::~Server() {
	stop();
}

void Server::async_accept(std::shared_ptr<Session> session, const boost::system::error_code& err)
{
	if (err || !m_start)
		return;

	m_activeSessions.insert({ session, std::time(nullptr) });

	session->start();

	acceptNewSession();
}

void Server::acceptNewSession() {
	auto session = Session::createSession(m_context, std::ref(m_requestHandlers));
	m_acceptor.async_accept(session->getSocket(), std::bind(&Server::async_accept, this, session, std::placeholders::_1));
}