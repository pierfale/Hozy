#include "ModuleManager.hpp"
#include "EventManager.hpp"
#include "view/ModuleView.hpp"
#include "network/ModuleNetwork.hpp"
#include "tool/log/Log.hpp"
#include "tool/error/ErrorManager.hpp"
#include <iostream>

int main() {

    //Register Log to SingletonManager
    Log::register_singleton("Log", 0);

    // Exception on singleton : use log before initialize
    Log::add(new LogStream(&std::cout, LOG_INFO | LOG_DEBUG));
    Log::add(new LogStream(&std::cerr, LOG_ERROR | LOG_WARNING));
    Log::add(new LogFile("debug.log", LOG_DEBUG | LOG_ERROR));

    Log::lout << "Server start ..." << std::endl;

    //Register the ModuleManager to SingletonManager
    ModuleManager::register_singleton("ModuleManager", 1);

    //Register all module to SingletonManager
    ModuleNetwork::register_singleton("ModuleNetwork", 2);


    //Initialize all register singleton instance
    SingletonManager::initialize_all();

    //Register module to ModuleManager
    ModuleManager::register_module("network", ModuleNetwork::instance());

    //Set events handler
    //EventManager<NetworkEvent>::set_event_handler("view", "network", ModuleView::network_event_handler);


    //Destroy all registered singleton contains in SingletonManager
    SingletonManager::destroy_all();
    return 0;
}



