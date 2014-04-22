#include "network/SocketTcp.hpp"

SocketTcp::SocketTcp() : _socket(), _status(DISCONNECTED){

}

SocketTcp::SocketTcp(const SocketTcp& origin __attribute__((unused))) : SocketTcp() {

}

SocketTcp& SocketTcp::operator=(const SocketTcp& origin __attribute__((unused))) {
    return *this;
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
}

void SocketTcp::close() {
    if(_status == CONNECTED) {
        closesocket(_socket);
        _status = DISCONNECTED;
    }
}

std::string SocketTcp::to_string() {
    struct sockaddr_storage addr;
    int size = sizeof(struct sockaddr_storage);
    char addr_str[INET6_ADDRSTRLEN];

    if(getpeername(_socket, &addr, &size) == SOCKET_ERROR) {
        throw_error_os(E_ADDRESS_NOT_FOUND, ERR_NO);
    }

    if(addr.ss_family == AF_INET) {
        struct sockaddr_in *s = (struct sockaddr_in *)&addr;
        port = ntohs(s->sin_port);
        inet_ntop(AF_INET, &s->sin_addr, addr_str, INET6_ADDRSTRLEN);

        return
    } else if(addr.ss_family == AF_INET6) {
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
        port = ntohs(s->sin6_port);
        inet_ntop(AF_INET6, &s->sin6_addr, ipstr, INET6_ADDRSTRLEN);
    }

    return *_address;
}
