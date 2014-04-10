#ifndef MODULE_VIEW_HPP
#define MODULE_VIEW_HPP

#include <vector>
#include "tool/Singleton.hpp"
#include "ModuleManager.hpp"

class ModuleView : public ModuleManager, public Singleton<ModuleView> {

    friend class Singleton<ModuleView>;

protected:
    virtual void initialize() {
        std::cout << "init ModuleView" << std::endl;
    }

    virtual void destroy() {
        std::cout << "destroy ModuleView" << std::endl;
    }

private:
    std::vector<int> _test;

};

#endif
