#ifndef SERVER_HPP
#define SERVER_HPP

#include "network/server/ModuleNetworkServer.hpp"
#include "ModuleManager.hpp"
#include "EventManager.hpp"
#include "view/ModuleView.hpp"
#include "tool/log/Log.hpp"
#include "tool/error/ErrorManager.hpp"
#include "ThreadManager.hpp"
#include "tool/Thread.hpp"
#include <iostream>

class Server {

public:
    static int start();
    static bool is_running();

private:
    Server();
    static void exit_handler(int sig);
    static bool _running;

};

#endif
