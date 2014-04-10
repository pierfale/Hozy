#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include "tool/Singleton.hpp"

class Module;

class ModuleManager : public Singleton<ModuleManager> {

    friend class Singleton<ModuleManager>;

public:
    static void register_module(std::string name, Module* module);

    template<class T>
    static void set_event_handler(std::string owner, std::string target, void(*handler)(T)) {
        auto it_owner = instance()->_module_list.find(owner);
        if(it_owner == instance()->_module_list.end())
            std::cerr << "Module " << owner << " not found" << std::endl;
        auto it_target = instance()->_module_list.find(target);
        if(it_target == instance()->_module_list.end())
            std::cerr << "Module " << target << " not found" << std::endl;
        std::vector<std::pair<Module*, void(*)(void*)>> vec;
        vec.push_back(std::pair<Module*, void(*)(void*)>(it_target->second, (void(*)(void*))handler));
        instance()->_event_trigger.insert(std::pair<Module*, std::vector<std::pair<Module*, void(*)(void*)>>>(it_owner->second, vec));
    }


    template<class T>
    static void trigger(Module*, T event) {
        for(const auto& module : instance()->_event_trigger) {
            for(unsigned int i=0; i<module.second.size(); i++)
                (module.second.at(i))(event);
        }
    }

protected:
    ModuleManager() {}
    virtual void initialize();
    virtual void destroy();

private:

    std::map<std::string, Module*> _module_list;
    std::map<Module*, std::vector<std::pair<Module*, void(*)(void*)>>> _event_trigger;

};

#endif
