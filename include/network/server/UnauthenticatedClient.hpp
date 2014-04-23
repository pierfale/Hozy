#ifndef UNAUTHENTICATED_CLIENT_HPP
#define UNAUTHENTICATED_CLIENT_HPP


#include "data/server/Client.hpp"
#include "tool/Singleton.hpp"
#include "tool/Mutex.hpp"
#include "tool/Thread.hpp"
#include "network/server/ClientSelector.hpp"

class UnauthenticatedClient : public Singleton<UnauthenticatedClient> {

    friend class Singleton<UnauthenticatedClient>;

public:
    static void add(Client* client);

protected:
    void virtual initialize();
    void virtual destroy();

private:
    UnauthenticatedClient();
    void run();
    std::vector<Client*> _list_client;
    Mutex _mutex;
    ClientSelector _selector;
};

#endif
