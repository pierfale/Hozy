#include "os/unix/SocketTcpImpl_unix.hpp"

SocketTcpImpl_unix::SocketTcpImpl_unix() {
/*
    _socket = socket(AF_INET, SOCK_STREAM, 0);

    if(_socket == -1) {
        throw_error_os(E_SOCKET_CREATE_FAILED, errno);
    }*/
}

void SocketTcpImpl_unix::connect(const NetAddress& address, unsigned int port) {
   /* address
    if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == -1) {
        throw_error_os(E_SOCKET_CONNECT_FAILED, errno);
    }*/

}
