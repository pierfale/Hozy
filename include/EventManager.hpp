#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include "tool/Singleton.hpp"

//class Module;

#include <vector>

template<class T>
/**
 * @brief EventManager class
 */
class EventManager {

public:

    /**
     * @brief set_event_handler : register a function for owner module which receive event triggered by target module
     * Can throw an exception if owner has already an handler registered for the module target
     * @param owner : module which receive event
     * @param target : module which trigger event
     * @param handler : function of owner for receive event. need to be static
     */
    static void set_event_handler(std::string owner, std::string target, void(*handler)(T*)) {
        Module* owner_instance = ModuleManager::getModule(owner);
        auto it_owner = _event_trigger.find(owner_instance);

        if(it_owner == _event_trigger.end()) {
            _event_trigger.insert(std::pair<Module*, std::vector<std::pair<Module*, void(*)(T*)>>>(owner_instance, std::vector<std::pair<Module*, void(*)(T*)>>()));
            it_owner = _event_trigger.find(owner_instance);
        }

        Module* target_instance = ModuleManager::getModule(target);

        for(const auto& event_handler : it_owner->second) {
            if(event_handler.first == target_instance)
                std::cerr << "Event Handler for " << target << " => " << owner << " already registered" << std::endl;
        }

        it_owner->second.push_back(std::pair<Module*, void(*)(T*)>(target_instance, handler));

    }


    /**
     * @brief trigger a event to all register module which own a handler for the transmitter module
     * @param transmitter module
     * @param event
     */
    static void trigger(Module* transmitter, T* event) {
        for(const auto& module : _event_trigger) {
            for(unsigned int i=0; i<module.second.size(); i++) {
                if(module.second.at(i).first == transmitter)
                    (module.second.at(i).second)(event);
            }
        }
    }

private:
    /**
     * @brief _event_trigger store handle associate with an owner and a target
     */
    static std::map<Module*, std::vector<std::pair<Module*, void(*)(T*)>>> _event_trigger;
};


template<class T>
std::map<Module*, std::vector<std::pair<Module*, void(*)(T*)>>> EventManager<T>::_event_trigger;

#endif
