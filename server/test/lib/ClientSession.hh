#pragma once

#include <boost/asio.hpp>

struct ClientSession
{
    ClientSession(boost::asio::io_context& context, size_t sessionNumber) : m_socket{ context }, m_id{ sessionNumber }, m_request_number{ 1 } {}
    void start(const boost::system::error_code& err);

    boost::asio::ip::tcp::socket m_socket;
private:
    void doRequest();
    void readAnswer(const boost::system::error_code& err);
    void onRead(const boost::system::error_code& err);

    boost::asio::streambuf m_inBuff;
    std::string m_request, m_answer;
    size_t m_id;
    size_t m_request_number;
};