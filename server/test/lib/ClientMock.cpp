#include "ClientMock.hh"
#include <thread>

void ClientMock::startSessions(size_t numberOfSessions) {
	for (auto i = 0; i < numberOfSessions; ++i) {
		m_sessions.emplace_back(std::make_shared<ClientSession>(m_context, i));
	}

	for (auto& session : m_sessions) {
		session->m_socket.async_connect(m_endPoint, std::bind(&ClientSession::start, session, std::placeholders::_1));
	}

	for (auto i = 0; i < numberOfSessions; ++i) {
		std::thread service_th([this]() {
			m_context.run();
			});
		
		service_th.detach();
	}
}