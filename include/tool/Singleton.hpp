#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>
#include <map>
#include <typeinfo>

template<class T>
class Singleton;
class SingletonManager;

/**
 * @brief Generic Class to represent all instance of template Singleton class.
 * Friend class of SingletonManager, which need access to initialize and destroy methods
 */
class ProtoSingleton {
    friend class SingletonManager;

    protected:
        /**
         * @brief ProtoSingleton constructor
         */
        ProtoSingleton() {}
        /**
         * @brief ProtoSingleton destructor
         */
        virtual ~ProtoSingleton() {}
        /**
         * @brief Initialize ProtoSingleton
         */
        virtual void initialize() = 0;
        /**
         * @brief Destroy ProtoSingleton
         */
        virtual void destroy() = 0;
};

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
        static void add(std::string name, ProtoSingleton** instance, unsigned int priority) {
            struct SingletonInfo info;
            info.instance = *instance;
            info.priority = priority;
            _singleton_list.insert(std::pair<std::string,struct SingletonInfo>(name, info));
        }

        /**
         * @brief initialize_all Initialize all Singleton's instances
         */
        static void initialize_all() {
            for(const auto& singleton : _singleton_list)
                singleton.second.instance->initialize();
        }

        /**
         * @brief destroy_all Destroy all Singleton's instances
         */
        static void destroy_all() {
            for(const auto& singleton : _singleton_list) {
                singleton.second.instance->destroy();
                delete singleton.second.instance;
            }
        }

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


template<class T>
/**
 * @brief Singleton class contains her own instance and undertake Singleton's register into the manager
 */
class Singleton : public ProtoSingleton {

public:
    /**
     * @brief instance Return her own instance
     * @return her own instance, or in the case of the Signelton's unregistered throw an UnregisteredSingleton's exception
     */
    static T* instance() {
        if(_instance == nullptr) {
            std::cerr << "Singleton " << typeid(T).name() << " Unregistered" << std::endl;
            exit(EXIT_FAILURE);
        }
        return _instance;
    }

    /**
     * @brief register_manager Allow to register instance into manager
     * @param name Singleton's ID
     * @param priority Construction/destruction's priority
     */
    static void register_manager(std::string name, unsigned int priority) {
        _instance = new T;
        SingletonManager::add(name, (ProtoSingleton**)&_instance, priority);
    }

    protected:
        /**
         * @brief Singleton constructor
         */
        Singleton() {
        }
        /**
         * @brief Singleton destrutor
         */
        virtual ~Singleton() {
        }

    private:
        /**
         * @brief _instance Own instance of Singleton
         */
        static T* _instance;
};

template<class T>
T* Singleton<T>::_instance = nullptr;

#endif
