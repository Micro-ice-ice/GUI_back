#include <boost/asio.hpp>

using namespace boost::asio;
using namespace std;
class Server
{
private:
    /* data */
public:
    Server(string ip, int port);
    ~Server();
};

Server::Server(string ip, int port)
{
    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string(ip), port);
    ip::tcp::acceptor acc(service, ep);
}

Server::~Server()
{
}
