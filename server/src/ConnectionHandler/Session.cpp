#include "Session.hh"
#include "../RequestHandler/RequestHandler.hh"

const std::string messageEnd = "\n";

std::shared_ptr<Session> Session::createSession(boost::asio::io_context& context, std::vector<std::shared_ptr<IRequestHandler>>& handlers) {
	auto ptr = std::make_shared<Session>(context, handlers);
	ptr->setPtr(ptr);
	
	return ptr;
}

void Session::start() {
	do_read();
}

boost::asio::ip::tcp::socket& Session::getSocket() {
	return m_socket;
}

void Session::do_read() {
	boost::asio::async_read_until(m_socket, m_inStream, messageEnd, std::bind(&Session::on_read, m_ptr));
}

void Session::on_read() {
	getRequestFromBuffer();

	clearBuffer();

	for(auto& handler : m_handlers) {
		m_answers.push_back(handler->handleRequest(m_request));
	}

	do_write();
}

void Session::do_write() {
	std::vector<boost::asio::const_buffer> buffer;

	for (std::string& answer : m_answers) {
		buffer.push_back(boost::asio::buffer(answer));
	}
	buffer.push_back(boost::asio::buffer(messageEnd));

	m_socket.async_send(buffer, std::bind(&Session::on_write, m_ptr));
}

void Session::on_write() {
	m_request.clear();
	m_answers.clear();

	do_read();
}

void Session::setPtr(std::shared_ptr<Session> ptr) {
	m_ptr = ptr;
}

void Session::getRequestFromBuffer() {
	 std::ostringstream stream;
	 stream << &m_inStream;
	 m_request = stream.str();
}

void Session::clearBuffer() {
	std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
	std::cout << &m_inStream << std::endl;
	std::cout.rdbuf(oldCoutStreamBuf);
}