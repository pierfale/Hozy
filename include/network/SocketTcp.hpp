#ifndef SOCKET_TCP_HPP
#define SOCKET_TCP_HPP

#ifdef UNIX
#include <unistd.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define ERR_NO errno
#define closesocket(sck) ::close(sck)
#elif defined WIN32
#include <winsock2.h>
#include <windows.h>
#include <Ws2tcpip.h>
#include <w32api.h>

#define ERR_NO WSAGetLastError()
#define inet_ntop InetNtop
#endif

#include "tool/error/ErrorManager.hpp"
#include "network/NetAddress.hpp"
#include "network/Packet.hpp"


class SocketTcp {

	friend class ServerTcp;
    friend class ClientSelector;

public:
    enum Status {
        DISCONNECTED,
        CONNECTED
    };

    SocketTcp();
    ~SocketTcp();

	void connect(const NetAddress& address, unsigned int port);
	void receive(Packet& packet);
	void send(Packet& packet);
    void close();

	std::string to_string();

private:
    SocketTcp(const SocketTcp& origin);
    SocketTcp& operator=(const SocketTcp& origin);

	SOCKET _socket;
    Status _status;
};

#endif
