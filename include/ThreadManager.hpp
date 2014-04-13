#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "tool/Singleton.hpp"

class Thread;

class ThreadManager : public Singleton<ThreadManager> {

    friend class Singleton<ThreadManager>;
public:
    static void add(Thread* thread);

protected:
    void initialize();
    void destroy();

private:
    ThreadManager() {}
    std::vector<Thread*> _thread_list;

};

#endif
