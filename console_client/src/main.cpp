#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main()
{
  try
  {
    boost::asio::io_context io_context;

    tcp::socket s(io_context);
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 7777);
    s.connect(ep);

    std::string request = "request fewefe\n";
    size_t request_length = request.length();
    boost::asio::write(s, boost::asio::buffer(request, request_length));

    boost::asio::streambuf buf;
    boost::asio::read_until(s, buf, '\n');
    std::ostringstream stream;
    stream << &buf;
    std::string msg = stream.str();



    std::cout << "Reply is: ";
    std::cout << msg;
    std::cout << "\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}