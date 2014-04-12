#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <thread>
#include "tool/Singleton.hpp"

class Module;

/**
 * @brief The ModuleManager class is a singleton which contains all registered modules
 * firend of class Singleton<ModuleManager>
 */
class ModuleManager : public Singleton<ModuleManager> {

    friend class Singleton<ModuleManager>;

public:
    /**
     * @brief register_module : register module
     * @param name : ID
     * @param module : module's instance
     */
    static void register_module(std::string name, Module* module);

    /**
     * @brief getModule : con throw an exception if the name ID is not found
     * @param name : ID of the module
     * @return module's instance associate to the name ID
     */
    static Module* getModule(std::string name);

    static void start_thread(std::string name);

protected:
    ModuleManager() {}
    virtual void initialize();
    virtual void destroy();

private:
    /**
     * @brief _module_list : associate module instance with his name ID
     */
    std::map<std::string, Module*> _module_list;
};

#endif
