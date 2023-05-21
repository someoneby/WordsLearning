#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <memory>

#include "../RequestHandler//IRequestHandler.hh"

struct Session
{
	static std::shared_ptr<Session> createSession(boost::asio::io_context &context, std::vector<std::shared_ptr<IRequestHandler>> &handlers);

	void start();
	boost::asio::ip::tcp::socket &getSocket();

	Session(boost::asio::io_context &context, std::vector<std::shared_ptr<IRequestHandler>> &handlers) : m_socket{boost::asio::ip::tcp::socket(context) }, m_handlers{handlers} {} // TODO make constructor private
private:
	// Read message from client into buffer
	void do_read();

	// Get message from buffer into string and handle it
	void on_read();

	// Send answer to the client
	void do_write();

	// Clear useless session data
	void on_write();

	void setPtr(std::shared_ptr<Session> self);
	void getRequestFromBuffer();
	void clearBuffer();

	boost::asio::ip::tcp::socket m_socket;
	std::shared_ptr<Session> m_ptr;
	boost::asio::streambuf m_inStream;
	std::string m_request;
	std::vector <std::string> m_answers;
	std::vector< std::shared_ptr<IRequestHandler>> &m_handlers;
};