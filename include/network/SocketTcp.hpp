#ifndef SOCKET_TCP_HPP
#define SOCKET_TCP_HPP

class SocketTcp {

public:
    SocketTcp();

    void connect(const NetAdress& address);
};

#endif
