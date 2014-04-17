#include "network/SocketTcp.hpp"

SocketTcp::SocketTcp() {
	_socket = socket(AF_INET, SOCK_STREAM, 0);

	if(_socket == INVALID_SOCKET) {
		throw_error_os(E_SOCKET_CREATE_FAILED, ERR_NO);
	}
}

void SocketTcp::connect(const NetAddress& address, unsigned int port) {
	if(::connect(_socket, (const sockaddr*)address.generateAddressStruct(port), sizeof(SOCKADDR)) == -1) {
		throw_error_os(E_SOCKET_CONNECT_FAILED, ERR_NO);
	}
}
