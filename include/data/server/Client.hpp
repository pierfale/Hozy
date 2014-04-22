#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "network/SocketTcp.hpp"

class Client {

public:
    Client(SocketTcp* socket);
    ~Client();

    bool authenticate(std::string pseudo, std::string password);

    SocketTcp* get_tcp_socket();
    std::string get_pseudo();

private:
    Client(const Client& origin);
    Client& operator=(const Client& origin);
    SocketTcp* _tcp_socket;
};

#endif
