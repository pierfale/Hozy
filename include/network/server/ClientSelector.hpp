#ifndef CLIENT_SELECTOR_HPP
#define CLIENT_SELECTOR_HPP

#ifdef UNIX
#define SOCKET_ERROR -1
#define ERR_NO errno
#define SOCKET int
#elif defined WIN32
#include <winsock2.h>
#include <windows.h>
#define ERR_NO WSAGetLastError()
#endif

#include <vector>
#include "tool/Mutex.hpp"

class Client;

class ClientSelector {

public:
    ClientSelector(const std::vector<Client*>& client_list, Mutex& mutex);

    unsigned int next();

private:
    const std::vector<Client*>& _client_list;
	Mutex& _mutex;
};

#endif
