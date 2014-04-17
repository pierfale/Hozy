#ifndef SOCKET_TCP_HPP
#define SOCKET_TCP_HPP

#ifdef UNIX
#define SOCKET int
#define INVALID_SOCKET -1
#define ERR_NO errno
#elif defined WIN32
#include <winsock2.h>
#include <windows.h>
#define ERR_NO WSAGetLastError()
#endif


#include "network/NetAddress.hpp"
#include "network/Packet.hpp"
#include "tool/error/ErrorManager.hpp"

class SocketTcp {

public:
    SocketTcp();

	void connect(const NetAddress& address, unsigned int port);
	void receive(Packet& packet);
	void send(Packet& packet);

private:
	SOCKET _socket;
};

#endif
