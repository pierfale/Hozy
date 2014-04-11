#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>
#include <map>
#include <typeinfo>
#include "SingletonManager.hpp"
//#include "tool/log/Log.hpp"

template<class T>
class Singleton;

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
        }
        return _instance;
    }

    /**
     * @brief register_singleton Allow to register instance into manager
     * @param name Singleton's ID
     * @param priority Construction/destruction's priority
     */
    static void register_singleton(std::string name, unsigned int priority) {
        _instance = new T;
        SingletonManager::add(name, _instance, priority);
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
