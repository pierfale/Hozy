#include "ModuleManager.hpp"
#include "Module.hpp"
#include "tool/Thread.hpp"
#include "tool/Function.hpp"

ModuleManager::ModuleManager() : _module_list() {

}

void ModuleManager::initialize() {

}

void ModuleManager::destroy() {

}

void ModuleManager::register_module(const std::string& name, Module* module) {
    if(instance()->_module_list.find(name) != instance()->_module_list.end()) {
        std::cerr << "Module already register : " << name << std::endl;
        return;
    }

    instance()->_module_list.insert(std::pair<std::string, Module*>(name, module));

}

Module* ModuleManager::get_module(const std::string& name) {
    auto it_module = instance()->_module_list.find(name);
    if(it_module == instance()->_module_list.end())
        std::cerr << "Module " << name << " not found" << std::endl;
    return it_module->second;
}

Thread* ModuleManager::start_thread(const std::string& name) {
    Module* module = get_module(name);
    Thread* thread = new Thread();
    thread->create(MemberFunction<Module, void>(module, &Module::run));
    return thread;
}
