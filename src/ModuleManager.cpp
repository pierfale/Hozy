#include "ModuleManager.hpp"
#include "Module.hpp"

void ModuleManager::initialize() {

}

void ModuleManager::destroy() {

}

void ModuleManager::register_module(std::string name, Module* module) {
    if(instance()->_module_list.find(name) != instance()->_module_list.end()) {
        std::cerr << "Module already register : " << name << std::endl;
        return;
    }

    instance()->_module_list.insert(std::pair<std::string, Module*>(name, module));

}
