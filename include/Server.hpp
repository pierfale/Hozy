#ifndef SERVER_HPP
#define SERVER_HPP

#include "ModuleManager.hpp"
#include "EventManager.hpp"
#include "view/ModuleView.hpp"
#include "network/server/ModuleNetworkServer.hpp"
#include "tool/log/Log.hpp"
#include "tool/error/ErrorManager.hpp"
#include "ThreadManager.hpp"
#include "tool/Thread.hpp"
#include <iostream>

class Server {

public:
    Server();
    int start();
    bool is_running();

private:
    static void exit_handler(int sig);
    bool _running;

};

#endif
