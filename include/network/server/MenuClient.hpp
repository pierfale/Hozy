#ifndef MENU_CLIENT_HPP
#define MENU_CLIENT_HPP

#include "tool/Singleton.hpp"
#include "data/server/Client.hpp"
#include "tool/Mutex.hpp"
#include "tool/Thread.hpp"
#include "network/server/ClientSelector.hpp"

class MenuClient : public Singleton<MenuClient> {

    friend class Singleton<MenuClient>;

public:
    static void add(Client* client);

protected:
    void virtual initialize();
    void virtual destroy();

private:
    MenuClient();
    void run();
    std::vector<Client*> _list_client;
    Mutex _mutex;
    ClientSelector _selector;
};

#endif
