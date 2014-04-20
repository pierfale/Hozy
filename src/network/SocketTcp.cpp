#include "network/SocketTcp.hpp"

SocketTcp::SocketTcp() : _socket(0) {

}

SocketTcp::~SocketTcp() {
    close();
}

void SocketTcp::connect(const NetAddress& address, unsigned int port) {
    close();

    if(address.type() == NetAddress::IPV4) {



		if((_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
            throw_error_os(E_SOCKET_CREATE_FAILED, ERR_NO);
        }

        struct sockaddr_in addr_in;
        memcpy(&addr_in, address.address(), sizeof(struct sockaddr_in));
        addr_in.sin_port = port;


		if(::connect(_socket, (const sockaddr*)&addr_in, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
            throw_error_os(E_SOCKET_CONNECT_FAILED, ERR_NO);
        }
    }
    else if(address.type() == NetAddress::IPV6) {

		if((_socket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
            throw_error_os(E_SOCKET_CREATE_FAILED, ERR_NO);
        }

        struct sockaddr_in6 addr_in;
        memcpy(&addr_in, address.address(), sizeof(struct sockaddr_in6));
        addr_in.sin6_port = port;


		if(::connect(_socket, (const sockaddr*)&addr_in, sizeof(struct sockaddr_in6)) == SOCKET_ERROR) {
            throw_error_os(E_SOCKET_CONNECT_FAILED, ERR_NO);
        }
    }

}

void SocketTcp::receive(Packet& packet) {
    if(_socket == 0)
        throw_error(E_SOCKET_CLOSED);

    uint32_t header;

    int err;

	if((err = recv(_socket, (char*)&header, sizeof(uint32_t), 0)) == SOCKET_ERROR) {
        throw_error_os(E_SOCKET_RECEIVE_FAILED, ERR_NO);
    }

    if(err == 0) {
        close();
        throw_error(E_SOCKET_CLOSED);
    }

    if(err < (int)sizeof(uint32_t)) {
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
		if((err = recv(_socket, (char*)packet._buffer.get_ptr(), size-curr, 0)) == SOCKET_ERROR) {
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
    if(_socket == 0)
        throw_error(E_SOCKET_CLOSED);

	std::size_t send_size = 0;

	while(send_size < packet._buffer.get_size()) {
		int err;
		if((err = ::send(_socket, (char*)packet._buffer.get_base()+send_size, packet._buffer.get_size()-send_size, 0)) == SOCKET_ERROR) {
			throw_error_os(E_SOCKET_SEND_FAILED, ERR_NO);
		}

		if(err == 0) {
			close();
			throw_error(E_SOCKET_CLOSED);
		}

		send_size += err;
	}
}

void SocketTcp::close() {
    if(_socket == 0) {
        closesocket(_socket);
        _socket = 0;
    }
}
