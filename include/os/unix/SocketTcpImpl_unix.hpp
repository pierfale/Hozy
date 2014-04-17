#ifndef SOCKET_TCP_IMPLEMENT_UNIX_HPP
#define SOCKET_TCP_IMPLEMENT_UNIX_HPP

#include "network/NetAddress.hpp"
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


class SocketTcpImpl_unix {

public:
    SocketTcpImpl_unix();

    void connect(const NetAddress& address, unsigned int port);

private:
    int _socket;

};

#endif
