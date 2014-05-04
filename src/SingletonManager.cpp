#include "SingletonManager.hpp"
#include "tool/log/Log.hpp"

SingletonManager::SingletonInfo::SingletonInfo(ProtoSingleton* _instance, unsigned int _priority, State _state) : instance(_instance), priority(_priority), state(_state) {

}

void SingletonManager::add(const std::string& name, ProtoSingleton* instance, unsigned int priority) {
	_singleton_list.insert(std::pair<std::string,struct SingletonInfo>(name, SingletonInfo(instance, priority, UNINITIALIZED)));
    Log::ldebug << "[SingletonManager] Adding " << name << std::endl;
}

void SingletonManager::initialize_all() {
    std::vector<std::string> init_complete;

    while(init_complete.size() < _singleton_list.size()) {
        unsigned int priority_max  = std::numeric_limits<int>::max();
        std::string id_max = "";
        for(const auto& singleton : _singleton_list) {
            if(std::find(init_complete.begin(), init_complete.end(), singleton.first) == init_complete.end() && singleton.second.priority < priority_max) {
                id_max = singleton.first;
                priority_max = singleton.second.priority;
            }
        }



        auto it = _singleton_list.find(id_max);

		if(it->second.state == UNINITIALIZED) {
			it->second.instance->initialize();
			it->second.state = INITIALIZED;
			Log::ldebug << "[SingletonManager] Initialize " << id_max << " (priority " << priority_max << ")" << std::endl;
		}
        init_complete.push_back(id_max);
    }
}

void SingletonManager::destroy_all() {
    std::vector<std::string> destroy_complete;

    while(destroy_complete.size() < _singleton_list.size()) {
        unsigned int priority_max  = 0;
        std::string id_max = "";
        for(const auto& singleton : _singleton_list) {
            if(std::find(destroy_complete.begin(), destroy_complete.end(), singleton.first) == destroy_complete.end() && (singleton.second.priority > priority_max || id_max == ""))  {
                id_max = singleton.first;
                priority_max = singleton.second.priority;
            }
        }

        auto it = _singleton_list.find(id_max);

		if(it->second.state == INITIALIZED) {
			Log::ldebug << "[SingletonManager] Destroy " << id_max << " (priority " << priority_max << ")" << std::endl;
			it->second.instance->destroy();
			it->second.state = DESTROYED;
			delete it->second.instance;
		}
        destroy_complete.push_back(id_max);
    }
}
