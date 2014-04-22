#ifndef SERVER_TCP_HPP
#define SERVER_TCP_HPP

#include "network/SocketTcp.hpp"


class ServerTcp {

public:
    enum Status {
        DISCONNECTED,
        CONNECTED
    };

	ServerTcp();
	~ServerTcp();

	void listen(unsigned int port);
	bool accept(SocketTcp& socket);
	void close();

private:
	SOCKET _socket;
    Status _status;
};

#endif
