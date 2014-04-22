#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "network/SocketTcp.hpp"

class Client {

public:
    Client(SocketTcp* socket);
    ~Client();

    SocketTcp* get_tcp_socket();

private:
    Client(const Client& origin);
    Client& operator=(const Client& origin);
    SocketTcp* _tcp_socket;
};

#endif
