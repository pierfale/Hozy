#include "ThreadManager.hpp"
#include "tool/Thread.hpp"
#include "tool/log/Log.hpp"

ThreadManager::ThreadManager() : _thread_list() {

}

void ThreadManager::initialize() {
    Log::ldebug << "[ThreadManager] Main thread " << Thread::get_current_thread_id() << std::endl;
}

void ThreadManager::destroy() {
    //TODO close thread
}

void ThreadManager::add(Thread* thread) {
    Log::ldebug << "[ThreadManager] Add thread " << thread->id() << std::endl;
    instance()->_thread_list.push_back(thread);
}
