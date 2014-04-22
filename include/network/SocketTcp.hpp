#ifndef SOCKET_TCP_HPP
#define SOCKET_TCP_HPP

#ifdef UNIX
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define ERR_NO errno
#define closesocket(sck) close(sck)
#elif defined WIN32
#include <winsock2.h>
#include <windows.h>
#define ERR_NO WSAGetLastError()
#endif

#include "tool/error/ErrorManager.hpp"
#include "network/NetAddress.hpp"
#include "network/Packet.hpp"


class SocketTcp {

	friend class ServerTcp;

public:
    SocketTcp();
    ~SocketTcp();

	void connect(const NetAddress& address, unsigned int port);
	void receive(Packet& packet);
	void send(Packet& packet);
    void close();

private:
	SOCKET _socket;
};

#endif
