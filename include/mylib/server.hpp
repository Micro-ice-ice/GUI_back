#include <boost/asio.hpp>

using namespace boost::asio;
class Server
{
private:
    /* data */
public:
    Server(/* args */);
    ~Server();
};

Server::Server(/* args */)
{
    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8000);
    ip::tcp::acceptor acc(service, ep);
}

Server::~Server()
{
}
