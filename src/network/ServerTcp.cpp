#include "network/ServerTcp.hpp"

ServerTcp::ServerTcp() : _socket(0) {

}

ServerTcp::~ServerTcp() {
	close();
}

void ServerTcp::listen(unsigned int port) {
	close();

	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		throw_error_os(E_SOCKET_CREATE_FAILED, ERR_NO);
	}


	struct sockaddr_in sin;
	std::memset(&sin, 0, sizeof(struct sockaddr_in));
	sin.sin_addr.s_addr   = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port   = htons(port);

	if (bind(_socket, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {
		throw_error_os(E_SOCKET_BIND_FAILED, ERR_NO);
	}

	if (::listen(_socket, 10) == SOCKET_ERROR) {
		throw_error_os(E_SOCKET_LISTEN_FAILED, ERR_NO);
	}
}

bool ServerTcp::accept(SocketTcp& socket) {
	if(_socket == 0)
		throw_error(E_SOCKET_CLOSED);

	if ((socket._socket = ::accept(_socket, NULL, NULL)) == INVALID_SOCKET) {
		throw_error_os(E_SOCKET_ACCEPT_FAILED, ERR_NO);
	}
	return true;
}

void ServerTcp::close() {
	if(_socket == 0) {
		closesocket(_socket);
		_socket = 0;
	}
}
