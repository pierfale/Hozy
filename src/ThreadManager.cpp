#include "ThreadManager.hpp"
#include "tool/Thread.hpp"
#include "tool/log/Log.hpp"

Mutex ThreadManager::_mutex_thread_list;

ThreadManager::ThreadManager() : _thread_list(), _manage_thread(nullptr), _main_thread(nullptr), _alive(true) {

}

ThreadManager::ThreadManager(const ThreadManager& origin __attribute__((unused))) : ThreadManager() {

}

ThreadManager& ThreadManager::operator=(const ThreadManager& origin __attribute__((unused))) {
    return *this;
}

void ThreadManager::initialize() {
    _main_thread = Thread::create_thread_from_this();
    Log::ldebug << "[ThreadManager] Main thread = " << _main_thread->id() << std::endl;

	_alive = true;
	_manage_thread = new Thread();
	_manage_thread->create(MemberFunction<ThreadManager, void>(instance(), &ThreadManager::manage));
    Log::ldebug << "[ThreadManager] Manage thread = " << _manage_thread->id() << std::endl;

}

void ThreadManager::destroy() {
    delete _main_thread;

    //TODO close thread
}

void ThreadManager::add(Thread* thread) {
    Log::ldebug << "[ThreadManager] Add thread " << thread->id() << std::endl;
	_mutex_thread_list.lock();
    instance()->_thread_list.push_back(thread);
	_mutex_thread_list.unlock();
}

void ThreadManager::wait_all() {

	instance()->_alive = false;
	instance()->_manage_thread->join();

    Log::ldebug << "[ThreadManager] Thread " << instance()->_manage_thread->id() << " terminate (manage thread)" << std::endl;
	delete instance()->_manage_thread;
}

void ThreadManager::debug_all() {

    Thread::debug_handler(true);

    for(unsigned int i = 0; i<instance()->_thread_list.size(); i++) {
        if(instance()->_thread_list.at(i)->id() != Thread::get_current_thread_id() && instance()->_thread_list.at(i)->is_alive()) {
            instance()->_thread_list.at(i)->debug();
            instance()->_thread_list.at(i)->join(false);
        }
    }

    if(Thread::get_current_thread_id() != instance()->_main_thread->id())
        instance()->_main_thread->debug();
}

void ThreadManager::manage() {

	while(instance()->_thread_list.size() > 1 || instance()->_alive) {



		_mutex_thread_list.lock();

		for(unsigned int i=0; i<instance()->_thread_list.size(); i++) {
			if(!instance()->_thread_list.at(i)->is_alive()) {
				Log::ldebug << "[ThreadManager] Thread " << instance()->_thread_list.at(i)->id() << " terminate" << std::endl;
				delete instance()->_thread_list.at(i);
				instance()->_thread_list.erase(instance()->_thread_list.begin()+i);
				i--;
			}
		}

		_mutex_thread_list.unlock();
		Thread::sleep(10);

	}
}
