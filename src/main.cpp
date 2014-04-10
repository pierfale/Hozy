#include "view/ModuleView.hpp"
#include "network/ModuleNetwork.hpp"
#include <iostream>

int main() {

    ModuleView::register_manager("ModuleView", 0);
    ModuleNetwork::register_manager("ZModuleNetwork", 0);

    SingletonManager::initialize_all();


    SingletonManager::destroy_all();
}
