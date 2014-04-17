#ifndef SOCKET_TCP_HPP
#define SOCKET_TCP_HPP

#ifdef WIN32
#include "os/win32/SocketTcpImpl_win32.hpp"
#define SOCKET_TCP_IMPLEMENTATION SocketTcpImpl_win32
#elif defined UNIX
#include "os/unix/SocketTcpImpl_unix.hpp"
#define SOCKET_TCP_IMPLEMENTATION SocketTcpImpl_unix
#else
#error "This Operating system is unsuported"
#endif

#include "network/NetAddress.hpp"

class SocketTcp {

public:
    SocketTcp();

    void connect(const NetAddress& address, unsigned int port);

private:
    SOCKET_TCP_IMPLEMENTATION impl;
};

#endif
