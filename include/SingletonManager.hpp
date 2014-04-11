#ifndef SINGLETON_MANAGER_H
#define SINGLETON_MANAGER_H

#include <string>
#include <map>
#include <limits>
#include <algorithm>

class ProtoSingleton;

/**
 * @brief SingletonManager class save all Singleton's instances.
 * TODO: Manage construction/destruction Singleton instance's order
 */
class SingletonManager {

    public:

        /**
         * @brief add Add a singleton to the manager
         * @param name Singleton's ID
         * @param instance Singleton's instance
         * @param priority Construction/destruction's priority
         */
        static void add(std::string name, ProtoSingleton* instance, unsigned int priority);

        /**
         * @brief initialize_all Initialize all Singleton's instances
         */
        static void initialize_all();

        /**
         * @brief destroy_all Destroy all Singleton's instances
         */
        static void destroy_all();

    private:
        /**
         * @brief SingletonManager constructor
         */
        SingletonManager();
        /**
         * @brief SingletonInfo struct (intern struct) use to store Singleton's instance and priority
         */
        struct SingletonInfo {
            ProtoSingleton* instance;
            unsigned int priority;
        };

    /**
     * @brief _singleton_list Map to store an ID and his data
     */
    static std::map<std::string, struct SingletonInfo> _singleton_list;

};

#endif
