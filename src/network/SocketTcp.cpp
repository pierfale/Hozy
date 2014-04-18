#include "network/SocketTcp.hpp"

SocketTcp::SocketTcp() : _socket(-1) {

}

SocketTcp::~SocketTcp() {
    close();
}

void SocketTcp::connect(const NetAddress& address, unsigned int port) {
    close();

    if(address.type() == NetAddress::IPV4) {

        _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if(_socket == INVALID_SOCKET) {
            throw_error_os(E_SOCKET_CREATE_FAILED, ERR_NO);
        }

        struct sockaddr_in addr_in;
        memcpy(&addr_in, address.address(), sizeof(struct sockaddr_in));
        addr_in.sin_port = port;


        if(::connect(_socket, (const sockaddr*)&addr_in, sizeof(struct sockaddr_in)) == -1) {
            throw_error_os(E_SOCKET_CONNECT_FAILED, ERR_NO);
        }
    }
    else if(address.type() == NetAddress::IPV6) {
        _socket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

        if(_socket == INVALID_SOCKET) {
            throw_error_os(E_SOCKET_CREATE_FAILED, ERR_NO);
        }

        struct sockaddr_in6 addr_in;
        memcpy(&addr_in, address.address(), sizeof(struct sockaddr_in6));
        addr_in.sin6_port = port;


        if(::connect(_socket, (const sockaddr*)&addr_in, sizeof(struct sockaddr_in6)) == -1) {
            throw_error_os(E_SOCKET_CONNECT_FAILED, ERR_NO);
        }
    }

}

void SocketTcp::receive(Packet& packet) {
    uint32_t header;

    int err;

    if((err = recv(_socket, &header, sizeof(uint32_t), 0)) == -1) {
        throw_error_os(E_SOCKET_RECEIVE_FAILED, ERR_NO);
    }

    if(err == 0) {
        close();
        throw_error(E_SOCKET_CLOSED);
    }

    if(err < sizeof(uint32_t)) {
        close();
        throw_error(E_SOCKET_DATA);
    }

    if(header >> 16 != PACKET_CHECK) {
        close();
        throw_error(E_SOCKET_DATA);
    }

    uint16_t size, curr;
    size = header & 0xFFFF;
    curr = 0;

    packet._buffer.reserve(size);

    do {
        if((err = recv(_socket, packet._buffer.get_ptr(), size-curr, 0)) == -1) {
            throw_error_os(E_SOCKET_RECEIVE_FAILED, ERR_NO);
        }

        if(err == 0) {
            close();
            throw_error(E_SOCKET_CLOSED);
        }

        packet._buffer.bump(err);
        curr += err;

    } while(curr < size);

}

void SocketTcp::send(Packet& packet) {

}

void SocketTcp::close() {
    if(_socket == -1) {
        closesocket(_socket);
        _socket = -1;
    }
}
