#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <thread>
#include "tool/Singleton.hpp"

class Module;
class Thread;

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
    static void register_module(const std::string&, Module* module);

    /**
     * @brief get_module : con throw an exception if the name ID is not found
     * @param name : ID of the module
     * @return module's instance associate to the name ID
     */
    static Module* get_module(const std::string& name);

    static Thread* start_thread(const std::string& name);

protected:
    ModuleManager();
    virtual void initialize();
    virtual void destroy();

private:
    /**
     * @brief _module_list : associate module instance with his name ID
     */
    std::map<std::string, Module*> _module_list;
};

#endif
