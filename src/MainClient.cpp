#include "ModuleManager.hpp"
#include "EventManager.hpp"
#include "view/ModuleView.hpp"
#include "network/client/ModuleNetworkClient.hpp"
#include "tool/log/Log.hpp"
#include "tool/error/ErrorManager.hpp"
#include "tool/Thread.hpp"
#include "ThreadManager.hpp"
#include "tool/Function.hpp"
#include "network/SocketTcp.hpp"
#include <iostream>

int main() {

    try {
        //Register Log to SingletonManager
        Log::register_singleton("Log", 0);

        // Exception on singleton : use log before initialize
        Log::add(new LogStream(&std::cout, LOG_INFO | LOG_DEBUG));
        Log::add(new LogStream(&std::cerr, LOG_ERROR | LOG_WARNING));
        Log::add(new LogFile("debug.log", LOG_DEBUG | LOG_ERROR));

        Log::lout << "Client start ..." << std::endl;

        //Register the ModuleManager and threadManager to SingletonManager
        ThreadManager::register_singleton("ThreadManager", 1);
        ModuleManager::register_singleton("ModuleManager", 1);

        //Register all module to SingletonManager
        ModuleView::register_singleton("ModuleView", 2);
		ModuleNetworkClient::register_singleton("ModuleNetwork", 2);


        //Initialize all register singleton instance
        SingletonManager::initialize_all();

        //Register module to ModuleManager
        ModuleManager::register_module("view", ModuleView::instance());
		ModuleManager::register_module("network", ModuleNetworkClient::instance());

        //Set events handler
		//EventManager<NetworkEvent>::set_event_handler("view", "network", ModuleView::network_event_handler);

		ModuleManager::start_thread("network");


		//wait all thread alive
		ThreadManager::wait_all();

        //Destroy all registered singleton contains in SingletonManager
        SingletonManager::destroy_all();

    }
	catch(Exception const& e) {
		std::cerr.flush();
		std::cerr << std::string(e.what()) << std::endl;
		std::cerr.flush();
        return e.get_error_code();
    }

    return 0;
}



