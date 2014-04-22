#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client {

public:
	Client(SocketTcp socket);

private:
	SocketTcp _socket;
};

#endif
