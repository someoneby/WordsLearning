#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <memory>

#include "ClientSession.hh"

struct ClientMock {
    void startSessions(size_t numberOfSessions = 8);

    ClientMock() : m_context{ boost::asio::io_context() }, m_endPoint{ boost::asio::ip::address::from_string("127.0.0.1"), 7777 }, m_sessions {} {}

private:
    boost::asio::io_context m_context;
    boost::asio::ip::tcp::endpoint m_endPoint;
    std::vector<std::shared_ptr<ClientSession>> m_sessions;
};