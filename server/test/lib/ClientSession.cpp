#include <iostream>
#include <gtest/gtest.h>

#include "ClientSession.hh"

void ClientSession::start(const boost::system::error_code& err) {
    if (err) return;
    
    doRequest();
}

void ClientSession::doRequest() {
    m_request.clear();
    m_request += "request id:";
    m_request += std::to_string(m_id) += ", number:";
    m_request += std::to_string(m_request_number++) += "\n";

    m_socket.async_send(boost::asio::buffer(m_request), std::bind(&ClientSession::readAnswer, this, std::placeholders::_1));
}

void ClientSession::readAnswer(const boost::system::error_code& err) {
    if (err) return;

    boost::asio::async_read_until(m_socket, m_inBuff, '\n', std::bind(&ClientSession::onRead, this, std::placeholders::_1));
}

void ClientSession::onRead(const boost::system::error_code& err) {
    if (err) return;

    std::ostringstream stream;
    stream << &m_inBuff;
    m_answer = stream.str();

    m_request += '\n';

    ASSERT_EQ(m_request, m_answer);

    doRequest();
}