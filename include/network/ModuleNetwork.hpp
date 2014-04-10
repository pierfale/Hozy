#ifndef MODULE_NETWORK_HPP
#define MODULE_NETWORK_HPP

#include "tool/Singleton.hpp"
#include "ModuleManager.hpp"

class ModuleNetwork : public ModuleManager, public Singleton<ModuleNetwork> {

    friend class Singleton<ModuleNetwork>;

protected:
    virtual void initialize() {
        std::cout << "init network" << std::endl;
    }

    virtual void destroy() {
        std::cout << "destroy network" << std::endl;
    }

};

#endif
