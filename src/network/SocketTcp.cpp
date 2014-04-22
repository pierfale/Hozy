#include "network/SocketTcp.hpp"

SocketTcp::SocketTcp() : _socket(), _status(DISCONNECTED) {

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
		addr_in.sin_port = htons(port);


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
    if(_status == CONNECTED)
        throw_error(E_SOCKET_CLOSED);

	// Receive header
	struct Packet::Header header;
	unsigned int curr = 0;
    int err;

	do {
		if((err = recv(_socket, (char*)&header, sizeof(struct Packet::Header)-curr, 0)) == SOCKET_ERROR) {
			throw_error_os(E_SOCKET_RECEIVE_FAILED, ERR_NO);
		}

		if(err == 0) {
			close();
			throw_error(E_SOCKET_CLOSED);
		}

		curr += err;

	} while(curr < sizeof(struct Packet::Header));

	if(header.check_code != PACKET_CHECK) {
        close();
        throw_error(E_SOCKET_DATA);
    }

	//Copy header
	std::memcpy(packet._buffer.get_base(), &header, sizeof(struct Packet::Header));

	//Receiver contents
    curr = 0;
	packet._buffer.reserve(header.size);

    do {
		if((err = recv(_socket, (char*)packet._buffer.get_ptr()+curr, header.size-curr, 0)) == SOCKET_ERROR) {
            throw_error_os(E_SOCKET_RECEIVE_FAILED, ERR_NO);
        }

        if(err == 0) {
            close();
            throw_error(E_SOCKET_CLOSED);
        }

        packet._buffer.bump(err);
        curr += err;

	} while(curr < header.size);

	std::cout << "Receive : " << std::endl << packet.to_string() << std::endl;

}

void SocketTcp::send(Packet& packet) {
    if(_status == CONNECTED)
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

	std::cout << "Send : " << std::endl << packet.to_string() << std::endl;
}

void SocketTcp::close() {
    if(_status == CONNECTED) {
        closesocket(_socket);
        _status = DISCONNECTED;
    }
}
