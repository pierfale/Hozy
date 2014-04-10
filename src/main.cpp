#include "ModuleManager.hpp"
#include "view/ModuleView.hpp"
#include "network/ModuleNetwork.hpp"
#include <iostream>

int main() {

    //Register the ModuleManager to SingletonManager
    ModuleManager::register_singleton("ModuleManager", 0);

    //Register all module to SingletonManager
    ModuleView::register_singleton("ModuleView", 1);
    ModuleNetwork::register_singleton("ModuleNetwork", 1);

    //Initialize all register singleton instance
    SingletonManager::initialize_all();

    //Register module to ModuleManager
    ModuleManager::register_module("view", ModuleView::instance());
    ModuleManager::register_module("network", ModuleNetwork::instance());

    //Set events handler
    ModuleManager::set_event_handler("view", "network", ModuleView::network_event_handler);





    SingletonManager::destroy_all();
    return 0;
}



